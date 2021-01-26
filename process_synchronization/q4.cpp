//Mohammad Faizan  2017UCP1202


#include <iostream>
#include <unistd.h>
#include <sys/mman.h>
#include <thread>
#define N 10
using namespace std;

static int *val;

  
enum pstate {IDLE, WAITING,ACTIVE};
pstate flags[N];
int turn; 

void init(){
	*val=100;
	turn = rand()%N;
	for (int i = 0; i < N; i++) {
		flags[i] = IDLE;
	}
}


void Process(int i){
	int index;
	do{
		
		flags[i] = WAITING;		
		
		index = turn; 
		while(index!=i){
			if (flags[index] != IDLE)
				index = turn;
			else 
				index = (index+1)%N; // circular queue of N processes
		}
		
		flags[i] = ACTIVE;
		
		
		index = 0;
		while((index < N) && ((index == i) || (flags[index] != ACTIVE))){
			index+=1;
		}

	}while (!((index >= N) && ((turn == i) || (flags[turn] == IDLE))));
	
	
	turn = i;	
	// CRITICAL SECTION
	cout<<"\nProcess "<<i<<" ENTERED CS!"<<endl;	
	*val = *val + 100;
	cout<<"PROCESS - "<<i<<": value = "<<*val<<endl;
	cout<<"PROCESS-"<<i<<" EXITED CS!"<<endl<<endl;

	  index = (turn+1)%N;
	while(flags[index]==IDLE){
		index=(index+1)%N;
	}	
	
	turn = index;
	
	// we are done 
	flags[i] = IDLE;
	
	printf("PROCESS -%d is IDLE !\n",i);
}

int main(){

	val = static_cast<int*>(mmap(NULL, sizeof *val, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0));
	srand(time(0));

	init();
	
	cout<<"No of threads = "<<N<<endl;
	cout<<"Initial value of shared variable = "<<*val<<endl;

	
	cout<<"turn = "<<turn<<endl;
	
	thread tid[N];
	
	tid[turn] = thread(Process,turn);
	int x = turn;
	for (int i = 0; i < N; i++) {
		if (i==x){
			cout<<"hi";
			continue;
		}
		else
			tid[i] = thread(Process, i);
	}
	
	for (int i = 0; i < N; i++) {
		tid[i].join();
	}
	cout<<"Final updated value of shared varibale is "<<*val<<endl;

	return 0;
}


