/********************************
 Name:     Alon Nov
 Exercise: TCP/UDP ping-pong
 Date:	   23.02.2025   
 Reviewer: Zack Molko

********************************/

#ifndef _TCP_LISTENER_H_ 
#define _TCP_LISTENER_H_

#include "tcp_talker.h"

int TCPlisten(int fd);

int TCPAccept(int fd);

#endif /* TCP_LISTENER */
