#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mqueue.h>
#include <signal.h>
#include <string.h>
#define MSG_SIZE 256
#define INTERVAL 10
mqd_t mq_f;
int f(int x) {
    if (x>100) {
        while(1){}
    }
    else if (x>50) return 0;
    else return x;
}
int main(int argc, char *argv[]) {
    int value = atoi(argv[1]); 
    mq_f = mq_open("/mq_f", O_WRONLY);
    if (mq_f == -1) {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }
       int result = f(value);
       char buffer[MSG_SIZE];
       sprintf(buffer, "%d", result); 
       mq_send(mq_f, buffer, strlen(buffer)+1, 0);
    mq_close(mq_f);
}
