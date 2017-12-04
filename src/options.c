/*
** options.c for options
** 
** Made by SRJanel
** Login SRJanel <n******.******s@epitech.eu>
** 
** Started on  Sat Oct 14 21:53:05 2017 
** Last update Mon Dec  4 17:02:55 2017 
*/

#include <unistd.h>
#include <getopt.h>
#include "options.h"

struct s_options			get_args(int argc, char **argv)
  {
    int					c;
    int					index;
    struct s_options			options = {.0};
    struct option			long_options[] =
      {
	{"interface", required_argument, NULL, 'i'},
	{"target", required_argument, NULL, 't'},
	{"help", no_argument, &options.help, 1},
	{NULL, 0, NULL, 0}
      };

    while (1)
      {
	if ((c = getopt_long(argc, argv,
			     "t:i:h",
			     long_options, &index)) == -1)
	  break ;
	if (optarg && *optarg == '-') continue ;
	if (c == 'i')
	  options.interface = optarg;
	else if (c == 't')
	  options.target = optarg;
	else if (c == 'h' || c == '?')
	  options.help = 1;

      }
    return (options);
}
