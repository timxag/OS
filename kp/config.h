#ifndef CONFIG
#define CONFIG
#define MAX_QUEUE_LEN 256
#define MSG_SIZE 1028
#include <stdbool.h>
enum message_type
{
    _quit = 0,
    _msg,
    _request
};
typedef struct // struct of message
{
    char sender[14];
    char recipient[14];
    char msg[MSG_SIZE];
    bool result;
    int type;
} stored_message;
#endif