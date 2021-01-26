//Mohammad faizan 2017ucp1202

#include<bits/stdc++.h>
#include<stdlib.h>
#include<unistd.h>
#include<fstream>

using namespace std;

typedef struct process{
	int arrival;
	int size;
	int valid;
	string status;
}P;

int memSize;

vector<P *> v;


void read(){
	string line;
	ifstream fin;
	int s,a,b,c;

// by default open mode = ios::in mode
	fin.open("alloc.dat");
	
	getline(fin,line);
	stringstream in(line);
	in>>s;
	memSize=s;
	cout<<s<<endl;
	while(fin){
		getline(fin, line);
		stringstream in(line);
		in>>a;
		in>>b;
		in>>c;
		if(a==-1 && b==-1 && c==-1)
			break;
		P *t=(P*)malloc(sizeof(P));
		t->arrival=a;
		t->size=b;
		t->valid=c;
		t->status="not allocated";
		//cout<<t->arrival<<" "<<t->size<<" "<<t->valid<<" "<<endl;
		v.push_back(t);
	}
}

void print(int n){
	cout<<"Process with arrival time and aloocation status\n";
	cout<<"	Arrives at"<<"		"<<"Status"<<endl;
	cout<<"	---------------------------------"<<endl;
	for(int i=0;i<=n;i++){
		cout<<"	"<<v[i]->arrival<<"			"<<v[i]->status<<endl;
	}
	cout<<"	---------------------------------"<<endl;
	cout<<endl;

}

