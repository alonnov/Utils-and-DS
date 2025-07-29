/********************************
 Name:     Alon Nov
 Exercise: TCP/UDP ping-pong
 Date:	   23.02.2025   
 Reviewer: Zack Molko

********************************/

#include <stdlib.h>						/* malloc, free */
#include <stdio.h>						/* puts */
#include <unistd.h>						/* close */
#include <string.h>						/* strcmp */
#include <assert.h>						/* assert */

#include "../include/udp.h"				/* UDP functions, Sock functions */
#include "../include/tcp_listener.h"	/* TCP functions */
#include "../include/server.h"			/* TCP functions */

#define STDIN (0)
#define FD_MAX (1024)

typedef int (*handler)(server*, int);

struct serv
{
	fd_set fds;
	sockinfo* listener_socks[3];
	handler handlers[FD_MAX];
	int fdmax;
	int run_flag;
};

static void InitSet(server* serv);
static void InsertFD(server* serv, int newfd);
static void RemoveFD(server* serv, int fd);
static int ClientHandler(server* serv, int fd);
static int TCPHandler(server* serv, int fd);
static int UDPHandler(server* serv, int fd);
static int StdinHandler(server* serv, int fd);


server* ServerCreate(const char* ipaddr, const char* port)
{
	sockinfo* udp = NULL;
	sockinfo* tcp = NULL;
	sockinfo* udp_brdcst = NULL;	
	server* serv = NULL;
	int i = 0;
	
	assert(ipaddr);
	assert(port);	
	
	serv = (server*)malloc(sizeof(server));
	if(serv == NULL)
	{
		puts("ServerCreate error");
		return NULL;
	}

	udp = UDPCreate(ipaddr, "5001");
	tcp = TCPCreate(ipaddr, "5002");
	udp_brdcst = UDPCreate(ipaddr, "5003");

	if( !tcp || SockBind(udp) ||
		!udp || SockBind(tcp) ||
		!udp_brdcst || SockBind(udp_brdcst) || UDPSetBroadcast(udp_brdcst))
	{
		puts("ServerCreate error");
		ServerDestroy(serv);
		return NULL;
	}

	serv->listener_socks[0] = tcp;
	serv->listener_socks[1] = udp;	
	serv->listener_socks[2] = udp_brdcst;	
	
	for(i = 0; i < FD_MAX; ++i)
	{
		serv->handlers[i] = NULL;
	}

	serv->handlers[0] = StdinHandler;
	serv->handlers[SockGetFD(tcp)] = TCPHandler;
	if(TCPlisten(SockGetFD(tcp)) != 0)
	{
		puts("ServerCreate error");
		ServerDestroy(serv);
		return NULL;
	}

	serv->handlers[SockGetFD(udp)] = UDPHandler;
	serv->handlers[SockGetFD(udp_brdcst)] = UDPHandler;

	return serv; 
}


void ServerDestroy(server* serv)
{
	int i = 0;

	assert(serv);

	SockDestroy(serv->listener_socks[0]);
	SockDestroy(serv->listener_socks[1]);
	SockDestroy(serv->listener_socks[2]);

	for(i = 0; i < FD_MAX; ++i)
	{
		if(serv->handlers[i] != NULL)
		{
			close(i);
		}
	}

	free(serv);
	puts("server closed");
}


int ServerRun(server* serv)
{
	int i = 0;
	int res = 0;
	struct timeval timeout = {0};

	assert(serv);

	puts("server is running");

	serv->run_flag = 1;

	while(serv->run_flag == 1)
	{
		InitSet(serv);

		timeout.tv_usec = 0;
		timeout.tv_sec = 7;
		res = select(serv->fdmax + 1, &serv->fds, NULL, NULL, &timeout);
		if(res == -1)
		{
			puts("ServerRun error");
			break;
		}
		
		for(i = 0; i < FD_MAX; ++i)
		{
			if(FD_ISSET(i, &serv->fds))
			{
				serv->handlers[i](serv, i);
			}
		}

		if(res == 0)
		{
			puts("server still running...");
		}
	}
	
	ServerDestroy(serv);

	return res;
}


static void InitSet(server* serv)
{
	int i = 0;

	assert(serv);

	serv->fdmax = 0;
	FD_ZERO(&serv->fds);

	for(i = 0; i < FD_MAX; ++i)
	{
		if(serv->handlers[i] != NULL)
		{
			FD_SET(i, &serv->fds);

			if(serv->fdmax < i)
			{
				serv->fdmax = i;
			}
		}
	}
}	


static int ClientHandler(server* serv, int fd)
{
	char buffer[BUFSIZ] = {0};
	ssize_t res = TCPRecv(fd, buffer, BUFSIZ);

	assert(serv);

	if(res == -1)
	{
		puts("ClientHandler error");
		return 1;
	}

	if(res == 0)
	{
		printf("socket %d disconnected\n", fd);
		RemoveFD(serv, fd);
		return 1;
	}

	if(strcmp(buffer, "ping") == 0)
	{
		puts("recieved TCP ping");
		TCPSend(fd, "pong", 5);
	}

	return 0;
}


static void InsertFD(server* serv, int newfd)
{
	assert(serv);

	FD_SET(newfd, &(serv->fds)); 	
	serv->handlers[newfd] = ClientHandler;
}


static void RemoveFD(server* serv, int fd)
{
	assert(serv);

	FD_CLR(fd, &(serv->fds)); 	
	serv->handlers[fd] = NULL;
}


static int TCPHandler(server* serv, int fd)
{
	int newfd = 0;

	assert(serv);

	newfd = TCPAccept(fd);
	if(newfd == -1)
	{
		return 1;
	}

	InsertFD(serv, newfd);  

	printf("new client: %d\n", newfd);

	return newfd;
}


static int UDPHandler(server* serv, int fd)
{
	int i = 1;
	char buffer[BUFSIZ] = {0};
	sockinfo* sock = NULL;
	ssize_t res = 0;

	assert(serv);

	sock = SockGetFD(serv->listener_socks[1]) == fd ? 
			serv->listener_socks[1] : serv->listener_socks[2];

	res = UDPRecvFrom(sock, buffer, BUFSIZ);
	if(res == -1)
	{
		puts("UDPHandler error");
		return res;
	}

	if(strcmp(buffer, "ping") == 0)
	{
		puts("recieved UDP ping");
		res = sendto(fd, "pong", 5, 0, SockGetAddr(sock), SockGetLen(sock));
		if(res == -1)
		{
			puts("UDPHandler error");
		}
	}
	
	return res;
}


static int StdinHandler(server* serv, int fd)
{
	char buffer[BUFSIZ] = {0};
	(void)fd;

	assert(serv);

	if(strcmp(fgets(buffer, 6, stdin), "ping\n") == 0)
	{
		puts("pong");
	}

	else if(strcmp(buffer, "quit\n") == 0)
	{
		puts("server stopped");
		serv->run_flag = 0;
	}

	return 0;
}
