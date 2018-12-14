#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "config.h"
#include "database.h"
int main()
{
    char name[14]; 
    printf("Enter your name(less than 13 characters)\n");
    scanf("%s", name);
    database* list = create_list();
    field* tmp = NULL;
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
            stored_message* message = (stored_message*) malloc(sizeof(stored_message)); // buffer for message
            message->type = false; //simple message
            strcpy(message->sender, name);
            printf("To :");
            scanf("%s", message->recipient);
            printf("Your message: \n");
            scanf("%s", message->msg);
            fflush(stdin); // temp measures
            fflush(stdout); // temp measures
            add(list, message);
            //print_list(list);

        }
        else if(command == 'p')
        {
            print_list(list);
        }     
        else if(command == 'f')
        {
            printf("Enter name\b\b\b\b\b\b\b\b\b\n");
            char name[14];
            scanf("%s", name);
            field* tmp = find(list, name);
            if(!tmp) printf("User find\n");
            else printf("NO\n");
            purge(list, tmp);
        }
    }
}