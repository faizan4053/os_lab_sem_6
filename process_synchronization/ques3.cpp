#include "Search_Insert_Delete.cpp"


//Mohammad Faizan 2017ucp1202 


int main(){
	srand(time(0));

	init();
	int i,a;
	int insertions,deletions,finds;
	cout<<"Enter the no of insetions,deletions and searches\n";
	cin>>insertions>>deletions>>finds;
	
	thread t_in[insertions],t_de[deletions],t_s[finds];
	for(i=0;i<insertions;i++){
		t_in[i]=thread(insertion,rand()%N);
	}
	 for(i=0;i<finds;i++){
		 t_s[i]=thread(searches,rand()%N);
	 }
	for(i=0;i<deletions;i++){
		t_de[i]=thread(deletion,rand()%N);
	}
	for(i=0;i<insertions;i++){
		t_in[i].join();
	}
	 for(i=0;i<finds;i++){
		 t_s[i].join();
	 }
	for(i=0;i<deletions;i++){
		t_de[i].join();
	}
	cout<<"final list"<<endl;
	print();
	return 0;
}
