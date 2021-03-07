struct process{
	int pid;
	int priority;
	int arrivalTime;
	int responceTime = -1;
	int start = 0;
	int end = 0;
	int totalBurst = 0;
	vector< vector< int > > oper;
};

struct process currCpu,currInp,currOut,nullProc;
void initnullProc(){
	nullProc.pid = -1;
	nullProc.priority = -1;
	nullProc.arrivalTime = 1000000;
	currCpu = currOut = currInp = nullProc; 
}
vector < struct process > cpu;
vector < struct process > inp;
vector < struct process > out;
vector < struct process > processBuffer;
vector < struct process > endFiles;


vector< struct process > inpbuff;
vector< struct process > outbuff;
vector< struct process > cpubuff;


vector < struct process > inputProcess;

int currTime = 0;
int numOfProc;
int quantVal;
int tempQuant = 0;

void clearGlobalArr(){
	cpu.clear();
	inp.clear();
	out.clear();
	processBuffer.clear();
	endFiles.clear();
	inpbuff.clear();
	outbuff.clear();
	cpubuff.clear();
	currTime = 0;
}

void printQueue(){
	int i = 0;
	cout<<currTime<<endl;
	cout<<currCpu.pid<<endl <<currInp.pid<<endl<<currOut.pid;
	cout<<endl <<"CPU queue:-  ";
	for( i = 0;i<cpu.size();i++){
		cout<<cpu[i].pid<<" "; 
	}
	cout<<endl <<"OUT queue:-  ";
	for( i =0;i<out.size();i++){
		cout<<out[i].pid<<" "; 
	}
	cout<<endl <<"inp queue:-  ";
	for( i =0;i<inp.size();i++){
		cout<<inp[i].pid<<" "; 
	}
	cout <<endl;
}