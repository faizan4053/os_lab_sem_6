#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h> 
#include <boost/algorithm/string.hpp>
using namespace std;


int main(){
    string line;
    //int fp=fopen("/proc/cpuinfo","r");
    fstream newfile;
    string tp;
    int ctxt,intr,btime,processes;
  string array[]={"MemTotal:","MemFree:","MemAvailable:","SwapTotal:","SwapFree:"};
  int MemTotal,MemFree,MemAvailable,SwapTotal,SwapFree;
    newfile.open("/proc/stat",ios::in);
    int k=0;
        if (newfile.is_open()){   
      
      while(getline(newfile, tp)){ 
        // for(string i:array){
            /*if(i==tp.substr(0, 9)){
                cout<<tp;
            }*/
            if(tp.find("cpu")!=string::npos){
                //cout<<tp<<endl;  
                vector<string> result;
                boost::split(result, tp, boost::is_any_of(" ")); 
               /* for(int i=0;i<result.size();i++){
                    cout<<result[i]<<endl;
                }*/
              /* cout<<result[0]<<endl;
               cout<<result[1]<<endl;
               cout<<result[2]<<endl;
               cout<<result[4]<<endl;
               cout<<result[5]<<endl;
               cout<<result[6]<<endl;*/
               float userTime=stoi(result[3])+stoi(result[2]);
	           float kernelTime=stoi(result[4]);
	           float idleTime=stoi(result[5]);
	           float totalTime = userTime+kernelTime+idleTime;
	           cout<<result[0]<<":"<<endl;
	           cout<<"\ttime spent in user mode: "<<userTime*100/totalTime<<" %"<<endl;
	           cout<<"\ttime spent in kernel mode: "<<kernelTime*100/totalTime<<" %"<<endl;
	           cout<<"\ttime spent ideally: "<<idleTime*100/totalTime<<" %"<<endl<<endl;
                         
            }
            
            if(tp.find("ctxt")!=string::npos){ 
                vector<string> result;
                boost::split(result, tp, boost::is_any_of(" ")); 
               ctxt=stoi(result[1]);
               //cout<<ctxt<<"HELLO"<<endl;
                         
            }
            
             
            if(tp.find("intr")!=string::npos){ 
                vector<string> result;
                boost::split(result, tp, boost::is_any_of(" ")); 
                intr=stoi(result[1]);
                         
            }
            
             
            if(tp.find("ctxt")!=string::npos){ 
                vector<string> result;
                boost::split(result, tp, boost::is_any_of(" ")); 
               ctxt=stoi(result[1]);
                         
            }
            
            if(tp.find("btime")!=string::npos){ 
                vector<string> result;
                boost::split(result, tp, boost::is_any_of(" ")); 
               btime=stoi(result[1]);
               //cout<<btime<<"HELLO"<<endl;
                         
            }
            if(tp.find("processes")!=string::npos){ 
                vector<string> result;
                boost::split(result, tp, boost::is_any_of(" ")); 
               processes=stoi(result[1]);
               //cout<<btime<<"HELLO"<<endl;
                         
            }
            
        }
      }
      newfile.close();
      
   int num;
   string kb;
   freopen("/proc/meminfo","r",stdin);
   for(int i=0;i<20;i++){
        cin>>tp;
        cin>>num;
        cin>>kb;
        if(tp==array[0]){
            MemTotal=num;
            cout<<"\nMemTotal:"<<MemTotal<<endl;
        }
        else if(tp==array[1]){
            MemFree=num;
            cout<<"MemFree:"<<MemFree<<endl;
        }
        else if(tp==array[2]){
            MemAvailable=num;
            cout<<"MemAvailable:"<<MemAvailable<<endl;
        }
        else if(tp==array[3]){
            SwapTotal=num;
            cout<<"SwapTotal:"<<SwapTotal<<endl;
        }
        else if(tp==array[4]){
            SwapFree=num;
            cout<<"SwapFree:"<<SwapFree<<endl;
        }
   }
   int SwapUsed=SwapTotal-SwapFree;
   cout<<"SwapUsed:"<<SwapUsed<<endl;
   
   float pm,ps;
   pm=((float)MemAvailable/MemTotal)*100;
   ps=((float)SwapFree/SwapTotal)*100;
   
   cout<<"\nType    "<<"      "<<" %"<<endl;
   cout<<"MemoryFree"<<"    "<<pm<<" %"<<endl;
   cout<<"SwapFREE  "<<"    "<<ps<<" %"<<endl;
   
   fclose(stdin);
   
   //Swap PArtition
   newfile.open("/proc/swaps",ios::in);
        if (newfile.is_open()){   
      
      cout<<endl<<"Swap File:"<<"\t"<<"Size"<<endl;
      getline(newfile,tp);
      while(getline(newfile, tp)){ 
                //cout<<tp<<endl;  
                vector<string> result;
                boost::split(result, tp, boost::is_any_of("\t")); 
              
               cout<<result[0].substr(0, 9)<<"\t";
               cout<<result[2]<<endl;
        }
      }
      newfile.close();
      
      //Last 15minutes Load
      cout<<endl;
      freopen("/proc/loadavg","r",stdin);
      cin>>pm;
      cin>>pm;
      cin>>pm;
      cout<<"Average load on the system in the last 15 minutes: "<<pm<<" %"<<endl;
      
      //befor calculated values
      
      cout<<"The number of context switches made by the system so far: "<<ctxt<<endl;
      
      cout<<"The number of interrupts made by the system so far: "<<intr<<endl;
   
     //Read Write block tranfer 
     cout<<endl;
     newfile.open("/proc/diskstats",ios::in);
        if (newfile.is_open()){   
      int readsector,readsectorTime,writesector,writesectorTime;
      while(getline(newfile, tp)){ 
            if(tp.find("loop0")!=string::npos){
                cout<<endl;
                vector<string> result;
                boost::split(result, tp, boost::is_any_of(" ")); 
                
                //cout<<result[18]<<"\t"<<result[19]<<endl;

               readsector=stoi(result[14]);
               readsectorTime=stoi(result[15]);
                
                writesector=stoi(result[18]);
               writesectorTime=stoi(result[19]);
               cout<<"loop0 memory:\n";
               if(writesectorTime!=0)
                    cout<<"\t"<<result[0]<<"write transfer block/sec :"<<(writesector/512)/(writesectorTime/1000)<<endl;
               else
                    cout<<"\t"<<result[0]<<"write transfer block/sec : 0"<<endl;
               cout<<"\t"<<result[0]<<"read transfer block/sec :"<<(readsector/512)/(readsectorTime/1000)<<endl<<endl;
               
            }
            if(tp.find("sda ")!=string::npos){ 
                
                //cout<<tp<<endl;
                vector<string> result;
                boost::split(result, tp, boost::is_any_of(" ")); 
               
               readsector=stoi(result[14]);
               readsectorTime=stoi(result[15]);
                
               writesector=stoi(result[18]);
               writesectorTime=stoi(result[19]);
               
               cout<<"sda memory:\n";
               cout<<"\t"<<result[0]<<"write transfer block/sec :"<<(writesector/512)/(writesectorTime/1000)<<endl;
               cout<<"\t"<<result[0]<<"read transfer block/sec :"<<(readsector/512)/(readsectorTime/1000)<<endl<<endl;
               
            }
        }
      }
      newfile.close();
    cout<<"The rate (number per second) of process creations in the system:"<<(float)processes/btime<<endl;
      
	cout<<"bootedTime: "<<btime<<endl;
	cout<<"context Switches:"<<ctxt<<endl;
	
	cout<<"Context Switches /Booted Time :"<<(float)ctxt/btime<<endl;
     

return 0;
}