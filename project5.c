#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>


sem_t full;

sem_t empty;

pthread_mutex_t mutex;

int gArr[16];


void *produce();

void *consume();


typedef struct{

	pthread_t tid;

	pthread_attr_t attr;

	int size;

	int tNum;

	int counter;

}Producers;


typedef struct{

	pthread_t tid;

	pthread_attr_t attr;

	int size;

}Consumers;

int main(int argc, char *argv[]){
//initialize semaphores and mutex lock
	sem_init(&full,0,0);

	sem_init(&empty,0,16);

	pthread_mutex_init(&mutex,NULL);

	
//convert user arguments
	int numP = pow(2,atoi(argv[1])) + 0.5;

	int numC = pow(2,atoi(argv[2])) + 0.5;

	int numProduced = pow(2,atoi(argv[3])) + 0.5;

	
//create producer struct array
	Producers pArr[numP];

	Producers *p;
//initialize producer array
	for(int i =0;i<numP;i++){

		p = (Producers *) malloc(sizeof(Producers));

		p->size = numProduced;

		p->tNum = i;

		p->counter = 0;

		pthread_attr_init(&(p->attr));

		pthread_create(&(p->tid),&(p->attr),produce,p);

		pArr[i] = *p;

		

	}

	
//create consumer struct array
	Consumers cArr[numC];

	Consumers *c;
//initialize consumer array
	for(int i=0;i<numC;i++){

		c = (Consumers *) malloc(sizeof(Consumers));

		c->size = numProduced*numP/numC;

		pthread_attr_init(&(c->attr));

		pthread_create(&(c->tid),&(c->attr),consume,c);

		cArr[i] = *c;

	}

	
//join producer threads
	for(int i = 0; i<numP; i++){

   pthread_join(pArr[i].tid, NULL);

}
//join consumer threads
	for(int i = 0; i<numC; i++){

   pthread_join(cArr[i].tid, NULL);

}

	return 0;

	

}


void *produce(void* param){

Producers* arg = (Producers*)param;

	int value;

	for(int i=0;i<arg->size;i++){
	int produced = arg->tNum * arg->size + arg->counter;
	sem_wait(&empty);
	pthread_mutex_lock(&mutex);
//must check if full semaphore is suspended
	if(sem_getvalue(&full,&value) == 0){

		gArr[value] = produced;

		arg->counter++;

		pthread_mutex_unlock(&mutex);

		sem_post(&full);

	}else{
//if full is suspended do not post full
	pthread_mutex_unlock(&mutex);

		}

	}

	pthread_exit(0);

	}

void *consume(void* param){

Consumers* arg = (Consumers*)param;

	int value;

	for(int i=0;i<arg->size;i++){

	sem_wait(&full);

	pthread_mutex_lock(&mutex);

		sem_getvalue(&full,&value);

	printf("consumed: %d\n",gArr[value]);	

	pthread_mutex_unlock(&mutex);

	sem_post(&empty);

	

	}

	pthread_exit(0);

	}
