/*
** recv.c for recv_target
** 
** Made by SRJanel
** Login SRJanel <n******.******s@epitech.eu>
** 
** Started on  Thu Nov  2 14:21:17 2017 
** Last update Fri Nov  3 01:35:22 2017 
*/

#include <stdio.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include "utils.h"

char			recv_target(const int sd,
				    struct sockaddr_in dest_addr,
				    const uint32_t source_addr)
{
  unsigned char         packet[IP_MAXPACKET] = {0};
  struct iphdr		*iphdr;
  struct tcphdr		*tcphdr;

  if (recvfrom(sd, packet, IP_MAXPACKET, 0, (struct sockaddr *)&dest_addr,
	       (socklen_t[1]){sizeof dest_addr}) <= 0)
    return (PRINT_ERROR("Could not receive: "), 0);
  iphdr = (struct iphdr *)packet;
  tcphdr = (struct tcphdr *)(packet + iphdr->ihl * 4);
  if (iphdr->protocol == IPPROTO_TCP && iphdr->daddr == source_addr
      && tcphdr->syn && tcphdr->ack)
    {
      fprintf(stdout, "[+] PORT %d is open\n", ntohs(tcphdr->source));
    }

  /* if (iphdr->protocol == IPPROTO_TCP && iphdr->daddr == source_addr */
  /*     && tcphdr->rst) */
  /*   { */
  /*     fprintf(stdout, "[+] PORT %d is closed\n", ntohs(tcphdr->source)); */
  /*   } */
  return (1);
}
