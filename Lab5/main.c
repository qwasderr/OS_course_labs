#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#define INTERVAL 10
#define MSG_SIZE 256
int flag_keep_asking=1;
char result_f[MSG_SIZE] = "No"; 
char result_g[MSG_SIZE] = "No";
mqd_t mq_f, mq_g;
void close_mq(){
    mq_close(mq_f);
    mq_close(mq_g);
    mq_unlink("/mq_f");
    mq_unlink("/mq_g");
}
void lazy_exec(){
    if (strcmp(result_f, "No") !=0){
        int res = atoi(result_f);
        //printf("%d\n",res);
        if (res!=0) {
        printf("f(x) || g(x) = %d\n", 1);
        close_mq();
        exit(0);
        }
    }
    if (strcmp(result_g, "No") !=0){
        int res = atoi(result_g);
        //printf("%d\n",res);
        if (res!=0) {
        printf("f(x) || g(x) = %d\n", 1);
        close_mq();
        exit(0);
        }
    }
}
void alarm_handler(int signum) {
    if (flag_keep_asking==1){
                 printf("Продовжити обчислення? (1 - так, 2 - припинити, 3 - продовжити без перепитування): ");
                 //fflush(stdout);
                 char response[10];
                 fgets(response, sizeof(response), stdin);
                 if (strcmp(response, "1\n") == 0) {} 
                 else if (strcmp(response, "2\n") == 0) {exit(EXIT_FAILURE);} 
                 else if (strcmp(response, "3\n") == 0) {flag_keep_asking=0;} 
                 else {}
    }
    alarm(INTERVAL);
    
}
int main() {

    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MSG_SIZE;
    attr.mq_curmsgs = 0;

    mq_f = mq_open("/mq_f", O_CREAT | O_RDONLY, 0644, &attr);
    mq_g = mq_open("/mq_g", O_CREAT | O_RDONLY, 0644, &attr);

    if (mq_f == -1 || mq_g == -1) {
        perror("mq_open");
        exit(1);
    }
    char buffer[20];
    int value;
    printf("X: ");
    fgets(buffer, sizeof(buffer), stdin);
    //system("./f_process &");
    //system("./g_process &");
    if (fork() == 0) { 
        execl("./f_process", "f_process", buffer, NULL);
    } 
    if (fork() == 0) { 
        execl("./g_process", "g_process", buffer, NULL);
    } 

    struct sigaction sa;
    sa.sa_handler = alarm_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGALRM, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
    alarm(INTERVAL);

    //mq_receive(mq_g, (char*)&result_g, MSG_SIZE, NULL);
    //lazy_exec();
    //mq_receive(mq_f, (char*)&result_f, MSG_SIZE, NULL);
    //lazy_exec();
    while (strcmp(result_f, "No") == 0 || strcmp(result_g, "No") == 0) {
        char result[MSG_SIZE];
        if (mq_receive(mq_g, result, MSG_SIZE, NULL) != -1) {strcpy(result_g, result); lazy_exec();}
        if (mq_receive(mq_f, result, MSG_SIZE, NULL) != -1) {strcpy(result_f, result); lazy_exec();}
    }
    //printf("%d/n",result_f);
    //printf("%d/n",result_g);
    int result = atoi(result_f) || atoi(result_g);

    printf("f(x) || g(x) = %d\n", result);

    close_mq();
}
