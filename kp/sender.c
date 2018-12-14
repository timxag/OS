#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include "config.h"
int main()
{
    int sock;
    struct sockaddr_in addr;
    stored_message* message = (stored_message*) malloc(sizeof(stored_message)); // buffer for message
    printf("Enter your name: ");
    scanf("%s", message->sender);
    while(1)
    {
        char command;
        printf("What you want?\n");
        printf("m - compose and send message to someone\n");
        printf("r - refresh letter box. May be someone just texted to you?\n");
        printf("q - exit from client\n");
        scanf("%s", &command);
        if(command == 'm') // write message
        {
            message->type = _msg; //simple message
            printf("To :");
            scanf("%s", message->recipient);
            printf("Your message: ");
            scanf("%s", message->msg);
        }
        else if(command == 'r') //request for mail
        {
            message->type = _request; // request
        }
        else if(command == 'q') 
        {
            free(message);
            exit(0);
        }
        else 
        {
            printf("Undefined command\n");
            continue;
        }
        A:;
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if(sock < 0)
        {
            perror("socket");
            exit(1);
        }
        addr.sin_family = AF_INET;
        addr.sin_port = htons(3425); //порт...
        addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

        if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
        {
            perror("connect");
            exit(2);
        }

        send(sock, message, sizeof(stored_message), 0);
        recv(sock, message, sizeof(stored_message), 0);

        if(message->type == _msg)
        {
            if(message->result) printf("Sent!\n");
            else 
            {
                printf("Try again later...\n"); 
                sleep(2);
                goto A;
            }
        }
        else if(message->type == _request)
        {
            if(message->result) 
            {
                printf("You have message from %s:", message->recipient);
                printf("%s\n", message->msg);
            }
            else printf("Letter box is empty\n");
        }
        else
        {
            printf("Undefined command\n");
            exit(-1);
        }
        close(sock);
    }
    return 0;
}