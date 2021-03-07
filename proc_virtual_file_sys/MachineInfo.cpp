#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main(){
    string line;
    //int fp=fopen("/proc/cpuinfo","r");
    fstream newfile;
    string tp;
    string array[]={"processor","model name","cpu cores","cpu MHz"};
    newfile.open("/proc/cpuinfo",ios::in);
        if (newfile.is_open()){   
      
      while(getline(newfile, tp)){ 
         for(string i:array){
            /*if(i==tp.substr(0, 9)){
                cout<<tp;
            }*/
            if(tp.find(i)!=string::npos){
                cout<<tp<<endl;  
                if(i=="cpu cores") cout<<endl;    
            }
         }
      }
      newfile.close();
      
   }
    newfile.open("/proc/version",ios::in);
    if (newfile.is_open()){ 
            while(getline(newfile,tp)){
                cout<<tp<<endl;
            }
            cout<<endl;
    }
     newfile.close(); 
     
     
      newfile.open("/proc/meminfo",ios::in);
      
    if (newfile.is_open()){ 
            while(getline(newfile,tp)){
                cout<<tp<<endl;
            }
            cout<<endl;
    }
     newfile.close(); 
     
             int val;
    ifstream input("/proc/uptime");
        input >> val;
        cout<<val<<endl;
        int min,hr,sec,day;
        min=val/60;
        sec=val%60;
        hr=min/60;
        min =min%60;
        day=hr/24;
        hr=hr%60;
        cout<<day<<":"<<hr<<":"<<min<<":"<<sec<<endl;
     input.close(); 
     

return 0;
}