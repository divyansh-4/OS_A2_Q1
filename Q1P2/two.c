#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<stdlib.h>
#include<sched.h>
#include<pthread.h>
#include<time.h>
#define BILLION  1000000000L;
int main(){
    struct timespec start, stop;
    double elapsed1;
    double elapsed2;
    double elapsed3;
    int a=fork();
    if(a==0){
	pid_t selfpid=getpid();
	struct sched_param strpar;
	strpar.sched_priority=0;
	sched_setscheduler(selfpid,SCHED_OTHER,&strpar);
        execl("./kern1.sh","./kern1.sh",NULL);
    }
    else{        
        clock_gettime( CLOCK_REALTIME, &start);
	wait(NULL);
	clock_gettime( CLOCK_REALTIME, &stop);
        elapsed1 = ( stop.tv_sec - start.tv_sec ) + (double) ( stop.tv_nsec - start.tv_nsec )/BILLION;
        printf("%lf seconds elapsed in other \n", elapsed1);
        int b=fork();
        if(b==0){
		pid_t selfpid=getpid();
		struct sched_param strpar;
		strpar.sched_priority=20;
		sched_setscheduler(selfpid,SCHED_RR,&strpar);
	        execl("./kern2.sh","./kern2.sh",NULL);        
        }
        else{           
		clock_gettime( CLOCK_REALTIME, &start);
		wait(NULL);
		clock_gettime( CLOCK_REALTIME, &stop);
       		elapsed2 = ( stop.tv_sec - start.tv_sec ) + (double) ( stop.tv_nsec - start.tv_nsec )/BILLION;
       		printf("%lf seconds elapsed in RR \n", elapsed2); 
        	int c=fork();
                if(c==0){
                	pid_t selfpid=getpid();	
			struct sched_param strpar;
			strpar.sched_priority=20;
			sched_setscheduler(selfpid,SCHED_FIFO,&strpar);
			execl("./kern3.sh","./kern3.sh",NULL);   
                }
                else{ 
        		clock_gettime( CLOCK_REALTIME, &start);
			wait(NULL);
			clock_gettime( CLOCK_REALTIME, &stop);
        		elapsed3 = ( stop.tv_sec - start.tv_sec ) + (double) ( stop.tv_nsec - start.tv_nsec )/BILLION;
        		printf("%lf seconds elapsed in FIFO \n", elapsed3);       
                
                }    

            }
    }
	printf("%lf seconds elapsed in other \n", elapsed1);
	printf("%lf seconds elapsed in RR \n", elapsed2);
	printf("%lf seconds elapsed in FIFO \n", elapsed3);
}

