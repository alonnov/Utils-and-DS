/* *****************************
 Name:     Alon Nov
 Exercise: DHCP
 Date:	   18.12.2024   
 Reviewer: Shani Davidian

********************************/

#include <stdio.h>		/* sscanf, sprintf */
#include <arpa/inet.h>  /* uint32_t, ntohl, htonl */
#include <stdlib.h>		/* malloc, free */
#include <string.h> 	/* memset */
#include <assert.h> 	/* assert */

#include "dhcp.h" /* API */

#define MASK (1)
#define IP_BITS (32)

enum test
{
    FALSE,
    TRUE          
};

typedef struct node node_t;

struct dhcp
{
    node_t* root;
    ip_t subnet_ip;
    size_t bits_in_subnet;
};

struct node
{
    node_t* left; 
    node_t* right; 
    int is_subtree_used;  
};

/***********************Static Function Delcarations*************************/

static int CheckNode(node_t* node);
static node_t* CreateNode();
static status_t GetLowestIp(node_t* node, uint32_t* res_ip, int bits);
void DestroyRec(dhcp_t* dhcp, node_t* node);
static status_t RequestRec(node_t* node, uint32_t* req_ip, uint32_t* res_ip, int bits);
static status_t ReleaseRec(node_t* node, uint32_t* req_ip, int bits);


/***************************DHCPCreate***************************************/
dhcp_t* DHCPCreate(ip_t subnet_ip, size_t bits_in_subnet)
{
	dhcp_t* dhcp = NULL;
	ip_t ip1 = {0};
	ip_t ip2 = {{255, 255, 255, 255}};
	uint32_t mask = 0;
	uint32_t broadcast = 0;
	uint32_t int_net = 0;

	assert(bits_in_subnet <= IP_BITS - 2);

	dhcp = (dhcp_t*)malloc(sizeof(dhcp_t));
	if(NULL == dhcp)
	{
		return NULL;
	}

	dhcp->root = CreateNode();
	if(NULL == dhcp->root)
	{
		free(dhcp);
		return NULL;
	}
	
	dhcp->bits_in_subnet = bits_in_subnet;

	mask = 0xFFFFFFFF << (IP_BITS - dhcp->bits_in_subnet);
	int_net = htonl(*(uint32_t*)subnet_ip.ip) & mask;
	*(uint32_t*)dhcp->subnet_ip.ip = ntohl(int_net);	
	broadcast = int_net | ~mask;
	*(uint32_t*)ip1.ip = ntohl(int_net);  
	*(uint32_t*)ip2.ip = ntohl(broadcast);

	if(SUCCESS != DHCPRequest(dhcp, &ip1, &ip1) ||
	   SUCCESS != DHCPRequest(dhcp, &ip2, &ip2))
	{
		DHCPDestroy(dhcp);
		return NULL;
	}

	return dhcp;
}	


/***************************DestroyRec**************************************/
void DestroyRec(dhcp_t* dhcp, node_t* node)
{
	if(NULL == node)
	{
		return;
	}
	
	DestroyRec(dhcp, node->left);
	DestroyRec(dhcp, node->right);
	free(node);
}


/***************************DHCPDestroy************************************/
void DHCPDestroy(dhcp_t* dhcp)
{
	assert(dhcp);
	
	DestroyRec(dhcp, dhcp->root);
	memset(dhcp, 0, sizeof(dhcp_t));
	free(dhcp);
}		


/**************************RequestRec******************************************/
static status_t RequestRec(node_t* node, uint32_t* req_ip, uint32_t* res_ip, int bits)
{
	status_t stat = SUCCESS;
	int res = (*req_ip >> (bits - 1)) & MASK;

	if(0 == bits)					 
	{
		node->is_subtree_used = TRUE;
		return stat;
	}

	if((0 == res && CheckNode(node->left)) ||
	   (1 == res && CheckNode(node->right)))
	{
		return DIFFERENT;
	}

	if(0 == res)
	{
		if(NULL == node->left)
		{
			node->left = CreateNode();
			if(NULL == node->left)
			{
				return FAILURE;
			}
		}
		stat = RequestRec(node->left, req_ip, res_ip, bits - 1);
	}
	else
	{
		if(NULL == node->right)
		{
			node->right = CreateNode();
			if(NULL == node->right)
			{
				return FAILURE;
			}
		}
		*res_ip |= (MASK << (bits - 1));
		stat = RequestRec(node->right, req_ip, res_ip, bits - 1);		
	}

	if(CheckNode(node->left) && CheckNode(node->right))
	{
		node->is_subtree_used = TRUE;	
	}		

	return stat;
}


/***************************DHCPRequest***************************************/
status_t DHCPRequest(dhcp_t* dhcp, ip_t* requested_ip, ip_t* result_ip)
{
	status_t stat = SUCCESS;
	uint32_t int_result = 0;
	uint32_t int_request = 0;
	size_t host_bits = 0;

	assert(dhcp);
	assert(result_ip);
	
	if(dhcp->root->is_subtree_used == TRUE)  
	{
		return NO_FREE_IP;
	}

	host_bits = IP_BITS - dhcp->bits_in_subnet;

	if(requested_ip)
	{
		int_request = htonl(*(uint32_t*)requested_ip->ip);
		if(int_request >> host_bits != 
		  (htonl(*(uint32_t*)dhcp->subnet_ip.ip) >> host_bits))
		{
			return IP_DOESNT_EXIST;
		}
		stat = RequestRec(dhcp->root, &int_request, &int_result, host_bits);
	}	

	if(DIFFERENT == stat || NULL == requested_ip)
	{
		int_result = 0;
		stat = GetLowestIp(dhcp->root, &int_result, host_bits);
		if(SUCCESS == stat && requested_ip)
		{
			stat = DIFFERENT;
		}
	}
	
	int_result |= htonl(*(uint32_t*)dhcp->subnet_ip.ip);
	*(uint32_t*)result_ip->ip = ntohl(int_result);

	return stat;
}	


/***************************ReleaseRec***************************************/
static status_t ReleaseRec(node_t* node, uint32_t* req_ip, int bits)
{
	status_t stat = SUCCESS;
	int res = (*req_ip >> (bits - 1)) & MASK;
	
	if(0 == bits)
	{
		if(FALSE == node->is_subtree_used)
		{
			return DOUBLE_FREE;
		}
		node->is_subtree_used = FALSE;
		return SUCCESS;
	}

	if((0 == res && NULL == node->left) ||
	   (1 == res && NULL == node->right))
	{
		return IP_DOESNT_EXIST;
	}

	if(0 == res)
	{
		stat = ReleaseRec(node->left, req_ip, bits - 1);
	}	
	else
	{
		stat = ReleaseRec(node->right, req_ip, bits -1);
	}	

	if(stat == SUCCESS)
	{
		node->is_subtree_used = FALSE;	
	}

	return stat;	
}


/***************************DHCPRelease***************************************/
status_t DHCPRelease(dhcp_t* dhcp, ip_t* ip)
{	
	uint32_t int_ip = 0;
	size_t host_bits = 0;
	
	assert(dhcp);

	host_bits = IP_BITS - dhcp->bits_in_subnet;
	int_ip = htonl(*(uint32_t*)ip->ip);
	if(int_ip >> host_bits != htonl(*(uint32_t*)dhcp->subnet_ip.ip) >> host_bits)
	{
		return IP_DOESNT_EXIST;
	}

	return ReleaseRec(dhcp->root, &int_ip, host_bits);
}


/***************************CountUsed************************************/
static void CountUsed(node_t* node, size_t *count, size_t from_leaf)
{
	if(NULL == node)
	{
		return;
	}

	if(TRUE == node->is_subtree_used)
	{
		*count += (1 << from_leaf);
		return;
	}

	CountUsed(node->left, count, from_leaf - 1);	
	CountUsed(node->right, count, from_leaf - 1);	
}


/***************************DHCPCountFree************************************/
size_t DHCPCountFree(const dhcp_t* dhcp)
{
	size_t used = 0;

	assert(dhcp);

	CountUsed(dhcp->root, &used, IP_BITS - dhcp->bits_in_subnet);

	return (1 << (IP_BITS - dhcp->bits_in_subnet)) - used;
}	


/***************************DHCPStrToIp**************************************/
void DHCPStrToIp(ip_t* dest, const char* src)
{
	int octets[OCTETS] = {0};

	assert(dest);
	assert(src);

	sscanf(src, "%d.%d.%d.%d", &octets[0], &octets[1], &octets[2], &octets[3]);

	dest->ip[0] = (unsigned char)octets[0];
    dest->ip[1] = (unsigned char)octets[1];
    dest->ip[2] = (unsigned char)octets[2];
    dest->ip[3] = (unsigned char)octets[3];
}


/***************************DHCPIpToStr***************************************/
void DHCPIpToStr(char* dest, const ip_t* src)
{
	assert(dest);
	assert(src);

    sprintf(dest, "%u.%u.%u.%u", src->ip[0], src->ip[1], src->ip[2], src->ip[3]);
}


/*****************************************************************************/
/*************************Static Functions************************************/
/*****************************************************************************/

/***************************CheckNode****************************************/
static int CheckNode(node_t* node)
{
	if(NULL == node)
	{
		return 0;
	}

	return node->is_subtree_used == TRUE;
} 


/***************************CreateNode**************************************/
static node_t* CreateNode()
{
	node_t* node = (node_t*)malloc(sizeof(node_t));	
	if(NULL == node)
	{
		return NULL;
	}
	
	node->is_subtree_used = FALSE;
	node->left = NULL;
	node->right = NULL;

	return node;
}	


/***************************GetLowestIp*****************************************/
static status_t GetLowestIp(node_t* node, uint32_t* res_ip, int bits)
{
	status_t stat = SUCCESS;

	if(0 == bits)					 
	{
		node->is_subtree_used = TRUE;
		return stat;
	}

	if(NULL == node->left || FALSE == node->left->is_subtree_used)
	{
		if(NULL == node->left)
		{
			node->left = CreateNode();
			if(NULL == node->left)
			{
				return FAILURE;
			}
		}
		GetLowestIp(node->left, res_ip, bits - 1);	
	}
	else if(NULL == node->right || FALSE == node->right->is_subtree_used)
	{
		if(NULL == node->right)
		{
			node->right = CreateNode();
			if(NULL == node->right)
			{
				return FAILURE;
			}
		}
		*res_ip |= (MASK << (bits - 1));
		stat = GetLowestIp(node->right, res_ip, bits - 1);
	}
	
	if(stat == SUCCESS && 
	   CheckNode(node->left) && CheckNode(node->right))
	{
		node->is_subtree_used = TRUE;	
	}		

	return stat;
}

