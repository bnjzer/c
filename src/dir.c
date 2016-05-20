#include<stdio.h>
#include<sys/types.h>
#include<dirent.h>

int main(){
  struct dirent *lecture;
  DIR *rep;

  rep = opendir(".");

  printf("current dir: %s\n", (char*) rep);

  lecture = readdir(rep);

  while(lecture != NULL){
    printf("%s : %d\n", lecture->d_name, (int) lecture->d_ino);
    lecture = readdir(rep);
  }

  closedir(rep);

  return 0;
}
