#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;
#include "GlobalLottery.cpp"
#include "Lottery.cpp"
#include "Stride.cpp"
void storeProcesses(string line){
	
	stringstream in(line);
	struct process temp;


	in >> temp.pid;
	// cout<<temp.pid<<endl;
	in >> temp.cpuShare;
	// cout << temp.cpuShare<<endl;
	string st ;
	in >> st;
	int burst;
	while(st != "-1"){
		// cout<<st;
		if(st== "P"){
			in >> burst;
			vector<int> ar{1,burst};
			temp.oper.push_back(ar);
			temp.totalBurst += burst;
		}else if(st == "I"){
			in >> burst;
			vector<int> ar{2,burst};
			temp.oper.push_back(ar);
		}else {
			in >> burst;
			vector<int> ar{3,burst};
			temp.oper.push_back(ar);
		}
		
		// cout<<burst<<endl;
		
		in >> st ;

	}
	inputProcess.push_back(temp);

}
int main(){

	fstream inputFile;

	inputFile.open("lottery.dat");

	string line,temp;	

	stringstream in;
	if(inputFile.is_open()){
		getline(inputFile,line);
		in << line;
		in >> numOfTickets;
		initTickets(numOfTickets);
		// printT();
		// cout << numOfTickets<<endl;
	}else{
		cout<<"lottery.dat filenot found please provide the appropriate file"<<endl;
		return 0;
	}

	in.str("");
	getline(inputFile,line);
	in<<line;
	in>>numOfProc;
	// cout<<numOfProc<<endl;

	in.str("");
	getline(inputFile,line);
	in<<line;
	in>>largeNumber;
	// cout<<largeNumber<<endl;

	int i = 0;
	while(i++<numOfProc){
		getline(inputFile,line);
		storeProcesses(line) ;
	}
	cout<<"Lottery"<<endl;
	Lottery(inputProcess);
	clearGlobalArr();
	cout<<endl<<"Stride"<<endl;
	Stride(inputProcess);

	return 0;
}