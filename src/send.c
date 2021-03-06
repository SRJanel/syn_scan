/*
** send.c for send
** 
** Made by SRJanel
** Login SRJanel <n******.******s@epitech.eu>
** 
** Started on  Thu Nov  2 12:29:46 2017 
** Last update Mon Dec  4 16:32:24 2017 
*/

#include <unistd.h>
#include <stdint.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "syn_scan.h"
#include "utils.h"

char			send_target(const int sd, struct sockaddr_in dest_addr,
				    const uint32_t source_addr, const size_t port)
{
  unsigned char		packet[IP_MAXPACKET] = {0};
  struct tcphdr		*tcphdr;
  struct iphdr		*iphdr;

  if (!build_packet(packet, dest_addr.sin_addr))
    return (PRINT_ERROR("Could not build packet"), 0);
  tcphdr = (struct tcphdr *)(packet + sizeof(struct iphdr));
  iphdr = (struct iphdr *)packet;
  iphdr->saddr = source_addr;

  tcphdr->source = htons(RANDOM_NBR_RANGE(42, 4242));
  tcphdr->seq = RANDOM_NBR_RANGE(0, 0xFFFF);
  tcphdr->window = htons(RANDOM_NBR_RANGE(1000, 65535));
  tcphdr->dest = htons(port);

  checksum_packets(iphdr, tcphdr);
  dest_addr.sin_port = htons(port);
#ifdef _SECURE_RUN
  return (1);
  (void)sd;
#else
  return (sendto(sd, packet, iphdr->tot_len, 0,
  		 (const struct sockaddr *)&dest_addr, sizeof(struct sockaddr_in)));
#endif /* !_SECURE_RUN */
}
