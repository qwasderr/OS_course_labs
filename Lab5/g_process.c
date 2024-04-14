#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mqueue.h>
#include <signal.h>
#include <string.h>
#define MSG_SIZE 256
#define INTERVAL 10 
mqd_t mq_g;
int g(int x) {
    if (x>200) {
        while(1){}
    }
    else if (x>100) return 1;
    else return x;
}
int main(int argc, char *argv[]) {
    int value = atoi(argv[1]);
    mq_g = mq_open("/mq_g", O_WRONLY);
    if (mq_g == -1) {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }
        int result = g(value);
        char buffer[MSG_SIZE];
        sprintf(buffer, "%d", result);
        mq_send(mq_g, buffer,strlen(buffer)+1, 0);
    mq_close(mq_g);
}
