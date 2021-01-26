#include <regex>
#include <thread>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;
#include "shared.cpp"
#include "fcfs.cpp"
#include "sjf.cpp"
#include "srtf.cpp"
#include "ppe.cpp"
#include "pnpe.cpp"
#include "roundrobin.cpp"

void storeProcesses(string line){
	
	stringstream in(line);
	struct process temp;


	in >> temp.pid;
	// cout<<temp.pid;
	in >> temp.priority;
	// cout<<temp.priority;
	in >> temp.arrivalTime;
	// cout<< temp.arrivalTime;
	string st ;
	in >> st;
	int burst;
	while(st != "-1"){
		// cout<<st;
		if(st== "P"){
			in >> burst;
			vector<int> ar{1,burst};
			temp.oper.push_back(ar);
		}else if(st == "I"){
			in >> burst;
			vector<int> ar{2,burst};
			temp.oper.push_back(ar);
		}else {
			in >> burst;
			vector<int> ar{3,burst};
			temp.oper.push_back(ar);
		}
		
		temp.totalBurst += burst;
		// cout<<burst;
		in >> st ;

	}
	inputProcess.push_back(temp);

}


bool cmp(struct process p1,struct process p2){

	return p1.arrivalTime < p2.arrivalTime;
}

int main(){

	fstream inputFile;

	inputFile.open("input.dat");

	string line,temp;

	


	if(inputFile.is_open()){
		getline(inputFile,line);
		stringstream in(line);
		in >> numOfProc;
		// cout<<numOfProc<<endl;
	}
	else{
		cout<<"input.dat filenot found please provide the appropriate file"<<endl;
		return 0;
	}

	getline(inputFile,line);
	stringstream in(line);
	in >> quantVal;
	// cout << quantVal <<endl;
	int i = 0;
	while(i++<numOfProc){
		getline(inputFile,line);
		storeProcesses(line) ;
	}

	sort(inputProcess.begin(),inputProcess.end(),cmp);
	FCFS(inputProcess);
	clearGlobalArr();
	SJF(inputProcess);

	clearGlobalArr();
	SRTF(inputProcess);
	clearGlobalArr();
	PPE(inputProcess);
	clearGlobalArr();
	PNPE(inputProcess);
	clearGlobalArr();
	RR(inputProcess);
	return 0;
}