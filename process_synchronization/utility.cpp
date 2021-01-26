

//Mohamd Faizan 2017ucp1202

#include<bits/stdc++.h>
#include<stdlib.h>
#include<unistd.h>
#include<thread>
#include<semaphore.h>
#define N 10
using namespace std;

typedef struct list{
	int data;
	struct list *next;
}L;


L *head=NULL,*tail=NULL;

L *createNode(int x){
	L *temp=(L*)malloc(sizeof(L));
	if(!temp){
		cout<<"Error creating node";
		return NULL;
	}
	temp->data=x;
	temp->next=NULL;
	return temp;
}

void print(){
	if(!head){
		cout<<"Nothing to print list is empty\n";
		return;
	}
	printf("List is :\n");
	L *temp=head;
	while(temp){
		cout<<temp->data<<" ";
		temp=temp->next;
	}
	cout<<endl;
}

void insert(int data){
	cout<<"\nInserting "<<data<<endl;
	L *temp=createNode(data);
	if(!temp)
		return;
	if(head==NULL)
		head=tail=temp;
	else{
		tail->next=temp;
		tail=temp;
	}
	print();
}


void search(int data){
	cout<<"\nSearching "<<data<<"\n";
	if(head==NULL){
		cout<<"\nlist is empty\n";
		return;
	}
	L *temp=head;
	int f=0;
	while(temp){
		if(temp->data==data){
			cout<<"\n"<<data<<" is Present"<<endl;
			f=1;
			return;
		}
		temp=temp->next;
	}
	if(f==0)
		cout<<"\n"<<data<<" is not Present"<<endl;
}



void remove(int data){
	if(head==NULL){
		cout<<"\nlist is empty\n";
		return;
	}
	L *temp=head,*a,*b;
	if(temp->data==data){
		a=temp->next;
		delete(temp);
		head=a;
		cout<<"\ndeleted "<<data<<endl;
		return;
	}
	else{
		while(temp && temp->next){
			if(temp->next->data==data){
				a=temp->next->next;
				//delete(temp->next);
				temp->next=a;
				cout<<"\ndeleted "<<data<<endl;
				return;
			}
			temp=temp->next;
		}
		cout<<"\nNothing is deleted as element is not present\n";
		return;
	}
}

sem_t multipleInserterLock,insertLock,searchLock,searchMutex,insertMutex,multipleDeleterLock;
int No_Of_Searchers=0,No_Of_Inserters=0;

void init(){
	sem_init(&multipleInserterLock,0,1);
	sem_init(&multipleDeleterLock,0,1);
	sem_init(&insertLock,0,1);
	sem_init(&searchLock,0,1);
	sem_init(&searchMutex,0,1);
	sem_init(&insertMutex,0,1);
}