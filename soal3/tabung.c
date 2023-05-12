#include <sys/shm.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    key_t key = 4321;

    int shmid = shmget(key, sizeof(double), IPC_CREAT | 0666);
    int shmid2 = shmget(key + 1, sizeof(double), IPC_CREAT | 0666);

    double *area = (double *)shmat(shmid, NULL, 0);
    double *surface = (double *) shmat(shmid2, NULL, 0);

    double r = 7.0;
    double t = 10.0;

    *surface = 2.0 * *area + 2.0 * 3.14 * r * t;

    printf("Luas permukaan tabung: %f\n", *surface);

    shmdt(area);
    shmdt(surface);
}