/*
** packet.c<syn_scan> for packet
** 
** Made by SRJanel
** Login SRJanel <n******.******s@epitech.eu>
** 
** Started on  Sun Oct 15 03:19:11 2017 
** Last update Fri Nov  3 01:45:28 2017 
*/

#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include "utils.h"

static char		build_ip_header(unsigned char * const packet,
					const struct in_addr target_ip_address)
{
  struct iphdr		*ip_header;
  
  ip_header = (struct iphdr *)packet;
  ip_header->ihl = 5;
  ip_header->version = 4;
  ip_header->ttl = RANDOM_NBR_RANGE(64, 255);
  ip_header->protocol = IPPROTO_TCP;
  ip_header->id = htons(RANDOM_NBR_RANGE(0, 0xFFFF));
  ip_header->tot_len = sizeof(struct iphdr) + sizeof(struct tcphdr);
  ip_header->daddr = target_ip_address.s_addr;
  return (1);
}

static char	build_tcp_header(unsigned char * const packet)
{
  struct tcphdr	*tcp_header;

  tcp_header = (struct tcphdr *)(packet + sizeof(struct iphdr));
  tcp_header->dest = htons(4242);
  tcp_header->doff = 5;
  tcp_header->syn = 1;
  return (1);
}

char		build_packet(unsigned char * const packet,
			     const struct in_addr target_ip_address)
{
  return (build_ip_header(packet, target_ip_address)
	  && build_tcp_header(packet));
}
