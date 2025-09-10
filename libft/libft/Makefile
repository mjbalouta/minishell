# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/02 18:50:42 by mjoao-fr          #+#    #+#              #
#    Updated: 2025/07/18 19:37:41 by mjoao-fr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#defining that when the variable CC is used, the compiler will be cc
CC = cc

#declaring that the variable CFLAGS will use the flags below everytime it's called in the program
CFLAGS = -Wall -Wextra -Werror -g

#listing the sources used by the program
SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_recalloc.c ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

#name of the executable
NAME = libft.a

#rule to create objs
OBJS = $(SRCS:.c=.o)
 
all: $(NAME)

#rule to create the static library libft.a from object files .o
$(NAME): $(OBJS)
	@@echo "Compiling all files..."
	@ar rcs $(NAME) $(OBJS) #ar creates a static library. r adds the files, c creactes the archive and s creates an index for the library to speed up linking.

#defining the rule to compile .c files into object .o files
%.o: %.c libft.h #any .o file will be created with the correspondent .c file
	@$(CC) $(CFLAGS) -c $< -o $@ 
#-c prevents it from creating an executable (only created with linking .o objects after. $< represents .c file and -o $@ represents the .o file

#clean rule (removes .o files, but not the static library)
clean:
	@@echo "Removing objects..."
	@rm -f $(OBJS) #-f forces the removal of files supressing possible errors

fclean: clean #removes objects and library
	@@echo "Removing library..."
	@rm -f $(NAME)

re: fclean $(NAME) #recompiles everything

.PHONY: all clean fclean re

