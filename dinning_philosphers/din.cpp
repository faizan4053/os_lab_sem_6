#include<bits/stdc++.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
using namespace std;
sem_t chopstick[5];
void philospher(int pno)
{
    for(int i=0;i<5;i++)
    {
        sem_wait(&chopstick[pno%5]);
        sem_wait(&chopstick[(pno+1)%5]);
        //cs
        cout<<"Philospher"<<pno<<" is eating"<<endl;
        sem_post(&chopstick[(pno+1)%5]);
        sem_post(&chopstick[(pno)%5]);
    }
}
void philospher_last(int pno)
{
    for(int i=0;i<5;i++)
    {
        sem_wait(&chopstick[(pno+1)%5]);
        sem_wait(&chopstick[pno%5]);
        
        //cs
        cout<<"Philospher"<<pno<<" is eating"<<endl;
        sem_post(&chopstick[(pno)%5]);
        sem_post(&chopstick[(pno+1)%5]);
        
    }
}
int main()
{
    thread p[5];
    for(int i=1;i<=4;i++)
    {
        p[i-1] = thread(philospher,i);
    }
    p[4] = thread(philospher_last,5);
    for(int i=0;i<5;i++)
    {
        p[i].join();
    }
    return 0;
}