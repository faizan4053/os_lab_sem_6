#define f first
#define s second
#define pb push_back
#define mkp make_pair
const int weight[40] = {
/*-20 */ 88761, 71755, 56483, 46273, 36291,
/*-15 */ 29154, 23254, 18705, 14949, 11916,
/*-10 */ 9548, 7620, 6100, 4904, 3906,
/* -5 */ 3121, 2501, 1991, 1586, 1277,
/*  0 */ 1024,820,655,526,423,
/*  5 */ 335,272,215,172,137,
/* 10 */ 110,87,70,56,45,
/* 15 */ 36,29,23,18,15}; 
class process{
	public:
	int pid,arr=0,pri,rem=0,comp,ftime,tot=0,sched=0,vrun=0,run=0,nice,time_slice;
	vector<pair<char,int>>des;
	vector<pair<char,int>>::iterator opr;	
};
class compare{
    public:
        bool operator()(vector<process>::iterator a,vector<process>::iterator b){
            if(a->vrun<b->vrun)return true;
            else if(a->vrun==b->vrun){
                if(a->nice<b->nice)return true;
                else if(a->nice==b->nice)return a->pid<b->pid;
                else return false;
            }            
            else return false;
        }
};
bool comp(process p1,process p2){
	if(p1.nice<p2.nice)return true;
    else if(p1.nice==p2.nice)return p1.pid<p2.pid;
	else return false;
}
void output(deque<vector<process>::iterator>inp,string s){
	cout<<s;
	for(auto i:inp)cout<<"["<<(*i).pid<<":"<<(*i).rem<<"] ";
	cout<<endl;
}
void output(set<vector<process>::iterator,compare>inp,string s){
	cout<<s;
	for(auto i:inp)cout<<"["<<(*i).pid<<":"<<(*i).opr->s<<"] ";
	cout<<endl;
}
void output(vector<process>input){
	int tat=0,tt,rtt=0,rt,wtt=0,wt;
	for(auto i=input.begin();i!=input.end();i++){
		tt=i->comp - i->arr;
		rt=i->ftime - i->arr;
		wt=tt - i->tot;
		cout<<"Pid: "<<i->pid<<" Turnaround Time: "<<tt<<" Response Time: "<<rt<<" Waiting Time: "<<wt<<endl;
		tat+=tt; rtt+=rt; wtt+=wt;		
	}
	cout<<"Average Turnaround Time: "<<1.0*tat/input.size()<<endl;
	cout<<"Average Response Time: "<<1.0*rtt/input.size()<<endl;
	cout<<"Average Waiting Time: "<<1.0*wtt/input.size()<<endl;
}