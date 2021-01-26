#include<bits/stdc++.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/mman.h>
using namespace std;

static int* val;
static bool *P1_wantstoEnter,*P2_wantstoEnter;
static int *favouredProcess;

int sum=0;

void Process1(){

	*P1_wantstoEnter=true;
	*favouredProcess==2;
		while(*P2_wantstoEnter && *favouredProcess==2)
						sleep(10);
				cout<<"\nprocess "<<1<<" is in critical section"<<endl;
	// CRITICAL SECTION
				*val=*val+20;
				cout<<"Updated value after the execution of process"<<1<<": value = "<<*val<<endl;
				cout<<"\nprocess "<<1<<" is out of critical section"<<endl;
				*P1_wantstoEnter=false;

	//cout<<*val<<endl;
}

void Process2(){

	*P2_wantstoEnter=true;
	*favouredProcess==1;
		while(*P1_wantstoEnter && *favouredProcess==1)
						sleep(10);
				
				cout<<"\nprocess "<<2<<" is in critical section"<<endl;// CRITICAL SECTION
				*val=*val+20;
				cout<<"Updated value after the execution of process"<<2<<": value = "<<*val<<endl;
				cout<<"\nprocess "<<2<<" is out of critical section"<<endl;
				//sum+=val;
				*P2_wantstoEnter=false;
	
}

int main(){

	//bool P1_wantstoEnter=false,P2_wantstoEnter=false;
	//int favouredProcess=1;

	val = static_cast<int*>(mmap(NULL, sizeof *val, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0));
	favouredProcess = static_cast<int*>(mmap(NULL, sizeof *favouredProcess, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0));
	P1_wantstoEnter = static_cast<bool*>(mmap(NULL, sizeof *P1_wantstoEnter, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0));
	P2_wantstoEnter = static_cast<bool*>(mmap(NULL, sizeof *P2_wantstoEnter, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0));

	*favouredProcess=1;
	*P1_wantstoEnter=false;
	*P2_wantstoEnter=false;
	
	*val=10;
	//sum+=val;
	int id=fork();
	if(id<0){
		cout<<"processes are not created"<<endl;
		exit(0);
	}
	else if(id==0){
		Process1();
	}
	else{
		Process2();
	}

	return 0;
}

