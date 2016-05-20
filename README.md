# Unix/Linux : programmation system programming in C

## 1) Compilation avec gcc

Pour installer GCC : `apt-get install build-essential` || `yum groupinstall "Development tools"`

4 étapes de la "compilation" :
1. **preprocessing** : `gcc -E compil.c > compil.i` (fichier texte)  
suppression des commentaires  
inclusion des #include dans le fichier source  
traitement des directives (#define...)  
`-Wall` pour afficher les warnings, qui par défaut ne s'affichent pas
2. **compilation** : transformation en assembleur : `gcc -S compil.i`
3. **assembling** : transformation du code assembleur en code machine binaire : `gcc -c compil.s` || `as -o compil.o compil.o`  
`od -x compil.o` pour voir le contenu binaire || `objdump -t compil.o`
4. **linking** : après assembling, le code est incomplet, il n'a pas l'implémentation de toutes les fonctions (exemple printf, dont le code est dans une bibliothèque)  
l'édition des liens va réunir le fichier objet et les fonctions contenues dans les bibliothèques, pour produire l'exécutable complet

## 2) Bibliothèques dynamiques et statiques

Bibliothèque standard : `glibc`. Elle contient 24 en-têtes

### 2.1) Bibliothèques statiques (.a)

pour compiler la bibliothèque : `gcc -c fic1.c fic2.c && ar rcs libfic.a fic1.o fic2.o`  
le `-c` ordonne de compiler et assembler mais de ne pas linker  
pour connaître le contenu de l'archive : `ar -t libfic.a`  
pour lister plus en détails le contenu de la librairie : `nm -s libfic.a`

### 2.2) Bibliothèques dynamiques/partagées (.so)

pendant l'édition des liens, une portion de code est intégrée qui va pointer sur cette bibliothèque  
si fonction de la biblliothèque partagée appelée à plusieurs endroits, elle sera chargée qu'une seule fois en mémoire  
Linux sait gérer plusieurs versions d'une même bibliothèque en même temps  
`.so[.version]` dans `/lib/ /usr/lib/` (.dll sur Windows)

poour compiler la lib : `gcc -fPIC -shared -Wl,-soname,libfic.so.1 -o lib/libfic.so.1.0 fic01.c fic02.c`  
`-fPIC` pour que le code ne soit pas re-logeable  
`ln -sf libfic.so.1.0 libfic.so`  
ajouter le chemin du .so dans un nouveau fichier.conf dans `/etc/ld.so.conf.d/`, puis `ldconfig`  
compiler le binaire utilisant la lib : `gcc -L./lib ficmain.c -o ficmain -lfic`

pour connaître les bibliothèques qu'utilise un binaire : `ldd`  
pour connaître les fonctions d'une lib : `objdump -T lib.so`

### 2.3) Language C

* `return EXIT_SUCCESS`
* `#include<>` va chercher dans `/usr/include`, `#include ""` prend dans le répertoire actuel

## 3) Système d'exploitation

Ensemble des programmes qui effectuent l'interface entre le matériel de la machine et les utilisateurs  
il doit prendre en charge la gestion des ressources : partage de la machine physique et des ressources matérielles entre les différents programmes  
module : rajouter une fonction au noyau (.ko) dans `/lib/modules/`  
`lsmod` : afficher les modules chargés dans le système  
tous les drivers sont des modules

## 4) Processus, threads et ordonnancement

### 4.1) Processus

Le processus classique est un processus lourd

instance d'un programme exécutable
processus : programme en cours d'exécution auquel est associé un environnement processeur (compteur ordinal, registre d'état, registres généraux) et un environnemnt mémoire appelés contexte du processus
il évolue dans un espace d'adressage protégé
32 bits (64 aussi) : espace d'adressage virtuel de 2^32 = 4 GB
PAE : on peut dépasser cette limite
mais en 64 bits le plan d'adressage peut varier
sur un 32 bits 3 Gio affectés à l'application et 1 Gio à l'OS
sur un 64 bits la totalité des 4 Gio est affectée à l'espace utilisateur
valeur (inatteignable) max du PID : 32768 (`/proc/sys/kernel/pid_max`)
un processus a un **état** :
  * prêt
  * élu (par l'ordonnanceur)
  * bloqué (attente de ressources, par exemple input utilisateur)
zombie : exécution terminée mais le PCB du processus existe toujours du fait que son père n'a pas pris en compte sa terminaison
processus qui a terminé son exécution et attend la prise en compte de cette fin par son père
Pour tuer un zombie il est nécessaire de tuer son père, le zombie est alors automatiquement rattaché au processus n°1 (init) qui s'occupera de le tuer.
le noyau a un chargeur qui a pour rôle de monter en mémoire centrale le code et les données du programme à exécuter
en même temps que ce chargement Linux crée une structure de description du processus associé au programme exécutable : le PCB (Process Control Block) `struct task_struct` dans `sched.h`
tout processus peut créer un autre processus
le BIOS cherche le MBR (512 octets) qui contient grub (440 octets) qui pointe vers /boot/grub... et précise le kernel /boot
Le kernel + modules démarrent. dans le noyau le 1er processus 0 démarre le 1er process avec PID 1 : /sbin/init
system V => /etc/inittab
`pidof init`
`pid_t fork(void)`
`pid_t wait(int *status)` : exécution du processus père suspendue jusqu'à ce que processus fils se termine
`pid_t waitpid(pid_t pid, int *status, int options)`
`void exit(int status)`
les 6 primitives de recouvrement permettent à un processus de charger en mémoire un nouveau code exécutable : `man 3 exec`
le code exécuté remplace l'ancien code sur le même PID
`main(   char **arge[])`: liste de pointeurs permettant d'accéder à l'environnement d'exécution du processus
quand on fork, un nouveau processus est créé. Tout est copié. Nouvel adressage mémoire

### 4.3) Threads

Un processus est constitué d'un espace d'adressage avec un seul fil d'exécution  
L'extension consiste à admettre plusieurs fils d'exécution indépendants dans un même espace d'adressage
threads caractérisés par une valeur de compteur ordinal propre et une pile d'exécution privée
l'entité contenant les différents fils d'exécutions est appelée processus
thread: processus léger
dans un CPU le compteur ordinal est le registre qui contient l'adresse mémoire de l'instruction en cours d'exécution. Une fois l'instruction chargée, il est automatiquement incrémentée pour pointer l'instruction suivante

les ressources sont partagées par tous les fils d'exécution
avantage: allègement des opérations de changement de contexte
création d'un nouveau fil d'exécution allégée puisque pas besoin de créer nouvel espace d'adressage
- : problème de partage des ressources plus important

threads niveau utilisateur (cercle 3) : le noyau Linux les ignore, il ordonnance des processus classiques composés d'un seul fil d'exécution
la bibliothèque système (POSIX Threads ou pthreads) gère l'interface avec le noyau en prenant en charge la gestion des threads à ce dernier. Elle est donc responsable de commuter les threads au sein d'un même processus
+: allège les commutations entre les threads d'un meême processus car cela se faiut au niveau utilisateur et pas au niveau noyau
-: au sein d'un processus, un thread peut monopoliser le processeur pour lui tout seul. Un thread bloqué au sein d'un processus bloque l'ensemble des threads de ce processus

threads niveau noyau: le noyau connaît l'existence des threads au sein d'un processus et attribue le processeur à chacun des threads de manière indépendante
-: commutation
+: un thread en bloque pas un autre


### 4.4) Ordonnancement

Son rôle est de gérer le partage du processeur entre les processus qui sont dans l'état prêt (opérations d'élection)
ordonnancement préemptif: réquisition autorisée (transition de l'état élu vers l'état prêt). Aujourd'hui quasi tous les systèmes
3 politiques d'ordonnacement sous Linux (celle appliquée à un processus est codée dans le champ policy de son PCB):
1. SCHED_FIFO et SCHED_RR: destinées aux processus "temps réel"
les processus sont qualifiés par une priorité fixe
SCHED_FIFO: premiier arrivé premier servi
SCHED_RR: tourniquet à quantum de temps
2. SCHED_OTHER: destinée aux processus classiques
priorité dynamique qui varie en fonction de l'utilisation faite par le processus des ressources de la machine et notamment du processeur
un processus devient moins prioritaire que les processus pas encore exécutés
un fils hérite de la priorité de son père et de la moitié des ticks
3. SCHED_BATCH: traitement de lots
4. SCHED_IDLE: tâches de très faibles priorité en arrière plan

L'ordonnancement réalisé par le noyau Linux est découpé en périodes. Au début de chaque période le système calcule le quantum de temps attribué à chaque processus

Au niveau utilisateur ce n'est pas le noyau qui ordonnances les threads, mais la bibliothèque POSIX thread

### 4.5) C

bibliothèque Linux Threads, pas dans la glibc `#include "pthread.h"`, `-lpthreads` lors du linking. Thread de type `pthread_t`. `pthread_self()` pour connaître son identité
`pthread_create()` : créer un Thread au sein du processus
`pthread_exit()` : met fin au thread
`pthread_join()` : jointure entre 2 threads. Attente que l'autre se termine (comme wait() pour les fork)

attributs d'un thread:
* adresse de départ et taile de la pile
* politique d'ordonnancement
* priorité
* attachement ou détachement (un thread détaché se termine immédiatement sans pouvoir être pris en compte par la primitive `pthread_join()`

prototypes déclarés dans sched.h
`int sched_setscheduler()` : modifie la politique d'ordonnacement policy du processus. Si PID NULL, processus courant concerné
`int sched_getscheduler()` : obtient la politique d'ordonnancement. "
̀int sched_setparam()` : modifie les paramètres. utilise la structure sched_param qui contient la priorité
̀int sched_getparam()`
si échec, retourne -1 et errno prend certaines valeurs
`int nice(int inc)` : modifie la politesse du processus (colonne NI dans top)
`int getpriority()` et `int setpriority()` permettent de lire et écrire la priorité d'un processus

## 5)  Système de gestion de fichiers

Les fichiers sont typéstypes de fichier:
ll : ^p : pipe pour communiquer
     ^s : socket
`ifconfig`: obsolete => `ip addr`
`netstat` obsolete => `ss`
`nslookup` => `dig`

pour avoir les infos sur un fichier : `stat`

FS journalisé : avant de modifier les tables système, le pilote écrit sur disque les détails de la transaction dans un journal. En cas d'arrêt brutal, il suffit de compléter la transaction

quel que soit le système de fichier c'est les mêmes primitives, grâce à VFS

# Communication inter-processus : via pipe

## sysadmin tips

* `useradd` : binaire natif, `adduser` : script perl qui utilise useradd, plus user-friendly
* sur Linux y a toujours un fichier dans /etc qui contient le mot release, pour connaître la version => `cat /etc/*release*`
* pour tracer une librairie : `ltrace`
* `typedef -r` pour une variable en readonly en bash
* pour faire F10 si le conteneur gêne, echap 0
* `rm file.[ios]`
* `man -k regex` : toutes les pages de man qui contiennent regex (POSIX, sinon pour Linux: `apropos`)
* les $() peuvent être imbriqués alors que les `` non
* `logname` : avec qui je me suis loggé != `whoami` : qui je suis tout de suite
* Linux charge tout en mémoire dès le départ et swap juste s'il y a besoin
* entre kernel mode et user mode : changement de contexte
* lorsqu'on fait un `ps aux` les noms entre crochets sont des processus du noyau
* faire planter le système : `:(){:|:&};:`
* `jobs -l` pour voir les PID. `fg 1` pour le remettre en premier plan

## References

* [Advanced Linux Programming](http://advancedlinuxprogramming.com/alp-folder/)
