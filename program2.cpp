/***************************************************************************
* File: program2.cpp
* Author: pql160030
* Procedures:

* main - calls initializedata and creates threads and inserts data and flushes them out
  InitializeData - defines full and empty semaphores and other variables
  produce - producer semaphore
  consume - consumer semaphore
  insertItem - function called by produce to insert items into buffer
  removeItem - function called by consume to remove items from butter
***************************************************************************/

/**************************************************************************
To execute:
gcc -pthread "program2.cpp"
./a.out
**************************************************************************/
#include <iostream>
#include <pthread.h>
#include <vector>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>

#define BUFFER_SIZE 1000	//buffer size

void InitializeData();		//declare functions
void *Produce(void *);
void *Consume(void *);
int InsertItem(int);
int RemoveItem(int *);

int counter;
pthread_mutex_t mutex;
sem_t full_sem, empty_sem;	//semaphore declaration

int buffer[BUFFER_SIZE];	//buffer


int main(int argc , char * argv[]){
	InitializeData();
	pthread_t ProducerThread , ConsumerThread;	//defining threads
	int *x = new int [10];	//rand ints
	for(int i = 0 ; i < 10 ; i++){
		x[i] = i;
		pthread_t t;
		pthread_create(&t , NULL, Produce , &x[i]);
		printf("Creating Producer %d \n", i);
	}
	int *y = new int[10];
	for(int i = 0 ; i < 10 ; i++){
		y[i] = i;
		pthread_t t;
		pthread_create(&t , NULL, Consume , &y[i]);
		printf("Creating Consumer %d \n", i);
	}
delete [] x;	//flush out 
delete [] y;

return 0;
}


void InitializeData(){
	pthread_mutex_init(&mutex , NULL);
	sem_init(&full_sem , 0 ,0);	//full semaphore definition
	sem_init(&empty_sem , 0 , BUFFER_SIZE);	//empty semaphore definition
	counter = 0;
}

// Function or produce the item and placed in Buffer
void * Produce(void * Param){
	int item;

	while(1){
		item = rand() % 100;
		sem_wait(&empty_sem);	//wait
		pthread_mutex_lock(&mutex);	//lock
		int msg = InsertItem(item);	//call insert function
		if(msg == -1){
			printf("Error Inserting Item \n");
		}else{
			printf("Produced Item : %d Thread No : %d\n", item , *((int *)Param));
		}
		pthread_mutex_unlock(&mutex);
		sem_post(&full_sem);
	}
}
//same functionality as produce just backwards
void * Consume(void * Param){
int item;
while(1){ //set while condition
sem_wait(&full_sem);
pthread_mutex_lock(&mutex);
int msg = RemoveItem(&item);
  
if(msg == -1){
printf("Error Removing Item \n");
}else
{
printf("Consumed Item :: %d Thread No :: %d \n", item ,*((int *)Param));
}
pthread_mutex_unlock(&mutex);
sem_post(&empty_sem);
  
}
}

//Insert into Buffer
int InsertItem(int item){
if(counter < BUFFER_SIZE){
	buffer[counter] = item;
	counter++;
	return 1;
}else{
	return -1;
}
}

// Remove from buffer
int RemoveItem(int *item){
if(counter > 0){
	*item = buffer[counter - 1];
	counter--;
	return 1;
}else{
	return -1;
}
}
