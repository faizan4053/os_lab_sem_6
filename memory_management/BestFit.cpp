//Mohammad faizan 2017ucp1202

#include "read.cpp"

int initial_Mem;
int successful_allocation=0;
int allocation=0;
bool compare(P *a,P *b){
	return a->size<b->size;
}
vector<pair<pair<int,int>,pair<int,int>>> m;
void best_fit(){
	int t=0;
	int i;
	for(i=0;i<v.size();i++){
		if(v[i]->size<=initial_Mem){
			initial_Mem-=v[i]->size;
			successful_allocation+=v[i]->size;
			v[i]->status="allocated";
			m.push_back({{v[i]->arrival,v[i]->size},{v[i]->valid,0}});
		}
		//t+=v[i]->arrival;
		t++;
		
		for(int k=0;k<m.size();k++){
			if(m[k].second.second==m[k].second.first){
				initial_Mem+=m[k].first.second;
				m.erase(m.begin()+k);
			}
			else{
				m[k].second.second++;
			}
		}
		allocation+=v[i]->size;
		if(t>=50 || i==v.size()-1){
			print(i);
			cout<<"Percentage of successful allocation is "<<(float)(successful_allocation)/((float)(successful_allocation+allocation))*100;
			cout<<endl;
			cout<<"\nMemory remaining is "<<initial_Mem<<endl;

			t=0;
		}
	}
}

int main(){
	read();
	initial_Mem=memSize;
	cout<<"Initial Memory is "<<initial_Mem<<endl;
	sort(v.begin(),v.end(),compare);
	int i;
	for(i=0;i<v.size();i++){
		cout<<v[i]->size<<" ";
	}
	cout<<endl;
	best_fit();
	return 0;
}