// 2 ways pipe

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
  int p1[2], p2[2], status;
  pid_t id_fils;
  char rep[7], mesg[5];

  if(pipe(p1)){
    perror("error pipe 1");
    exit(1);
  }

  if(pipe(p2)){
    perror("error pipe 2");
    exit(2);
  }

  if((id_fils = fork()) == -1){
    perror("Erreur FORK");
    exit(3);
  }

  // père
  if(id_fils){
    // 1er tube: père vers fils
    close(p1[0]); // fermmé en lecture
    // 2ème tube : fils vers père
    close(p2[1]); // fermé en écriture

    // envoi message au fils via tube 1
    if(write(p1[1], "Hello", 5) != 5){
      fprintf(stderr, "père: erreur en écriture\n");
      exit(4);
    }

    // attente réponse du fils via tube 2
    if(read(p2[0],rep,7) != 7){
      fprintf(stderr, "père: erreur lecture\n");
      exit(5);
    }

    printf("message reçu par le père: %s\n", rep);
    wait(&status);
  } else {
    // fils

    close(p1[1]); // tube 1 fermé en écriture
    close(p2[0]); // tube 1 fermé en lecture

    // attente du messag du père
    if(read(p1[0], mesg, 5) != 5){
      fprintf(stderr, "fils: erreur lecture\n");
      exit(6);
    }

    printf("message reçu par le fils: %s\n", mesg);

    // envoi message au ppère
    if(write(p2[1], "Bonjour", 7) != 7){
      fprintf(stderr, "fils: erreur en écriture\n");
      perror("fils: erreur en écriture");
      exit(7);
    }

    exit(0);
  }

  return 0;
}
