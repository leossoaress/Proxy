#include "writer.h"

Writer::Writer(char* IP_, unsigned int port_, SharedParameters &sharedValues_)
    :IP(IP_),
    port(port_),
    sharedValues(sharedValues_){}


void Writer::WriterRoutine(){
    int sock, length, n;
    socklen_t fromlen;

    // A estrutura sockaddr_in contem um endereco de internet
    struct sockaddr_in server;


    // Cria um socket do tipo datagrama e retorna um descritor
    sock = socket(AF_INET, SOCK_DGRAM, 0);


    if (sock < 0) error("Opening socket");

    length = sizeof(server);

    // Zera a estrutura "server"
    bzero(&server, length);
    // Define a familia do endereco como do tipo Internet
    server.sin_family = AF_INET;
    // Seta o endereco para o endereço escolhido
    //server.sin_addr.s_addr = inet_addr(IP);
    server.sin_addr.s_addr = INADDR_ANY;
    // A funcao htons() converte o numero da porta para o padrao Little Endian.
    server.sin_port = htons(port);


    // Associa um socket a um endereco

    if (bind(sock, (struct sockaddr *) &server, length) < 0)
        error("binding");

    fromlen = sizeof(struct sockaddr_in);

    while (1)
    {
        // A funcao recvfrom() bloqueia o programa ate que um pacote seja lido.
        // Quando isso acontece, o pacote e' armazenado em um buffer passado por
        // parametro. Parametros: socket, buffer, tamanho do buffer, flags,
        // endereco da maquina que enviou o pacote, tamanho da estrutura do endereco.
        // Retorna o numero de bytes recebidos.


        sharedValues.empty.P();         //Verifica se tem espaço para escrever, caso tenha, deixa entrar na seção

        n = recvfrom(sock, sharedValues.buffer[rear], BUFFER_SIZE, 0, (struct sockaddr *) &server, &fromlen);   //Recebe as informações da porta

        rear = (rear + 1) % LIMITED_BUFFERSIZE; //Acrescenta 1 no rear, ou seja, muda a posição onde vai ser escrito na proxima interação

        sharedValues.full.V();      //Avisa que tem informação no buffer

    }
}


void Writer::Start()
{
    thread = new std::thread(&Writer::WriterRoutine, this);
}

Writer::~Writer()
{
    if(thread != nullptr)
        delete thread;
}
