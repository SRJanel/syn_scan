/*
** utils.h<syn_scan> for UTILS_H_
** 
** Made by SRJanel
** Login SRJanel <n******.******s@epitech.eu>
** 
** Started on  Thu Nov  2 12:26:57 2017 
** Last update Mon Dec  4 16:23:50 2017 
*/

#ifndef UTILS_H_
# define UTILS_H_

# include <stdio.h>
# include <stdint.h>
# include <string.h>
# include <stdlib.h>
# include <errno.h>

# define RANDOM_NBR_RANGE(MIN, MAX)	(((MAX > MIN) ?        \
                                           (rand() % (MAX - MIN) + MIN) : \
                                           (rand() % (MIN - MAX) + MAX)))
# define PRINT_ERROR(MESG)		fprintf(stderr, "%s %s @ %s:%s:%d\n", MESG, strerror(errno), \
						__FILE__, __extension__ __FUNCTION__, __LINE__)
# define INSIDE				fprintf(stderr, "INSIDE: %s\n", __FUNCTION__)

uint32_t				get_iface_ip_addr(const int, const char * const);

#endif /* !UTILS_H_ */
