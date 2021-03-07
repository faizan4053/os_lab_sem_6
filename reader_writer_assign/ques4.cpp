#include <iostream>
#include <unistd.h>
#include <sys/mman.h>
#include <thread>
using namespace std;

const int N=12; 
static int *val;

  
enum pstate {IDLE, WAITING,ACTIVE} flags[N];
int turn; 

void EntryProtocol(int i){	
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

}

void ExitProtocol(int i){
	 
	int  index = (turn+1)%N;
	while(flags[index]==IDLE){
		index=(index+1)%N;
	}	
	
	turn = index;
	
	// we are done 
	flags[i] = IDLE;
	
	printf("PROCESS -%d is IDLE !\n",i);
	// REMAINDER SECTION 
	
}

void NProcess(int i){
	EntryProtocol(i);
	// CRITICAL SECTION
	cout<<"\nPROCESS-"<<i<<" ENTERED CS!"<<endl;	
	*val = *val + 10;
	cout<<"PROCESS - "<<i<<": value = "<<*val<<endl;
	cout<<"PROCESS-"<<i<<" EXITED CS!"<<endl<<endl;
	ExitProtocol(i);
}

int main(){
	// shared variable  for N processes	
	val = static_cast<int*>(mmap(NULL, sizeof *val, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0));
	*val = 20;
	srand(time(0));
	
	cout<<"Total no of processes = "<<N<<endl;
	cout<<"INITIAL VALUE OF SHARED VARIABLE = "<<*val<<endl;

	turn = rand()%N;
	cout<<"turn = "<<turn<<endl;
	
	thread tid[N];
	// initialising all processes as idle 
	for (int i = 0; i < N; i++) {
		flags[i] = IDLE;
	}
	tid[turn] = thread(NProcess,turn);
	int x = turn;
	for (int i = 0; i < N; i++) {
		if (i==x){
			cout<<"hi";
			continue;
		}
		else
			tid[i] = thread(NProcess, i);
	}
	
	for (int i = 0; i < N; i++) {
		tid[i].join();
	}
	cout<<"THE VALUE AT THE END OF ALL PROCESSES = "<<*val<<endl;

	return 0;
}


