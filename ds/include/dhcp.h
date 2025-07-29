/* *****************************
 Name:     Alon Nov
 Exercise: DHCP
 Date:	   18.12.2024   
 Reviewer: Shani Davidian

********************************/
					
#ifndef _DHCP_H_ 
#define _DHCP_H_

#include <stddef.h> /* size_t */

#define OCTETS (4)

typedef struct dhcp dhcp_t;

typedef struct ip
{
    unsigned char ip[OCTETS]; 
}ip_t;

typedef enum status
{
    SUCCESS,
    FAILURE,
    IP_DOESNT_EXIST,
    DIFFERENT,
    NO_FREE_IP,
    DOUBLE_FREE
}status_t;


/*@Desc - creates a Dynamic Host Configuration Protocol (DHCP) 
* @Params - subnet_ip: network part of IP
* @Params - bits_in_subnet: number of bits designated for subnet
* @Return - pointer to the created DHCP
* @Return - NULL, if creation fails
* @Warning - bits_in_subnet must be no larger than 30
* @Warning - all bits in subnet_ip after bits_in_subnet will be reset
* @Warning - lowest and highest ip addresses are used by the system
* @time complexity - O(1)  
* @Space complexity - O(1) */
dhcp_t* DHCPCreate(ip_t subnet_ip, size_t bits_in_subnet);


/*@Desc - frees the given DHCP
* @Params - dhcp: dhcp to destroy
* @Return - N/A
* @Warning - if dhcp param is not a pointer to a valid DHCP, can cause UB
* @time complexity - O(n)  
* @Space complexity - O(1) */
void DHCPDestroy(dhcp_t* dhcp);


/*@Desc - requests an IP address from the DHCP
* @Params - dhcp: dhcp to request IP address from 
* @Params - requested_ip: specific IP to request, 
			can be NULL to request a non specific IP 
* @Return - SUCCESS on success
* @Return - FAILURE on internal error
* @Return - DIFFERENT if a different IP than the one requested is assigned
* @Return - IP_DOESNT_EXIST if requested_ip subnet is different than dhcp subnet
* @Return - NO_FREE_IP if there are no free IPs in dhcp's range
* @Warning - if dhcp param is not a pointer to a valid dhcp, can cause UB
* @Warning - if res_ip param is a is not a pointer to a valid ip_t, can cause UB
* @time complexity - O(1) 
* @Space complexity - O(1) */
status_t DHCPRequest(dhcp_t* dhcp, ip_t* requested_ip, ip_t* res_ip);


/*@Desc - requests to release an IP address previously assigned by the given DHCP
* @Params - dhcp: dhcp to request release of IP address from
* @Params - ip: IP address to request release of
* @Return - SUCCESS on success
* @Return - FAILURE on internal error
* @Return - IP_DOESNT_EXIST if ip is not assigned or not in dhcp's range
* @Return - DOUBLE_FREE if ip has already been released
* @Warnings - if dhcp param is not a pointer to a valid dhcp, can cause UB  
* @time complexity - O(1)  
* @Space complexity - O(1) */
status_t DHCPRelease(dhcp_t* dhcp, ip_t* ip);


/*@Desc - gets the number of unassigned IP addresses the DHCP can assign
* @Params - dhcp: DHCP to get number of free IP addresses in
* @Return - number of unassigned IP addresses
* @Warnings - N/A
* @time complexity - O(1)
* @Space complexity - O(1) */
size_t DHCPCountFree(const dhcp_t* dhcp);


/*@Desc - tanslates an IP address written as a string in IPv4 format
		  to an ip_t struct
* @Params - dest: ip_t struct to write to
* @Params - src: string to translate
* @Return - N/A
* @Warnings - if dest param is not a pointer to a valid ip_t, can cause UB
* @Warnings - if src param is not a pointer to a valid string, can cause UB
* @time complexity - O(1)  
* @Space complexity - O(1) */
void DHCPStrToIp(ip_t* dest, const char* src);


/*@Desc - tanslates an IP address written as an ip_t struct to a 
		  string in IPv4 format
* @Params - dest: string to write to 
* @Params - src: ip_t struct to translate
* @Return - N/A
* @Warnings - if dest param is not a pointer to a valid string, can cause UB
* @Warnings - if src param is not a pointer to a valid ip_t, can cause UB
* @time complexity - O(1)  
* @Space complexity - O(1) */
void DHCPIpToStr(char* dest, const ip_t* src);


#endif /* DHCP_H */
