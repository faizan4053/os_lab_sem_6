#include<bits/stdc++.h>
#include "fun.h"
using namespace std;


int main(){
	
	shmid = shmget(cindexkey,sizeof(int),IPC_CREAT|0666);
	memory = shmat(shmid,NULL,0);
	cindex=(int *)memory;
	*cindex=0;

	shmid = shmget(pindexkey,sizeof(int),IPC_CREAT|0666);
	memory = shmat(shmid,NULL,0);
	pindex=(int *)memory;
	*pindex=0;

	shmid = shmget(itemkey,sizeof(int),IPC_CREAT|0666);
	memory = shmat(shmid,NULL,0);
	items=(int *)memory;
	*items=0;

	shmid = shmget(buffkey,sizeof(int)*n,IPC_CREAT|0666);

	memory = shmat(shmid,NULL,0);

	p=(int*)memory;
	for(int i=0;i<n;i++){
		p[i]=i;
	}

	retval = shmdt(p);
	shmdt(cindex);
	shmdt(pindex);
	shmdt(items);
	//cout<<"Hello YASHSB";

	//for check initialy semaphor works or not
	sem_t *sem_id = sem_open(semName, O_CREAT, 0600, 0);
    if (sem_id == SEM_FAILED){
        perror("Producer  : [sem_open] Failed\n"); exit(0);
    }
	if (sem_trywait(sem_id) < 0)
		printf("Process start\n");
	
	sem_post(sem_id);

	if(fork()==0){//Consumer code
		int i=0;
		while(i<5){
			ConsumerWait();
			shmid = shmget(cindexkey,sizeof(int),IPC_CREAT|0666);
			memory = shmat(shmid,NULL,0);
			cindex=(int *)memory;

			
			*cindex+1;

			sem_t *sem_id = sem_open(semName, O_CREAT, 0600, 0);
		    if (sem_id == SEM_FAILED){
		        perror("Consumer  : [sem_open] Failed\n");
		        exit(0);
		    }
			if (sem_wait(sem_id) < 0)
        		printf("Consumer wait for update item\n");
        	shmid = shmget(itemkey,sizeof(int),IPC_CREAT|0666);
			memory = shmat(shmid,NULL,0);
			items=(int *)memory;
			*items=*items-1;
			sleep(.9);
			printf("Consumer just update an item, Total items:%d\n",*items);
			shmdt(cindex);
			shmdt(items);
			sem_post(sem_id);
			i++;
		}
		exit(0);
	}
	else{//Producer Code
		int i=0;
		//int pid =fork();
		//int pid1=fork();
		while(i<15){
			ProducerWait();
			shmid = shmget(pindexkey,sizeof(int),IPC_CREAT|0666);
			memory = shmat(shmid,NULL,0);
			pindex=(int *)memory;

			shmid = shmget(buffkey,sizeof(int)*n,IPC_CREAT|0666);
			memory = shmat(shmid,NULL,0);
			p=(int*)memory;
			p[*pindex%n]=rand()%100;

			sem_t *sem_id = sem_open(semName, O_CREAT, 0600, 0);
		    if (sem_id == SEM_FAILED){
		        perror("Producer  : [sem_open] Failed\n"); exit(0);
		    }
			if (sem_wait(sem_id) < 0)
        		printf("Producer wait for update item\n");
        	//cout<<"HEllo Yashvendar";
        	*pindex+=1;
        	shmid = shmget(itemkey,sizeof(int),IPC_CREAT|0666);
			memory = shmat(shmid,NULL,0);
			items=(int *)memory;
			*items=*items+1;
			sleep(1);
			printf("Producer just update an item, Total items:%d\n",*items);
			shmdt(items);
			shmdt(p);
			sem_post(sem_id);
			i++;
		}
		exit(0);
	}
	exit(0);
}
