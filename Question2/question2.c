#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid == 0) {
        printf("Child (PID %d) is running\n", getpid());
        while (1) {
            sleep(1);
        }
    }
    else {
        printf("Parent: monitoring Child (PID %d) \n", pid);

        sleep(3);

        if (kill(pid, 0) == 0) {
            printf("Child: unresponsive.\n");
            kill(pid, SIGTERM);

            sleep(1);
            if (kill(pid, 0) == 0) {
                printf("Parent: Sending SIGKILL\n");
                kill(pid, SIGKILL);
            }
        }

        wait(NULL);
        printf("Parent: Child killed successfully.\n");
    }

    return 0;
}
