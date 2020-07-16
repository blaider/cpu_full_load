
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <limits.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>

//run shell script: time echo "scale=5000; 4*a(1)" | bc -l -q

static int run_daemon = 0;

void print_usage(char *cmd)
{
    printf("%s usage:\n",cmd);
    printf("\t -h show this help\n");
    printf("\t -d run deamon\n");
}

int parse_opt(int argc, char *argv[])
{
    int ch;
    while ((ch = getopt(argc, argv, "dh")) != -1)
    {
        //printf("optind: %d\n", optind);
        switch (ch)
        {
        case 'h':
            print_usage(argv[0]);
            exit(0);
            break;
        case 'b':
            printf("HAVE option: -b\n");
            printf("The argument of -b is %s\n\n", optarg);
            break;
        case 'c':
            printf("HAVE option: -c\n");
            printf("The argument of -c is %s\n\n", optarg);
            break;
        case 'd':
            //printf("HAVE option: -d\n");
            run_daemon = 1;
            break;
        case 'e':
            printf("HAVE option: -e\n");
            printf("The argument of -e is %s\n\n", optarg);
            break;
        case '?':
            printf("Unknown option: %c\n", (char)optopt);
            break;
        }
    }
}

void *cpu_pi(void *arg)
{
    printf("start thread \n");
    pthread_detach(pthread_self());

    while (1)
    {
        ;
    }
}

int main(int argc, char *argv[])
{
    int i = 0;
    printf("This system has:\n\t%d processors configured  "
           "\n\t%d processors available.\n",
           get_nprocs_conf(), get_nprocs());
    parse_opt(argc,argv);
    if (run_daemon)
    {
        printf("run daemon\n");
        daemon(0, 0);
    }
    for (i = 1; i < get_nprocs(); i++)
    {
        pthread_t cpu_thread;
        pthread_create(&cpu_thread, NULL, cpu_pi, NULL);
    }

    //main thead
    cpu_pi(NULL);

    return 0;
}