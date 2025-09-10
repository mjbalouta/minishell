# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/02 15:31:27 by mjoao-fr          #+#    #+#              #
#    Updated: 2025/06/02 15:31:27 by mjoao-fr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC 			= cc
CFLAGS		= -Wall -Wextra -Werror -I./Libft -g
NAME		= complete_libft.a

SRCS		= ./get-next-line/get_next_line.c ./get-next-line/get_next_line_utils.c ./get-next-line/get_next_line_utils2.c
OBJS		= $(SRCS:.c=.o)
LIBFT_DIR 	= ./libft
LIBFT 		= ./libft/libft.a
PRINTF_DIR 	= ./printf
PRINTF 		= ./printf/libftprintf.a

all: $(NAME) 

$(NAME): $(LIBFT) $(PRINTF) $(OBJS)
	@echo "Building libft..."
#removes the old static library (if it exists) to prevent duplicates -f avoids errors if file doesn't exist
	@rm -f $(NAME)
#-rf deletes everything inside the folder and the folder recursively
	@rm -rf temp
#creates temporary folder and -p prevents an error if the folder already exists
	@mkdir -p temp
#copies obj files from gnl to the folder
	@cp $(OBJS) temp/
#changes directory to the folder and extracts object files from libft.a (ar x unpacks .a archive files into .o files)
	@cd temp && ar x ../$(LIBFT)
	@cd temp && ar x ../$(PRINTF)
#re-archives all previous .o files into the final .a library
	@ar rcs $(NAME) temp/*.o
	@ranlib $(NAME)
	@rm -rf temp

$(LIBFT): $(LIBFT_SRC)
#libft depends on libft_dir: if libft is out of date, make will update it
#this make refers to the libft makefile (-C tells make to change directory to libft_dir)
	@$(MAKE) -C $(LIBFT_DIR) > /dev/null
	
$(PRINTF): $(PRINTF_SRC)
#libft depends on libft_dir: if libft is out of date, make will update it
#this make refers to the libft makefile (-C tells make to change directory to libft_dir)
	@$(MAKE) -C $(PRINTF_DIR) > /dev/null

%.o: %.c ./get-next-line/get_next_line.h
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Removing objects..."
#/dev/null cleans commands from the output
	@$(MAKE) clean -C $(LIBFT_DIR) > /dev/null
	@$(MAKE) clean -C $(PRINTF_DIR) > /dev/null
	@rm -f $(OBJS) 

fclean: clean
	@@echo "Removing library..."
	@$(MAKE) fclean -C $(LIBFT_DIR) > /dev/null
	@$(MAKE) fclean -C $(PRINTF_DIR) > /dev/null
	@rm -f $(NAME)

re: fclean $(NAME) all

.PHONY: all clean fclean re
