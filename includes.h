#ifndef INCLUDES_H_
#define INCLUDES_H_

#define BUFFER_SIZE 1316
#define LIMITED_BUFFERSIZE 1000

#include <sys/types.h>
#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <netdb.h>
#include <cstdio>
#include <thread>
#include <semaphore.h>
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>

void error(const char *msg);


/* Classe das operações dos semáforos*/
class Semaphore{
    sem_t semaphore;
public:
    Semaphore(unsigned int counter_);
    void P();
    void V();
    int GetValue();
    int TryP();
};

/* Classe com todas as variáveis*/
class SharedParameters{
public:
    unsigned int delayUntilAllRead = 0;
    unsigned int counter = 0;
    unsigned int front = 0;
    unsigned int numberOfThreads = 0;
    unsigned int numberOfHThreads = 0;
    unsigned int numberOfActiveThreads = 0;
    unsigned int delayedHighPriority;
    unsigned int delayedLowPriority;
    char buffer[LIMITED_BUFFERSIZE][BUFFER_SIZE]; // buffer
    Semaphore empty{LIMITED_BUFFERSIZE};
    Semaphore full{0};
    Semaphore readersMutex{1};
    Semaphore waitUntilAllRead{0};
    Semaphore highPrioritySemaphore{0};
    Semaphore lowPrioritySemaphore{0};
    Semaphore entranceLock{1};
    bool pauseAll = false;
};


#endif /* INCLUDES_H_ */
