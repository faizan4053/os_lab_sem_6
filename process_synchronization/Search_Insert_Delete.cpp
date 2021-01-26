#include "utility.cpp"

void insertion(int data){
	sem_wait(&insertMutex);					//to protect the shared variable No_Of_Insertors
	No_Of_Inserters++;
	if(No_Of_Inserters==1)
		sem_wait(&insertLock);				//make deletion know that insertion is in critical section
	sem_post(&insertMutex);

		sem_wait(&multipleInserterLock);	//mutual exclusion between two or more inserterss
			insert(data);					//cs
		sem_post(&multipleInserterLock);

	sem_wait(&insertMutex);
		No_Of_Inserters--;
		if(No_Of_Inserters==0)
			sem_post(&insertLock);
	sem_post(&insertMutex);
	sleep(1);
}

void deletion(int data){
	sem_wait(&searchLock);						//if serches is in critical section
		sem_wait(&insertLock);					//if insertion is in critical section
			sem_wait(&multipleDeleterLock);		//mutual exclusion among deleters
				remove(data);					//critical section
			sem_post(&multipleDeleterLock);
		sem_post(&insertLock);
	sem_post(&searchLock);
	sleep(1);
}

void searches(int data){
	sem_wait(&searchMutex);						//to protect the shared variable No_Of_Searchers
		No_Of_Searchers++;
		if(No_Of_Searchers==1)
			sem_wait(&searchLock);				//make deletion know that seacrhes is in critical section
	sem_post(&searchMutex);

		search(data);							//since multiple searches can enter the critical section 

	sem_wait(&searchMutex);
		No_Of_Searchers--;
		if(No_Of_Searchers==0)
			sem_post(&searchLock);
	sem_post(&searchMutex);
	sleep(1);
}


