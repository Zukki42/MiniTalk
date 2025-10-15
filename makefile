# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bavirgil <bavirgil@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/13 18:39:57 by bavirgil          #+#    #+#              #
#    Updated: 2025/10/15 14:03:04 by bavirgil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler & flags
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -I.

# Executables
NAME_SERVER = server
NAME_CLIENT = client

# Headers
HEADERS = minitalk.h

# Sources
SRCS_COMMON = bit_utils.c \
              signal_utils.c \
              validate.c \
              error.c \
              sleep_utils.c

SRCS_SERVER = server.c $(SRCS_COMMON)
SRCS_CLIENT = client.c $(SRCS_COMMON)

# Objects
OBJS_SERVER = $(SRCS_SERVER:.c=.o)
OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)

# Tools
RM = rm -f

#curl parrot.live

# Default
all: $(NAME_SERVER) $(NAME_CLIENT)

# Link
$(NAME_SERVER): $(OBJS_SERVER)
	$(CC) $(CFLAGS) $^ -o $@

$(NAME_CLIENT): $(OBJS_CLIENT)
	$(CC) $(CFLAGS) $^ -o $@

# Compile: each .o depends on headers
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	$(RM) $(OBJS_SERVER) $(OBJS_CLIENT)

# Clean all
fclean: clean
	$(RM) $(NAME_SERVER) $(NAME_CLIENT)

# Rebuild
re: fclean all

.PHONY: all clean fclean re
