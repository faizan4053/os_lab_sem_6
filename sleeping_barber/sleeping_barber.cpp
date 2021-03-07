#include <bits/stdc++.h>
// include<iostream>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>
#include<time.h>

using namespace std;

#define N 10
sem_t customer,barber,seats;

int freeSeats=N;

void  * Barber(void *arg){
	while(1){
		sem_wait(&customer);
			sem_wait(&seats);

				freeSeats++;
				cout<<"new customer"<<endl;
				cout<<"freeSeats are "<<freeSeats<<endl;
			sem_post(&barber);
		sem_post(&seats);
		sleep(2);
	}

}

void * Customer(void *arg){
	while(1){
		sem_wait(&seats);
		if(freeSeats>0){
			freeSeats--;
			cout<<"donw with customer"<<endl;
			cout<<"freeSeats are "<<freeSeats<<endl;
			sem_post(&customer);
			sem_post(&seats);
			sem_wait(&barber);
		}
		else{
			sem_post(&seats);
		}
		sleep(2);
	}
}


int main(){
	int i;
	sem_init(&barber,0,0);
	sem_init(&customer,0,0);
	sem_init(&seats,0,1);

	pthread_t B,C[N];
	//B=thread(barber);
	pthread_create(&B,NULL,&Barber,NULL);
	for(i=0;i<N;i++){
		//C[i]=thread(customer);
		pthread_create(&C[i],NULL,&Customer,NULL);
	}


	//B.join();
	pthread_join(B,NULL);

	for(i=0;i<N;i++){
		//C[i].join();
		pthread_join(C[i],NULL);
	}

	return 0;
}
