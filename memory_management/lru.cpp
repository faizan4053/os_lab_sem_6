//mohammad faizan 2017ucp1202

//least recently used

#include "read_file.cpp"


int search(int frame[],int num){

	for(int i=0;i<pageSize;i++)
		if(frame[i]==num)
			return 1;
		return 0;
}

void lru(deque<int> q){
	//cout<<"1"<<endl;
	int count=0;
	int j=0;
	int x=0;
	//cout<<"2"<<endl;
	for(int i=0;i<pages.size();i++){
		//cout<<"3"<<endl;
		if(find(q.begin(),q.end(),pages[i])!=q.end()){
			//cout<<"4"<<endl;
			hits.push_back(pages[i]);
			//cout<<"5"<<endl;
		}
		else{
			//cout<<"6"<<endl;

			miss.push_back(pages[i]);
			if(x<pageSize){
				q.push_front(pages[i]);
				x++;
			}
			else{
				q.pop_back();
				q.push_front(pages[i]);
			}
			
			//cout<<"7"<<endl;
		}
		count++;
		if(count==25 || i==pages.size()-1){
			//cout<<"8"<<endl;
			cout<<"Current frame is: \n";
			for(auto it=q.begin();it!=q.end();it++)
					cout<<*it<<" ";
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
	deque<int> q;
	lru(q);

	return 0;
}