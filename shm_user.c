#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char **argv)
{

    int pid;
    pid = fork();

    if(pid > 0) {
        printf(2, "parent\n");
        if(shm_open(0, 1, 0) == 0) {
            printf(2, "shm successful opened\n");
            int shm = shm_attach(0);
            printf(2, "parent attached -> %d\n", shm);

            ;(*((int *) shm)) = 100;
            printf(2, "=> %d\n", *((int*)shm))

            while (1) {
                (*((int *) shm)) ++;
                printf(2, "+1\n");
            }
        }
        wait();
    } else if(pid == 0) {
        printf(2, "child\n");
        int shm;
        while((shm = shm_attach(0)) < 0);

        printf(2, "child attached -> % d\n", shm);
        while (1)
            printf(2, "-> %d\n", *((int*)shm));
    }

    exit();
}
