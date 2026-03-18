#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <signal.h>
#include <time.h>
#include "utils.h"

#ifndef UTILS_H
#define UTILS_H

int getSpeed();
int getSeatbelt();

#endif

int speed, seatbelt;
int fd[2];
pthread_mutex_t lock;

void signalHandler(int sig) {
    printf("\nShutting down safely...\n");
    exit(0);
}

void* monitorThread(void* arg) {
    while(1) {
        pthread_mutex_lock(&lock);

        if(speed > 20 && seatbelt == 0)
            printf(" WARNING! Speed=%d Seatbelt OFF\n", speed);
        else
            printf("SAFE Speed=%d Seatbelt=%d\n", speed, seatbelt);

        pthread_mutex_unlock(&lock);
        sleep(1);
    }
    return NULL;
}

int main() {

    signal(SIGINT, signalHandler);

    pthread_mutex_init(&lock, NULL);

    pipe(fd);

    pid_t pid = fork();

    if(pid == 0) {
        // CHILD (SENSOR)
        srand(time(NULL));

        while(1) {
            int s = getSpeed();
            int sb = getSeatbelt();

            write(fd[1], &s, sizeof(s));
            write(fd[1], &sb, sizeof(sb));

            sleep(1);
        }
    }
    else {
        // PARENT (MONITOR)

        pthread_t t1;
        pthread_create(&t1, NULL, monitorThread, NULL);

        while(1) {

            read(fd[0], &speed, sizeof(speed));
            read(fd[0], &seatbelt, sizeof(seatbelt));

            pthread_mutex_lock(&lock);

            int file = open("log.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);

            char buffer[100];

            if(speed > 20 && seatbelt == 0)
                sprintf(buffer, "Speed:%d Seatbelt:%d → WARNING\n", speed, seatbelt);
            else
                sprintf(buffer, "Speed:%d Seatbelt:%d → SAFE\n", speed, seatbelt);

            write(file, buffer, strlen(buffer));
            close(file);

            pthread_mutex_unlock(&lock);
        }

        waitpid(pid, NULL, 0);
    }

    return 0;
}
