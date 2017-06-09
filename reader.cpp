#include "reader.h"

Reader::Reader(char* IP_, unsigned int port_, SharedParameters &sharedValues_, bool priority_ = false):
sharedValues(sharedValues_),
IP(IP_),
port(port_),
priority(priority_)
{}

void Reader::ReaderRoutine(){
    int sock, length, n;
    socklen_t fromlen;

    // A estrutura sockaddr_in contem um endereco de internet
    struct sockaddr_in server;
    // Buffer para receber mensagens

    // Cria um socket do tipo datagrama e retorna um descritor
    sock = socket(AF_INET, SOCK_DGRAM, 0);


    if (sock < 0) error("Opening socket");

    length = sizeof(server);

    // Zera a estrutura "server"
    bzero(&server, length);
    // Define a familia do endereco como do tipo Internet
    server.sin_family = AF_INET;
    // Seta o endereco para o IP escolhido
    //server.sin_addr.s_addr = INADDR_ANY;
    server.sin_addr.s_addr = inet_addr(IP);

    // Associa um socket a um endereco

    /*if (bind(sock, (struct sockaddr *) &server, length) < 0)
        error("binding");*/

    fromlen = sizeof(struct sockaddr_in);


    while (1){

        sharedValues.entranceLock.P();  //Entrada da seção crítica

        /*protocolo de entrada das threads de alta prioridade */

        if(priority == true)    //Verifica se a thread tem prioridade
        {
           if(sharedValues.numberOfThreads > 0 || sharedValues.numberOfHThreads > 0) //Verifica se já tem alguma thread rodando
           {
               sharedValues.delayedHighPriority++;      //Avisa que foi dormir
               sharedValues.entranceLock.V();           //Librea a seção crítica
               sharedValues.highPrioritySemaphore.P();  //Coloca pra dormir a thread
           }

           sharedValues.numberOfHThreads++;             //Avisa que tem uma thread de alta prioridade rodando
           sharedValues.numberOfActiveThreads++;        //Avisa que tem mais uma thread ativa
           sharedValues.entranceLock.V();               //Libera a seção crítica
        }

        /*protocolo de entrada das threads de baixa prioridade */

        else
        {
           if(sharedValues.numberOfHThreads > 0)        //Verifica se tem alguma thread de alta prioridade
           {                                            //Se tiver
               sharedValues.delayedLowPriority++;       //Avisa que a thread de baixa proridade vai dormir
               sharedValues.entranceLock.V();           //Libera a seção crítica
               sharedValues.lowPrioritySemaphore.P();   //Coloca pra dormir a thread de baixa prioridade pra dormir
           }

           sharedValues.numberOfThreads++;              //Avisa que tem uma thread de baixa prioridade rodando
           sharedValues.numberOfActiveThreads++;        //Avisa que tem uma thread ativa

           if(sharedValues.delayedLowPriority > 0)      //Verifica sem tem alguma thread de baixa prioridade dormindo
           {
               sharedValues.delayedLowPriority--;       //Avisa que vai acordar uma thread de baixa prioridade
               sharedValues.lowPrioritySemaphore.V();   //Acorda uma thread de baixa prioridade
           }

           else
               sharedValues.entranceLock.V();           //Libera a seção crítica

        }

        while (1)
        {

            sharedValues.readersMutex.P();      //Protege na seção crítica

            if(sharedValues.counter == 0)       //A primeira thread vai liberar o full
            {
                 sharedValues.full.P();
            }


            server.sin_port = htons(port);      //Seta a porta

            n = sendto(sock, sharedValues.buffer[sharedValues.front], BUFFER_SIZE, 0, (struct sockaddr *) &server, fromlen);    //Envia o vídeo para a porta

            sharedValues.counter++;     //Avisa que uma thread já leu o pacote

            if(sharedValues.counter < sharedValues.numberOfActiveThreads)   //Verifica se o número de threads que já leu o pacote é menor que o numero de threads ativas
            {
                sharedValues.delayUntilAllRead++;       //Avisa que vai colocar pra dormir a thread que já leu o pacote
                sharedValues.readersMutex.V();          //Libera a seção crítica
                sharedValues.waitUntilAllRead.P();      //Coloca pra dormir a thread
            }
            else
            {
                sharedValues.empty.V();         //Todo mundo já leu o pacote e libera o empty
                sharedValues.counter = 0;       //Zera o contador para a prixima leitura do pacote
                sharedValues.front = (sharedValues.front + 1) % LIMITED_BUFFERSIZE;     //Seta novo front de todas as threads
            }

            if(sharedValues.delayUntilAllRead > 0)      //Verifica se tem alguma thread esperando as restantes lerem
            {
                sharedValues.delayUntilAllRead--;       //Avisa que vai liberar a thread que tava esperando todas lerem
                sharedValues.waitUntilAllRead.V();      //Acorda essa thread
            }
            else
                sharedValues.readersMutex.V();          //Libera a seção crítica

            if(isPaused)        //Verifica se foi clicado o botão de pausa
            {
                break;          //Sai do while
            }

        }

        sharedValues.entranceLock.P();      //Protege a seção crítica


        /*protocolo de saida das threads de alta prioridade */

        if(priority == true)        //Verifica se a thread é alta prioridade
        {
            sharedValues.numberOfHThreads--;        //Avisa que vai acordar uma thread de alta prioridade
            sharedValues.numberOfActiveThreads--;   //Avisa que uma thread não está mais ativa

            if(sharedValues.delayedHighPriority > 0)    //Verifica se tem alguma thread de alta prioridade dormindo
            {
                sharedValues.delayedHighPriority--;         //Avisa que vai acordar a thread que estava dormindo
                sharedValues.highPrioritySemaphore.V();     //Passa o bastão para a thread de alta prioridade
            }
            else if(sharedValues.delayedLowPriority > 0)    //Verifica se tem alguma thread de baixa prioridade dormindo
            {
                sharedValues.delayedLowPriority--;          //Avisa que vai acordar a thread que estava dormindo
                sharedValues.lowPrioritySemaphore.V();      //Passa o bastão para a threade de baixa prioridade que estava dormindo
            }
            else
                sharedValues.entranceLock.V();      //Livera a seção crítica
        }

        /* protocolo de saida das threads de baixa prioridade */

        else        //Caso a thread for de baixa prioridade
        {
            sharedValues.numberOfThreads--;         //Avisa que vai acordar uma thread de baixa prioridade
            sharedValues.numberOfActiveThreads--;   //Avisa que uma thread não está mais ativa

            if(sharedValues.numberOfThreads == 0 && sharedValues.delayedHighPriority > 0)   //Verifica se não tem mais nenhuma thread de baixa prioridade rodando e se tem alguma thred de alta prioridade esperando
            {
                sharedValues.delayedHighPriority--;         //Avisa que vai liberar uma thread de alta prioridade
                sharedValues.highPrioritySemaphore.V();     //Passa o bastão para a thread de alta prioridade que tava esperando
            }
            else
                sharedValues.entranceLock.V();      //Libera a seção crítica
        }

        if(isPaused)    //Verifica se o botão do pause foi clicado
        {
            pauseSemaphore.P();     //Coloca a thread atual pra dormir
        }

    }
}

void Reader::Start()
{
    thread = new std::thread(&Reader::ReaderRoutine, this);
}

Reader::~Reader()
{
    if(thread != nullptr)
        delete thread;
}
