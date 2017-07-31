#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/msg.h>

#define MAX_TEXT 512

const char text[] = "message from sender";

struct msg_s
{
    long int type;
    const char *text;
};

void send()
{
    struct msg_s msg = {1, text};
    int id;

    id = msgget((key_t)1234, 0666 | IPC_CREAT);
    int count = 10;
    while(count--)
    {
        msgsnd(id, (void *)&msg, MAX_TEXT, 0);
    }
}

void recv()
{
    char buf[MAX_TEXT];
    int msgid = -1;
    struct msg_s msg = {1, buf};

    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);

    int count = 10;
    while(count--)
    {
        msgrcv(msgid, (void*)&msg, BUFSIZ, msg.type, 0);
        printf("%s\n",msg.text);
    }
}

int main(int argc, char* argv[])
{
    pid_t pid;
    pid = fork();
    if (pid == 0) {
        send();
        return 0;
    }
    recv();
    return 1;
}
