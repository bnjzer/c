#include<stdio.h>
#include<sched.h>
#include<errno.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/time.h>
#include<sys/resource.h>

int main(){
  pid_t ret, pid;
  int politique, status;
  struct timespec quantum;
  struct sched_param param;

  ret = fork();

  if(ret == 0){ // I'm the son
    pid = getpid();
    printf("Je suis le fils: \n");
    printf("Ma priorité d'ordonnancement est %d\n", getpriority(PRIO_PROCESS, pid));
    politique = sched_getscheduler(pid);

    switch(politique){
      case SCHED_RR:
        printf("politique d'ordonnancement: SCHED_RR\n");
        break;
      case SCHED_FIFO:
        printf("politique d'ordonnancement: SCHED_FIFO\n");
        break;
      case SCHED_OTHER:
        printf("politique d'ordonnancement: SCHED_OTHER\n");
        break;
      default:
        printf("politique d'ordonnancement: %d\n", politique);
    }

    setpriority(PRIO_PROCESS, pid, 5);
    printf("Ma priorité d'ordonnancement est %d\n", getpriority(PRIO_PROCESS, pid));

    printf("application de la politique FIFO\n");

    param.sched_priority = 10;
    if(sched_setscheduler(pid, SCHED_FIFO, &param) == -1){
      perror("Problème setscheduler");
      switch(errno){
        case ESRCH:
          printf("problem: ESRCH\n");
          break;
        case EACCES:
          printf("problem: EACCESS\n");
          break;
        case EPERM:
          printf("problem: EPERM\n");
          break;
        default:
          printf("problem: %d\n", errno);
      }
    }

    printf("Ma priorité d'ordonnancement est %d\n", getpriority(PRIO_PROCESS, pid));
    politique = sched_getscheduler(pid);

    switch(politique){
      case SCHED_RR:
        printf("politique d'ordonnancement: SCHED_RR\n");
        break;
      case SCHED_FIFO:
        printf("politique d'ordonnancement: SCHED_FIFO\n");
        break;
      case SCHED_OTHER:
        printf("politique d'ordonnancement: SCHED_OTHER\n");
        break;
      default:
        printf("politique d'ordonnancement: %d\n", politique);
    }
  }else{
    printf("Je suis le père: \n");
    printf("priorité min %d et max %d de la politique FIFO\n",
        sched_get_priority_min(SCHED_FIFO),
        sched_get_priority_max(SCHED_FIFO));

    printf("priorité min %d et max %d de la politique RR\n",
        sched_get_priority_min(SCHED_RR),
        sched_get_priority_max(SCHED_RR));

    sched_rr_get_interval(0, &quantum);

    printf("voici les valeurs du quantum de la politique SCHED_RR, %d secondes, %ld nanosecondes\n",
        (int) quantum.tv_sec, quantum.tv_nsec);

    wait(&status);
  }
  return 0;
}
