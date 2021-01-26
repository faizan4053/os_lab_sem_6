#include<bits/stdc++.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/mman.h>
using namespace std;

static int* val;
static int* favouredProcess;
static bool* P1_wantstoEnter,*P2_wantstoEnter;
int sum=0;

void Process1(){

	*P1_wantstoEnter=true;
		while(*P2_wantstoEnter){
			if(*favouredProcess==2){
				*P1_wantstoEnter=false;
				while(*favouredProcess==2)
						sleep(10);

				*P1_wantstoEnter=true;
		}
	}
	//*val=*val+5;
	//cout<<*val<<endl;
	cout<<"\nprocess "<<1<<" is in critical section"<<endl;
	// CRITICAL SECTION
	*val = *val + 30;
	cout<<"Updated value after the execution of process"<<2<<": value = "<<*val<<endl;
	cout<<"\nprocess "<<1<<" is out of critical section"<<endl;
	//sum+=val;
	*favouredProcess=2;
	*P1_wantstoEnter=false;
	
}

void Process2(){

	*P2_wantstoEnter=true;
		while(*P1_wantstoEnter){
			if(*favouredProcess==1){
				*P2_wantstoEnter=false;
				while(*favouredProcess==1)
						sleep(10);

				*P2_wantstoEnter=true;
		}
	}
	//*val=*val+4;//critical section
	//cout<<*val<<endl;
	cout<<"\nprocess "<<2<<" is in critical section"<<endl;
	// CRITICAL SECTION
	*val = *val + 20;
	cout<<"Updated value after the execution of process"<<2<<": value = "<<*val<<endl;
	cout<<"\nprocess "<<2<<" is out of critical section"<<endl;
	//sum+=val;
	*favouredProcess=1;
	*P2_wantstoEnter=false;
	
}

int main(){

	
	val = static_cast<int*>(mmap(NULL, sizeof *val, PROT_READ | PROT_WRITE,MAP_SHARED | MAP_ANONYMOUS, -1, 0));
	favouredProcess = static_cast<int*>(mmap(NULL, sizeof *favouredProcess, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0));
	P1_wantstoEnter = static_cast<bool*>(mmap(NULL, sizeof *P1_wantstoEnter, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0));
	P2_wantstoEnter = static_cast<bool*>(mmap(NULL, sizeof *P2_wantstoEnter, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0));
	

	*P1_wantstoEnter=false;
	*P2_wantstoEnter=false;
	*favouredProcess=1;


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
	//cout<<sum<<endl;

	return 0;
}

