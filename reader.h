#ifndef READER_H
#define READER_H

#include "includes.h"

class Reader
{
    SharedParameters &sharedValues;
    unsigned int port;
    bool priority;
    //unsigned int front = 0;
    char* IP;
    std::thread *thread = nullptr;
public:
    Reader(char* IP_, unsigned int port_, SharedParameters &sharedValues_,bool priority_);
    void ReaderRoutine();
    void Start();
    void Join(){
        thread->join();
    }
    ~Reader();
    bool isPaused = false;
    Semaphore pauseSemaphore{0};
};

#endif // READER_H
