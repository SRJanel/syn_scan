##
## Makefile for Makefile in /home/janel/Projects/templates/network/SYN_flooder
##
## Made by Janel
## Login   <XXX@epitech.eu>
##
## Started on  Tue Jul 12 12:19:34 2017 Janel
## Last update Fri Nov  3 02:08:46 2017 
##

SRC	= src/main.c \
	src/options.c \
	src/utils.c \
	src/packet.c \
	src/checksum.c \
	src/send.c \
	src/recv.c \

OBJ	= $(SRC:.c=.o)

NAME	= syn_scan

RM	= rm -f

CC	= gcc -D_GNU_SOURCE

CFLAGS	= -Wall -Wextra -Werror
CFLAGS	+= -ansi # -pedantic-errors
CFLAGS	+= -I./include
#CFLAGS	+= -ggdb3

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
