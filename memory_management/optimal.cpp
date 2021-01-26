#include "read_file.cpp"

int search(pair<int,int> frame[],int num){           //function to search the element 

	for(int i=0;i<pageSize;i++)
		if(frame[i].first==num)
			return i;
		return -1;
}
int search_not_used_longest(pair<int,int> frame[]){ //function to find the element which is not used longest
	int i,j;
	int min=INT_MAX;
	for(i=0;i<pageSize;i++){
		if(frame[i].second<min){
			min=frame[i].second;
			j=i;
		}
	}
	return j;
}

void optimal(pair<int,int> frame[]){
	//cout<<"1"<<endl;
	int count=0;
	int j=0;
	int x=0;
	int t=1;
	//cout<<"2"<<endl;
	for(int i=0;i<pages.size();i++){
		//cout<<"3"<<endl;
		int index;
		index=search(frame,pages[i]);
		if(index!=-1){
			//cout<<"4"<<endl;
			hits.push_back(pages[i]);
			frame[i].second=t;
			//cout<<"5"<<endl;
		}
		else{
			//cout<<"6"<<endl;
			miss.push_back(pages[i]);
			if(x<pageSize){
				j=x;
				x++;
			}
			else
				j=search_not_used_longest(frame);

			frame[j].first=pages[i];
			frame[j].second=t;
			//cout<<"7"<<endl;
		}
		count++;
		if(count==25 || i==pages.size()-1){
			//cout<<"8"<<endl;
			cout<<"Current frame is: \n";
			for(int k=0;k<pageSize;k++)
				cout<<frame[k].first<<" ";
			cout<<endl;
			//cout<<"9"<<endl;
			//print(frame);
			output();
			cout<<endl;
			count=0;
			
		}
		t++;
	}

}

int main(){

	Read_File("refrence.dat");
	conversion();
	cout<<"frame size="<<pageSize<<endl;
	cout<<"no of pages="<<pages.size()<<endl;
	print(pages);
	pair<int,int> frame[pageSize];
	//cout<<"-1"<<endl;
	for(int i=0;i<pageSize;i++){
		frame[i].first=-1;
		frame[i].second=0;
	//	cout<<":::"<<endl;
	}
	//cout<<"455"<<endl;
	optimal(frame);
	cout<<"complete"<<endl;
	return 0;
}