#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

int main(){
  struct eleve { 
    char nom[10];
    int note;
  };

  int fd, i, ret, nbEleves;
  struct eleve unEleve;

  char *filename = "./notes.dat";
  nbEleves = 2;

  fd = open(filename, O_RDWR | O_CREAT | S_IRUSR | S_IWUSR);
  if(fd == -1)
    perror("Problem while opening opening file");

  i=0;
  while(i < nbEleves){
    printf("Nom élève: ");
    scanf("%s", unEleve.nom);
    printf("Note: ");
    scanf("%d", &unEleve.note);

    write(fd, &unEleve, sizeof(unEleve));

    i++;
  }

  ret = lseek(fd, 0, SEEK_SET);
  if(ret == -1)
    perror("Problem while lseek");

  printf("New position: %d\n", ret);

  i=0;
  while(i < nbEleves){
    read(fd, &unEleve, sizeof(unEleve));
    printf("%s : %d\n", unEleve.nom, unEleve.note);
    i++;
  }

  close(fd);

  return 0;
}
