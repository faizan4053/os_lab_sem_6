//Mohammad faizan 2017ucp1202

#include<bits/stdc++.h>
#include<stdlib.h>
#include<unistd.h>
#include<fstream>

using namespace std;

int pageSize;
string input;

vector<int> pages;
vector<int> hits;
vector<int> miss;


void Read_File(string fileName){
	fstream inputFile;


	int n;
	string st;

	inputFile.open("refrence.dat");

	string line;
	if(inputFile.is_open()){
		getline(inputFile,line);
		stringstream in(line);
		in >> n;
		getline(inputFile,line);
	}
	else
		cout<<"file not found\n";

		stringstream in(line);
		in >> st;
		pageSize=n;
		input=st;
		cout<<pageSize<<endl;
		cout<<input<<endl;

}

void conversion(){
	int s=input.size(),i;;
	for(i=0;i<s;i++){
		if(input[i]==',')
			continue;
		else if(input[i]=='-')
			break;
		else{
			int t=input[i]-'0';
			pages.push_back(t);
		}
	}
}

void print(vector<int> v){
	for(int i=0;i<v.size();i++)
		cout<<v[i]<<" ";
	cout<<endl;
}

void output(){
	cout<<"So far--\n";
	cout<<"hits are: ";
	print(hits);
	cout<<"Misses are: ";
	print(miss);
	int h=hits.size();
	int m=miss.size();
	cout<<"hits="<<h<<endl;
	cout<<"misses="<<m<<endl;
	cout<<"Hit Ratio = ";
	float hitratio=(float)h/((float)(h+m));
	cout<<hitratio<<endl;
}