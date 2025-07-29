/********************************
 Name:     Alon Nov
 Exercise: TCP/UDP ping-pong
 Date:	   23.02.2025   
 Reviewer: Zack Molko

********************************/

#ifndef _SERVER_H_ 
#define _SERVER_H_

#include "sockets.h"

typedef struct serv server;

server* ServerCreate(const char* ipaddr, const char* port);

void ServerDestroy(server* serv);

int ServerRun(server* serv);


#endif /* SERVER */