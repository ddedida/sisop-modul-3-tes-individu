#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <unistd.h>

int main()
{
    key_t key = 4321;
    int shmid = shmget(key, sizeof(double), IPC_CREAT | 0666);
    double *area = (double *)shmat(shmid, NULL, 0);

    double r = 7.0;
    *area = 3.14 * r * r;

    printf("Luas lingkaran: %.2f\n", *area);
    shmdt(area);
    sleep(10);

    int shmid2 = shmget(key + 1, sizeof(double), IPC_CREAT | 0666);
    double *surface = (double *)shmat(shmid2, NULL, 0);

    double price = *surface * 25;

    printf("Luas permukaan: %.2f\n", *surface);
    printf("Total harga cat: %.2f\n", price);
    shmdt(surface);
}