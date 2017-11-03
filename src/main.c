/*
** main.c for main
** 
** Made by SRJanel
** Login SRJanel <n******.******s@epitech.eu>
** 
** Started on  Thu Nov  2 01:24:45 2017 
** Last update Fri Nov  3 02:00:56 2017 
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
  return (EXIT_SUCCESS);  
}
