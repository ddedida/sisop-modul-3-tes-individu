#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <pthread.h>

#define FOLDER "latihan"
#define SUBFOLDER "subangka"

void *spam(void *arg){
  FILE *fp = fopen("angka.txt", "w");
  for (int i = 1; i <= 100000; i++){
    fprintf(fp, "%d\n", i);
  }
  fclose(fp);
  pthread_exit(NULL);
}

void *makeFolder(void *arg){
  char folder[100];
  char subfolder[100];
  char file[1000];
  struct stat st;
  FILE *fp;
  mkdir(FOLDER, 0755);

  for (int i = 1; i <= 1000; i++){
    sprintf(subfolder, "%s/%s %d", FOLDER, SUBFOLDER, i);
    mkdir(subfolder, 0755);
    sprintf(file, "%s/angka.txt", subfolder);
    if (stat(file, &st) == -1){
      fp = fopen(file, "w");
      fprintf(fp, "angka.txt in %s\n", subfolder);
      fclose(fp);
      link("angka.txt", file);
    }
  }
  pthread_exit(NULL);
}

int main(int argc, char const *argv[]){
  pthread_t tid[2];
  int i;

  if (pthread_create(&tid[0], NULL, spam, NULL) != 0){
    perror("pthread_create");
    exit(EXIT_FAILURE);
  }
  if (pthread_create(&tid[1], NULL, makeFolder, NULL) != 0){
    perror("pthread_create");
    exit(EXIT_FAILURE);
  }
  for (i = 0; i < 2; i++){
    if (pthread_join(tid[i], NULL) != 0){
      perror("pthread_join");
      exit(EXIT_FAILURE);
    }
  }
  return 0;
}
