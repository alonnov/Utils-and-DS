/* *****************************
 Name:     Alon Nov
 Exercise: unique identifier 
 Date:	   07.11.2024   
 Reviewer: Liad Tiblum

********************************/

#include <stdio.h>      /* size_t, puts */
#include <string.h>		/* memcmp, memcpy, strcmp */
#include <unistd.h>     /* getpid */
#include <ifaddrs.h>	/* getifaddrs, freeifaddrs, ifaddrs */
#include <netinet/in.h>	/* sockaddr_in, AF_INET */
#include <stdatomic.h> 	/* atomic_size_t, atomic_fetch_add */
#include <time.h>

#include "uid.h"   /* API */

static const unid_t bad_unid = {0};
static atomic_size_t counter = 1;

/***************************GetIP**************************************/
static int GetIP(unsigned char ip[4])
{
	struct ifaddrs* list = NULL; 
	struct ifaddrs* runner = NULL;
	struct sockaddr_in* addr = NULL;
	int found = 0;
	
    if(getifaddrs(&list) == -1) 
    {
        puts("could not retrieve IP");
        return 1;
    }
	
    for(runner = list; runner != NULL; runner = runner->ifa_next) 
    {
        if(runner->ifa_addr != NULL && runner->ifa_addr->sa_family == AF_INET) 
        {
            addr = (struct sockaddr_in*)runner->ifa_addr;
            
            if(0 != strcmp(runner->ifa_name, "lo"))
            {       
        		memcpy(ip, &addr->sin_addr, 4); 
        		found = 1; 
        		break;
        	}
        }
    }
    
    freeifaddrs(list);
    
    if (!found)
    {
        puts("Could not retrieve IP");
        return 1;
    }
    
    return 0;
}


/***************************UnIDGenerate**************************************/
unid_t UnIDGenerate(void)
{
	unid_t unid = {0};

	unid.time = time(NULL);
	if(unid.time == (time_t)-1)
	{
		return bad_unid;
	}	
	
	unid.pid = getpid();

	if(GetIP(unid.ip))
	{
		return bad_unid;
	}
	
	unid.counter = 	atomic_fetch_add(&counter, 1);

	return unid;					
}	


/***************************UnIDIsEqual***************************************/
int UnIDIsEqual(unid_t unid1, unid_t unid2)
{
	
	return unid1.time == unid2.time && 
		   unid1.pid == unid2.pid &&
		   0 == memcmp(unid1.ip, unid2.ip, 4) &&
		   unid1.counter == unid2.counter;
}	

