/********************************
 Name:     Alon Nov
 Exercise: TCP/UDP ping-pong
 Date:	   23.02.2025   
 Reviewer: Zack Molko

********************************/

#include <stdlib.h>					/* NULL */
#include <stdio.h>					/* puts */
#include <sys/socket.h>				/* accept, listen */
#include <assert.h>					/* assert */

#include "../include/tcp_listener.h"/* API */

int TCPlisten(int fd)
{
	int res = listen(fd, 100);
	if(res == -1)
	{
		puts("TCPListen error");
	}

	return res; 
}

int TCPAccept(int fd)
{
	int res = accept(fd, NULL, NULL);
	if(res == -1)
	{
		puts("TCPAccept error");
	}

	return res; 
}

