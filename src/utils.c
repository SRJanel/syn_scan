/*
** utils.c for utils
** 
** Made by SRJanel
** Login SRJanel <n******.******s@epitech.eu>
** 
** Started on  Wed Oct 25 12:44:58 2017 
** Last update Mon Dec  4 16:25:33 2017 
*/

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>

uint32_t		get_iface_ip_addr(const int sd, const char * const interface)

{
  struct ifreq		ifr = {0};

  strncpy(ifr.ifr_name, interface, IFNAMSIZ - 1);
  if (ioctl(sd, SIOCGIFADDR, &ifr) == -1)
    return (0);
#ifdef _DEBUG
  fprintf(stdout, "Local addr: %s\n", inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
#endif /* !_DEBUG */
  return (((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr.s_addr);
}
