#ifndef WRITER_H_
#define WRITER_H_

#include "includes.h"


class Writer{
    SharedParameters &sharedValues;
    unsigned int rear = 0;
    char *IP;
    unsigned int port;
    std::thread *thread = nullptr;
public:
    Writer(char* IP_, unsigned int port_, SharedParameters &sharedValues_);
    void WriterRoutine();
    void Start();
    void Join(){
        thread->join();
    }
    ~Writer();
    bool isPaused = false;
    Semaphore pauseSemaphore{0};
};




#endif /* WRITER_H_ */
