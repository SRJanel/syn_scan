/*
** main.c for main
** 
** Made by SRJanel
** Login SRJanel <n******.******s@epitech.eu>
** 
** Started on  Thu Nov  2 01:24:45 2017 
** Last update Fri Nov  3 02:05:15 2017 
*/

#include <unistd.h>
#include <net/if.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "syn_scan.h"
#include "options.h"
#include "utils.h"

__inline__ static void	usage(const char * const prog_name)
{
  fprintf(stderr, "USAGE: %s -t d_addr -i iface\n"			\
          "\t-t, --target\t\tTarget to scan.\n"				\
	  "\t-i, --interface\t\tInterface to use for the scan.\n"	\
          "\t-h, --help\t\tDisplays this message.\n", prog_name);
}

__inline__ static char	set_header_ip_inclusion(const int sd)
{
  return ((setsockopt(sd, IPPROTO_IP, IP_HDRINCL,
                      &(int){1}, sizeof(int)))
          ? (perror(__FUNCTION__), 0) : 1);
}

static char		bind_raw_sock(const int sd,
				      const char * const interface)
{
  struct ifreq		ifr = {0};
  struct sockaddr_in	dest_addr;

  dest_addr.sin_family = AF_INET;
  dest_addr.sin_addr.s_addr = get_iface_ip_addr(sd, interface);
  if (bind(sd, (const struct sockaddr *)&dest_addr, sizeof dest_addr))
    goto error_exit;
  strncpy(ifr.ifr_ifrn.ifrn_name, interface, IFNAMSIZ - 1);
  if (!setsockopt(sd, SOL_SOCKET, SO_BINDTODEVICE, interface, strlen(interface)))
    return (1);
 error_exit:
  perror(__FUNCTION__);
  return (0);
}

char			loop(const int sd,
			     const struct s_options options)
{
  struct sockaddr_in	destination_address;
  fd_set		read_fds, write_fds;
  uint32_t		source_ip_addr;
  size_t		port;

  destination_address.sin_family = AF_INET;
  if ((destination_address.sin_addr.s_addr = inet_addr(options.target)) == INADDR_NONE
      || !(source_ip_addr = get_iface_ip_addr(sd, options.interface)))
    return (PRINT_ERROR("ERROR could not set ipaddr"), 0);
  port = 0;
  FD_ZERO(&write_fds);
  FD_ZERO(&read_fds);
  FD_SET(sd, &read_fds);

  /*
  ** MAX_NBR_PORT * 3 is an attempt to wait for
  ** some lasts packets to receive after the last
  ** packet was sent. Haven't test it on a connection
  ** where propagation delay is high.
  ** If you have a better approach, please do comment.
  */
  while (++port <= MAX_NBR_PORT * 3)
    {
      FD_SET(sd, &write_fds);
      FD_SET(sd, &read_fds);
      if (select(sd + 1, &read_fds, &write_fds, NULL, NULL/* &(struct timeval){0, 900000} */) == -1)
      	return (PRINT_ERROR("select"), 0);
      if (FD_ISSET(sd, &read_fds)
      	  && recv_target(sd, destination_address, source_ip_addr) == -1)
      	return (PRINT_ERROR("Error recv"), 0);
      else if (port <= MAX_NBR_PORT && FD_ISSET(sd, &write_fds)
      	       && send_target(sd, destination_address, source_ip_addr, port) <= 0)
      	return (PRINT_ERROR("Error send"), 0);
    }
  close(sd);
  return (1);
}

int			main(int argc, char *argv[])
{
  struct s_options	options;
  int			sd;
  
  options = get_args(argc, argv);
  if (!options.interface || !options.target
      || options.help)
    return (usage(argv[0]), EXIT_FAILURE);
  if ((sd = socket(AF_INET, SOCK_RAW, IPPROTO_TCP)) == -1)
    return (PRINT_ERROR("Socket Creation"), EXIT_FAILURE);
  if (!set_header_ip_inclusion(sd)
      || !bind_raw_sock(sd, options.interface))
    return (EXIT_FAILURE);  
  loop(sd, options);
  return (EXIT_SUCCESS);  
}
