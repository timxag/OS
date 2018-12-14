#include <stdio.h>
#include <sys/un.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"
database* create_list()
{
    database* list = (database*) malloc(sizeof(database));
    list->begin = NULL;
    list->end = NULL;
    list->size = 0;
    return list;
}
bool add(database* list, stored_message* msg)
{
    stored_message* tmp = (stored_message*)malloc(sizeof(stored_message));
    if(tmp == NULL) return false;
    *tmp = *msg;
    field* fld = (field*)malloc(sizeof(field));
    if(fld == NULL) return false;
    fld->msg = tmp;   
    if(list->size == 0)
    {
        fld->next = NULL;
        fld->prev = NULL;
        list->begin = fld;
        list->end = fld;
        ++list->size;
        return true;
    }
    else
    {
        fld->next = list->begin;
        fld->prev = NULL;
        list->begin->prev = fld;
        list->begin = fld;
        ++list->size;
        return true;
    }
}
field* find(database* list, char* name)
{
    field* tmp = list->end;
    while(tmp != NULL)
    {
        if(strcmp(name, tmp->msg->recipient) == 0)
        {
            break;
        }
        else
        {
            tmp = tmp->prev;
            continue;
        }
    }
    return tmp;
}
void print_list(database* list)
{
    field* tmp = list->begin;
    //printf("%d\n", list->size);
    while(tmp != NULL)
    {
        printf("------------------------------\n");
        printf("recipient is %s\n",(char*)tmp->msg->recipient);
        printf("sender is %s\n", (char*)tmp->msg->sender);
        printf("message is %s\n", (char*)tmp->msg->msg);
        printf("------------------------------\n");        
        tmp = tmp->next;
    }
    return;
}
bool purge(database* list, field* fld)
{
    if(list->size == 1)
    {
        list->begin = NULL;
        list->end = NULL;
        free(fld);
        --list->size;
        return true;
    }
    if(fld == list->begin)
    {
        fld->next->prev = NULL;
        list->begin = fld->next;
        free(fld);
        --list->size;        
        return true;
    }
    if(fld == list->end)
    {
        fld->prev->next = NULL;
        list->end = fld->prev;
        free(fld);
        --list->size;
        return true;
    }
    else
    {
        fld->prev->next = fld->next;
        fld->next->prev = fld->prev;
        free(fld);        
        --list->size;
        return true;        
    }
}