/*
** checksum.c for checksum
** 
** Made by SRJanel
** Login SRJanel <n******.******s@epitech.eu>
** 
** Started on  Sun Oct 15 22:40:33 2017 
** Last update Fri Nov  3 01:46:09 2017 
*/

#include <string.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include "syn_scan.h"

/*
** This function is taken from
** somewhere on the internet
*/
unsigned short		csum(unsigned short *ptr, int nbytes)
{
  register long		sum;
  unsigned short	oddbyte;

  sum = 0;
  while (nbytes > 1)
    {
      sum += *ptr++;
      nbytes -= 2;
    }
  if (nbytes == 1)
    {
      oddbyte = 0;
      *((unsigned char *)&oddbyte) = *(unsigned char *)ptr;
      sum += oddbyte;
    }
  sum = (sum >> 16) + (sum & 0xFFFF);
  sum = sum + (sum >> 16);
  return ((short)~sum);
}

static void		build_tcp_pseudoheader(t_tcp_pseudoheader *tcp_pseudoheader,
					       struct iphdr *ip_header,
					       struct tcphdr *tcp_header)
{
  tcp_pseudoheader->source_address = ip_header->saddr;
  tcp_pseudoheader->destination_address = ip_header->daddr;
  tcp_pseudoheader->reserved = 0;
  tcp_pseudoheader->protocol = IPPROTO_TCP;
  tcp_pseudoheader->tcp_segment_length = htons(sizeof(struct tcphdr));
  memcpy(&tcp_pseudoheader->tcp_header, tcp_header, sizeof(struct tcphdr));
}

void			checksum_packets(struct iphdr *ip_header, struct tcphdr *tcp_header)
{
  t_tcp_pseudoheader	tcp_pseudoheader;

  tcp_header->check = 0;
  ip_header->check = 0;
  build_tcp_pseudoheader(&tcp_pseudoheader, ip_header, tcp_header);
  ip_header->check = csum((unsigned short *)ip_header, sizeof(ip_header->tot_len >> 1));
  tcp_header->check = csum((unsigned short *)&tcp_pseudoheader, sizeof(t_tcp_pseudoheader));
}
