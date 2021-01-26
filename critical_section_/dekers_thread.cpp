#include <bits/stdc++.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <pthread.h> 
#define NO_OF_THREADS 1

using namespace std;

int g = 0; 

bool P1_wantstoEnter=false,P2_wantstoEnter=false;
int favouredProcess=1;

void *Process2(void *vargp) 
{ 
	// int *myid = (int *)vargp;
	// cout<<*myid<<endl; 

	P2_wantstoEnter=true;
		while(P1_wantstoEnter){
			if(favouredProcess==1){
				P2_wantstoEnter=false;
				while(favouredProcess==1)
						sleep(2);

				P2_wantstoEnter=true;
		}
	}
	cout<<"\nprocess "<<1<<" is in critical section"<<endl;
	// CRITICAL SECTION
	g+=25;
	cout<<"Updated value after the execution of process"<<1<<": value = "<<g<<endl;
	cout<<"\nprocess "<<1<<" is out of critical section"<<endl;
	favouredProcess=1;
	P2_wantstoEnter=false;
} 

void *Process1(void *vargp) 
{ 
	// int *myid = (int *)vargp;
	// cout<<*myid<<endl; 

		P1_wantstoEnter=true;
		while(P2_wantstoEnter){
			if(favouredProcess==2){
				P1_wantstoEnter=false;
				while(favouredProcess==2)
						sleep(2);

				P1_wantstoEnter=true;
		}
	}
	cout<<"\nprocess "<<1<<" is in critical section"<<endl;
	// CRITICAL SECTION
	g+=20;
	cout<<"Updated value after the execution of process"<<1<<": value = "<<g<<endl;
	cout<<"\nprocess "<<1<<" is out of critical section"<<endl;
		
	//cout<<"\nThread ID:"<<1<<"  g= "<<g<<endl;
	favouredProcess=2;
	P1_wantstoEnter=false;
} 

int main() 
{ 
	int i; 
	pthread_t tid1[NO_OF_THREADS],tid2[NO_OF_THREADS]; 

	// Let us create three threads 
	for (i = 0; i < NO_OF_THREADS; i++) {
		pthread_create(&tid1[i], NULL, Process1, NULL); 
		pthread_create(&tid2[i],NULL,Process2,NULL);
	}
	for (i = 0; i < NO_OF_THREADS; i++){
		pthread_join(tid1[i], NULL);
		pthread_join(tid2[i], NULL);
	}

	return 0; 

} 
