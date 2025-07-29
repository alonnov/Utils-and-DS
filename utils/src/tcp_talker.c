/********************************
 Name:     Alon Nov
 Exercise: TCP/UDP ping-pong
 Date:	   23.02.2025   
 Reviewer: Zack Molko

********************************/

#include <string.h>					/* memset */
#include <stdio.h>					/* puts */
#include <unistd.h>					/* close */
#include <sys/socket.h>				/* socket, bind */
#include <netdb.h>					/* addrinfo, getaddrinfo, freeaddrinfo, AI_PASSIVE */
#include <assert.h>					/* assert */

#include "../include/tcp_talker.h"	/* API */


sockinfo* TCPCreate(const char* ip_addr, const char* port)
{
	sockinfo* sock = SockCreateSocketInfo(ip_addr, port, TCP);
	
	SockCreate(sock);
	if(!sock)
	{
		return NULL;
	}

	return sock;
}


void TCPDestroy(sockinfo* sock)
{
	SockDestroy(sock);
}


ssize_t TCPSend(int fd, void* data, size_t data_size)
{
	ssize_t res = 0;
	
	assert(data);

	res = send(fd, data, data_size, 0);
	if(res == -1)
	{
		puts("TCPSend error");
	}

	return res;
}


ssize_t TCPRecv(int fd, void* data, size_t data_size)
{
	ssize_t res = 0;
	
	assert(data);

	res = recv(fd, data, data_size, 0);
	if(res == -1)
	{
		puts("TCPRecv error");
	}

	return res;
}


int TCPConnect(sockinfo* sock)
{
	int res = 0;

	res = connect(SockGetFD(sock), SockGetAddr(sock), SockGetLen(sock));
	if(res == -1)
	{
		puts("TCPConnect error");
	}

	return res;
}


