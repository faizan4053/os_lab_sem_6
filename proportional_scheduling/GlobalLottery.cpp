struct process{
	int pid = -1;
	int cpuShare ;
	int responceTime = -1;
	int ticketAssigned;
	int pass = 0;
	int start;
	int stride = 0;
	int end = 0;
	int totalBurst = 0;
	vector< vector< int > > oper;
};
int resch = 0;
int numOfTickets;
int numOfProc;
int largeNumber;
int currTime = 0;
int currTicketMax = 0;
vector < struct process > inp;
vector < struct process > out;
vector < struct process > processBuffer;
vector < struct process > endFiles;
vector < struct process > inpbuff;
vector < struct process > outbuff;
vector < struct process > cpubuff;
vector < int > tickets;

vector < struct process > inputProcess;

void initTickets(int numOfTickets){
	for(int i = 0;i< numOfTickets;i++){
		tickets.push_back(-1);
	}
}
void clearGlobalArr(){
	inp.clear();
	out.clear();
	processBuffer.clear();
	endFiles.clear();
	inpbuff.clear();
	outbuff.clear();
	cpubuff.clear();
	currTime = 0;
}
void printT(){
	cout<<endl <<"ticket queue:-  ";
	for(int i =0;i<tickets.size();i++){
		cout<<tickets[i]<<" "; 
	}cout<<endl;
}

void printQueue(){
	int i = 0;
	cout<<currTime<<endl;
	cout<<endl <<"process queue:-  ";
	for( i =0;i<out.size();i++){
		cout<<processBuffer[i].pid<<" "; 
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