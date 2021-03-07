struct process{
	int pid;
	int priority;
	int arrivalTime;
	int responceTime = -1;
	int start = 0;
	int end = 0;
	int currPriority;
	int totalBurst = 0;
	int currQuant = 0;
	int currDownT = 0;

	vector< vector< int > > oper;
};

vector < vector < struct process > > queues;
vector < struct process > inp;
vector < struct process > out;
vector < struct process > processBuffer;
vector < struct process > endFiles;
vector < struct process > inputProcess;
vector < int > quant; 

vector< struct process > inpbuff;
vector< struct process > outbuff;
vector< struct process > cpubuff;


int currTime = 0;
int numOfProc;
int numOfQueues;
int downT,upT;
int tempUpT = 0;
void initQueues(int q){
	vector< struct process > temp;
	for ( int i = 0; i<q;i++){
		queues.push_back(temp);
		quant.push_back(-1);
	}

}

void printQueue(){
	int i = 0, j = 0;
	cout << "Current time: " << currTime<<endl;

	for( i = 0; i < queues.size(); i++){

		cout<<"Queue No: "<<i<<": ";
		for(j = 0;j<queues[i].size();j++){
			cout << queues[i][j].pid<<" "; 
		}
		cout << endl;
	}
	cout << endl;
}