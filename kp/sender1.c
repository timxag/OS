#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    int sock;
    struct sockaddr_in addr;
    char message[64];
    char buf[64];
    while(1)
    {
        printf("Press any key to send message\n");
        getchar();

        sock = socket(AF_INET, SOCK_STREAM, 0);
        if(sock < 0)
        {
            perror("socket");
            exit(1);
        }
        addr.sin_family = AF_INET;
        addr.sin_port = htons(3425); // или любой другой порт...
        addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
        if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
        {
            perror("connect");
            exit(2);
        }
        scanf("%s", message);
        send(sock, message, sizeof(message), 0);
        recv(sock, buf, sizeof(message), 0);
        printf("%s\n", buf);
        close(sock);
    }
    return 0;
}