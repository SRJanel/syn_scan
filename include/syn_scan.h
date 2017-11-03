/*
** syn_scan.h for SYN_SCAN_H_
** 
** Made by SRJanel
** Login SRJanel <n******.******s@epitech.eu>
** 
** Started on  Thu Nov  2 12:27:44 2017 
** Last update Thu Nov  2 22:08:34 2017 
*/

#ifndef SYN_SCAN_H_
# define SYN_SCAN_H_

# include <netinet/ip.h>
# include <netinet/tcp.h>

# define MAX_NBR_PORT 65535

struct s_options;

typedef struct		s_tcp_pseudoheader
{
  unsigned int		source_address;
  unsigned int		destination_address;
  unsigned char		reserved;
  unsigned char		protocol;
  unsigned short	tcp_segment_length;
  struct tcphdr		tcp_header;
}			t_tcp_pseudoheader;

char			send_target(const int,
				      struct sockaddr_in,
				      const uint32_t,
				      const size_t);
char			recv_target(const int,
				      struct sockaddr_in,
				      const uint32_t);

char			build_packet(unsigned char * const,
				       const struct in_addr);
void			checksum_packets(struct iphdr *, struct tcphdr *);

#endif /* !SYN_SCAN_H_ */
