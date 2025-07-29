/********************************
 Name:     Alon Nov
 Exercise: TCP/UDP ping-pong
 Date:	   23.02.2025   
 Reviewer: Zack Molko

********************************/

#include <stdlib.h>				/* atoi	*/
#include <string.h>				/* memset */
#include <stdio.h>				/* puts */
#include <unistd.h>				/* close */
#include <sys/socket.h>			/* socket, bind */
#include <netdb.h>				/* addrinfo, getaddrinfo, freeaddrinfo, AI_PASSIVE*/
#include <assert.h>				/* assert */
#include "../include/udp.h"		/* API */


sockinfo* UDPCreate(const char* ip_addr, const char* port)
{
	sockinfo* sock = SockCreateSocketInfo(ip_addr, port, SOCK_DGRAM);
	
	SockCreate(sock);
	if(!sock)
	{
		return NULL;
	}

	return sock;
}


void UDPDestroy(sockinfo* socket)
{
	SockDestroy(socket);
}


ssize_t UDPSend(int fd, void* data, size_t data_size)
{
	ssize_t res = 0;

	res = send(fd, data, data_size, 0);
	if(res == -1)
	{
		puts("UDPSend error");
	}

	return res;
}


ssize_t UDPSendTo(sockinfo* sock, void* data, size_t data_size)
{
	ssize_t res = 0;

	assert(sock);
	assert(data);

	res = sendto(SockGetFD(sock), data, data_size, 0, 
				SockGetAddr(sock), SockGetLen(sock));
	if(res == -1)
	{
		puts("UDPSendTo error");
	}

	return res;
}


ssize_t UDPRecv(int fd, void* data, size_t data_size)
{
	ssize_t res = 0;

	assert(data);

	res = recv(fd, data, data_size, 0);
	if(res == -1)
	{
		puts("UDPSendTo error");
	}

	return res;
}


ssize_t UDPRecvFrom(sockinfo* sock, void* buffer, size_t data_size)
{
	ssize_t res = 0;
	unsigned int size = SockGetLen(sock);
	res = recvfrom(SockGetFD(sock), buffer, data_size, 0, SockGetAddr(sock), &size);
	if(-1 == res)
	{
		puts("UDPRecvFrom error");
	}

	return res;
}


int UDPSetBroadcast(sockinfo* sock)
{
	int yes = 1;
	int res = 0;

	assert(sock);
	
	res = setsockopt(SockGetFD(sock), SOL_SOCKET, SO_BROADCAST, &yes, sizeof(int));
	if(res == -1)
	{
		puts("UDPSetBroadcast error");
	}

	return res;
}
