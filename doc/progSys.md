Unix/Linux programmation avancée

# Compilation avec gcc

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

# Bibliothèques dynamiques et statiques

bibliothèque standard : glibc. Elle contient 24 en-têtes

## Bibliothèques statiques (.a)

pour compiler la bibliothèque : `gcc -c fic1.c fic2.c && ar rcs libfic.a fic1.o fic2.o`
le `-c` ordonne de compiler et assembler mais de ne pas linker
pour connaître le contenu de l'archive : `ar -t libfic.a`
pour lister plus en détails le contenu de la librairie : `nm -s libfic.a`

## Bibliothèques dynamiques/partagées (.so)

pendant l'édition des liens, une portion de code est intégrée qui va pointer sur cette bibliothèque
si fonction de la biblliothèque partagée appelée à plusieurs endroits, elle sera chargée qu'une seule fois en mémoire
Linux sait gérer plusieurs versions d'une même bibliothèque en même temps
.so[.version] dans `/lib/ /usr/lib/` (.dll sur Windows)

poour compiler la lib : `gcc -fPIC -shared -Wl,-soname,libfic.so.1 -o lib/libfic.so.1.0 fic01.c fic02.c`
`-fPIC` pour que le code ne soit pas re-logeable
`ln -sf libfic.so.1.0 libfic.so`
ajouter le chemin du .so dans un nouveau fichier.conf dans `/etc/ld.so.conf.d/`, puis `ldconfig`
compiler le binaire utilisant la lib : `gcc -L./lib ficmain.c -o ficmain -lfic`

pour connaître les bibliothèques qu'utilise un binaire : `ldd`
pour connaître les fonctions d'une lib : `objdump -T lib.so`

# Language C

* `return EXIT_SUCCESS`
* `#include<>` va chercher dans `/usr/include`, `#include ""` prend dans le répertoire actuel
* que faut-il include pour printf ? `man 3 printf`

# OS

ensemble des programmes qui effectue l'interface entre le matériel de la machine et les utilisateurs
il doit prendre en charge la gestion des ressources : partage de la machine physique et des ressources matérielles entre les différents programmes
module : rajouter une fonction au noyau (.ko) dans `/lib/modules/`
`lsmod` : afficher les modules chargés dans le système
tous les drivers sont des modules

# Processus, threads et ordonnancement

## Processus

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
  * bloqué
zombie : exécution terminée mais le PCB du processus existe toujours du fait que son père n'a pas pris en compte sa terminaison
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

## Threads

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


### en C

bibliothèque Linux Threads, pas dans la glibc `#include "pthread.h"`, `-lpthreads` lors du linking. Thread de type `pthread_t`. `pthread_self()` pour connaître son identité
`pthread_create()` : créer un Thread au sein du processus
`pthread_exit()` : met fin au thread
`pthread_join()` : jointure entre 2 threads. Attente que l'autre se termine

attributs d'un thread:
* adresse de départ et taile de la pile
* politique d'ordonnancement
* priorité
* attachement ou détachement (un thread détaché se termine immédiatement sans pouvoir être pris en compte par la primitive `pthread_join()`

# sysadmin tips

* `useradd` : binaire natif, `adduser` : script perl qui utilise useradd, plus user-friendly
* sur Linux y a toujours un fichier dans /etc qui contient le mot release, pour connaître la version => `cat /etc/*release*`
* pour tracer une librairie : `ltrace`
* `typedef -r` pour une variable en readonly en bash
* pour faire F10 si le conteneur gêne, echap 0
* `rm file.[ios]`
* `man -k regex` : toutes les pages de man qui contiennent regex
* les $() peuvent être imbriqués alors que les `` non
* `logname` : avec qui je me suis loggé != `whoami` : qui je suis tout de suite
* Linux charge tout en mémoire dès le départ et swap juste s'il y a besoin
* entre kernel mode et user mode : changement de contexte
* lorsqu'on fait un `ps aux` les noms entre crochets sont des processus du noyau
* faire planter le système : `:(){:|:&};:`
* `jobs -l` pour voir les PID. `fg 1` pour le remettre en premier plan

