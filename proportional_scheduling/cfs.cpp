#include<bits/stdc++.h>
using namespace std;
#include "GlobalCfs.cpp"
int main(){
    int sum=accumulate(weight,weight+40,0);
	fstream file;
	file.open("cfs.dat",ios::in);
	int n,sched_latency,min_granularity;
	file>>n>>sched_latency>>min_granularity;
	vector<process>input;
	for(int i=0;i<n;i++){
		process p;
		file>>p.pid; file>>p.nice;
        if(p.nice==45)file>>p.nice , p.nice=-p.nice;
		char typ='+'; int time;	
		while(typ!='-'){
			file>>typ; file>>time;
			if(typ=='-')break;	
			p.des.pb(mkp(typ,time));
			p.tot+=time;
		}
        p.time_slice=max(min_granularity,(weight[p.nice+20]*sched_latency)/sum);
        // cout<<p.pid<<" "<<p.time_slice<<endl;
		input.pb(p);		
	}
    sort(input.begin(),input.end(),comp);
	for(int i=0;i<input.size();i++)input[i].opr=input[i].des.begin();
	deque<vector<process>::iterator>ind,outd;
    set<vector<process>::iterator,compare>cpu;
	int time=0,count=input[0].time_slice;
	auto it=input.begin();
	while(!cpu.empty() or !ind.empty() or !outd.empty() or it!=input.end()){
		if(!ind.empty()){
			auto j=ind.begin();
			(*j)->rem-=1;
			if((*j)->rem<0){
                (*j)->opr++;
				if((*j)->opr->f=='P'){
					if(!cpu.empty()){
                        auto r=cpu.begin();
                        (*j)->vrun=(*r)->vrun;
                    }
                    cpu.insert(*j);
				}
				else if((*j)->opr->f=='O'){
					(*j)->rem=(*j)->opr->s;				
					outd.pb(*j);
				}
				ind.pop_front();
			}
		}
		if(!outd.empty()){
			auto j=outd.begin();
			(*j)->rem-=1;
			if((*j)->rem<0){
                (*j)->opr++;
				if((*j)->opr->f=='P'){
                    if(!cpu.empty()){
                        auto r=cpu.begin();
                        (*j)->vrun=(*r)->vrun;
                    }
					cpu.insert(*j);
				}
				else if((*j)->opr->f=='I'){
					(*j)->rem=(*j)->opr->s;
					if(ind.empty()) (*j)->rem--;
					ind.pb(*j);
				}
				outd.pop_front();
			}
		}
		while(it->arr==time && it!=input.end()){
			it->rem=it->opr->s;
			cpu.insert(it);
			it++;
		}
		if(!cpu.empty()){
			auto j=cpu.begin();
            if(count<=0 && (*j)->opr->s!=0)count=(*j)->time_slice;
			if((*j)->sched==0){
				(*j)->sched++;
				(*j)->ftime=time;
			}		
			(*j)->opr->s-=1;
            (*j)->run++;
            count--;
            if(count==0){
                if((*j)->opr->s > 0){    
                    (*j)->vrun+=weight[0]*((*j)->run)/weight[(*j)->nice+20];
                    cpu.erase(j);
                    cpu.insert(*j);
                }   
                if(!cpu.empty()){ 
                    auto r=cpu.begin();
                    count=(*r)->time_slice;
                }
                //else count--;
            }
			if((*j)->opr->s<0){
                (*j)->run--;
                (*j)->opr++;
                if((*j)->opr->f=='I'){
					(*j)->rem=(*j)->opr->s;
					if(ind.empty()) (*j)->rem--;
					ind.pb(*j);
				}
				else if((*j)->opr->f=='O'){
					(*j)->rem=(*j)->opr->s;
					if(outd.empty()) (*j)->rem--;
					outd.pb(*j);
				}
				else (*j)->comp=time;
				cpu.erase(j);
				if(!cpu.empty()){
					auto r=cpu.begin();
                    count=(*r)->time_slice;
					if((*r)->sched==0){
						(*r)->sched++;
						(*r)->ftime=time;
					}		
					(*r)->opr->s-=1;
                    (*r)->run+=1;
                    count--;
				}
			}
		}
		// cout<<"TIME: "<<time<<endl;
		// output(ind,"Input Device Queue: ");
		// output(outd,"Output Device Queue: ");
		// output(cpu,"CPU Queue: ");
		// cout<<endl;
		time+=1;		
	}
	output(input);		
	return 0;	
}