#include "read_file.cpp"


int search(int frame[],int num){

	for(int i=0;i<pageSize;i++)
		if(frame[i]==num)
			return 1;
		return 0;
}

void fcfs(int frame[]){
	//cout<<"1"<<endl;
	int count=0;
	int j=0;
	//cout<<"2"<<endl;
	for(int i=0;i<pages.size();i++){
		//cout<<"3"<<endl;
		if(search(frame,pages[i])==1){
			//cout<<"4"<<endl;
			hits.push_back(pages[i]);
			//cout<<"5"<<endl;
		}
		else{
			//cout<<"6"<<endl;
			miss.push_back(pages[i]);
			frame[j]=pages[i];
			j=(j+1)%pageSize;
			//cout<<"7"<<endl;
		}
		count++;
		if(count==25 || i==pages.size()-1){
			//cout<<"8"<<endl;
			cout<<"Current frame is: \n";
			for(int k=0;k<pageSize;k++)
				cout<<frame[k]<<" ";
			cout<<endl;
			//cout<<"9"<<endl;
			//print(frame);
			output();
			cout<<endl;
			count=0;
			
		}
		
	}

}

int main(){

	Read_File("refrence.dat");
	conversion();
	cout<<"frame size="<<pageSize<<endl;
		cout<<"no of pages="<<pages.size()<<endl;
	print(pages);
	int frame[pageSize];
	memset(frame,-1,sizeof(frame));
	fcfs(frame);

	return 0;
}