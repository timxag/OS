#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define P1_READ    0
#define P2_WRITE   1

int fd[2];

int sum(int n)
{
    pid_t pid;
    int buf, status, bufread;

    if (n == 1) {
        return 1;
    }

    pid = fork(); 
    if (pid == 0) {
        buf = sum(n - 1) + n; 
        close(fd[P1_READ]); 
        if (write(fd[P2_WRITE], &buf, sizeof(buf)) == -1) { 
            perror("write");
        }
        exit(0);
    } else if (pid < 0) { 
        perror("fork");
    } else { 
        if (waitpid(pid, &status, 0) == -1) { 
            perror("waitpid");
        }
    }

    if (read(fd[P1_READ], &bufread, sizeof(bufread)) == -1) { 
        perror("read");
    }

    return bufread;
}

int main(void)
{
    int n = 0;

    if (pipe(fd) == -1) { 
        perror("pipe");
    }

    printf("Enter a sequence number: ");
    scanf("%d", &n);
    if (n < 0) {
        printf("Number must be > 0.\n");
    } else {
        printf("%d\n", sum(n));
    }

    return 0;
}
