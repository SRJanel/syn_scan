/*
** main.c for main
** 
** Made by SRJanel
** Login SRJanel <n******.******s@epitech.eu>
** 
** Started on  Thu Nov  2 01:24:45 2017 
** Last update Fri Nov  3 01:57:53 2017 
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
  return (EXIT_SUCCESS);  
}
