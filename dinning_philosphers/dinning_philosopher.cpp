#include<bits/stdc++.h>
#include<unistd.h>
#include<thread>
#include<semaphore.h>
using namespace std;

#define N 5

sem_t chopsticks[5];

void Philospher(int pno){
	while(1){

		sem_wait(&chopsticks[pno%5]);
			sem_wait(&chopsticks[(pno+1)%5]);

				// cs

				cout<<"Philospher "<<pno<<" is eating"<<endl;
				sleep(2);
			sem_post(&chopsticks[(pno+1)%5]);
		sem_post(&chopsticks[pno%5]);
	}
}

void Philospher_Last(int pno){
	while(1){
		sem_wait(&chopsticks[(pno+1)%5]);
			sem_wait(&chopsticks[pno%5]);
				cout<<"Philospher "<<pno<<" is eating"<<endl;
				sleep(2);
			sem_post(&chopsticks[pno%5]);
		sem_post(&chopsticks[(pno+1)%5]);

	}
}

int main(){
	int i;

	for(i=0;i<N;i++)
		sem_init(&chopsticks[i],0,1);
	thread P[N];

	for(i=0;i<N-1;i++)
		P[i]=thread(Philospher,i+1);

	P[N-1]=thread(Philospher,N);

	for(i=0;i<N;i++)
		P[i].join();

	return 0;

}