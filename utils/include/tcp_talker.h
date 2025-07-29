/********************************
 Name:     Alon Nov
 Exercise: TCP/UDP ping-pong
 Date:	   23.02.2025   
 Reviewer: Zack Molko

********************************/

#ifndef _TCP_TALKER_H_ 
#define _TCP_TALKER_H_

#include <sys/types.h>  /* ssize_t */

#include "sockets.h"


sockinfo* TCPCreate(const char* ipaddr, const char* port);

void TCPDestroy(sockinfo* socket);

ssize_t TCPSend(int fd, void* data, size_t data_size);

ssize_t TCPRecv(int fd, void* data, size_t data_size);

int TCPConnect(sockinfo* socket);

#endif /* TCP_TALKER */