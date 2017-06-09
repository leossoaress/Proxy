#include "includes.h"

void error(const char *msg){
    perror(msg);
    exit(0);
}

Semaphore::Semaphore(unsigned int counter_){
    sem_init(&semaphore, 0, counter_);
}

void Semaphore::P(){
    sem_wait(&semaphore);
}
void Semaphore::V(){
    sem_post(&semaphore);
}

int Semaphore::GetValue(){
    int value;
    sem_getvalue(&semaphore, &value);
    return value;
}

int Semaphore::TryP(){
    return sem_trywait(&semaphore);
}
