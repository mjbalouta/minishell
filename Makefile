# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/20 16:10:57 by mjoao-fr          #+#    #+#              #
#    Updated: 2025/10/20 16:10:58 by mjoao-fr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC          	= cc
NAME        	= minishell
INCLUDES_PATH	= includes
INCLUDES		= -I$(INCLUDES_PATH)
CFLAGS      	= -Wall -Wextra -Werror -I$(LIBFT_DIR) $(INCLUDES) -g
SRCS			= $(addprefix srcs/, \
				main.c \
				shell/shell_utils.c \
				shell/shell_utils2.c \
				tokenizer/tokenizer.c \
				tokenizer/tokenizer2.c \
				tokenizer/tokenizer_lst_utils.c \
				tokenizer/tokenizer_utils.c \
				environment/environment.c \
				environment/envp_lst_utils.c \
				environment/envp_lst_utils2.c \
				environment/envp_utils.c \
				environment/envp_utils2.c \
				expander/expander.c \
				expander/expander_utils.c \
				parsing/command_list.c \
				parsing/verify_tokens.c \
				parsing/verify_commands.c \
				parsing/parsing_utils.c \
				parsing/process_tokens.c \
				execution/build_comm_path.c \
				execution/pipes.c \
				execution/execution_utils.c \
				execution/execution_utils2.c \
				execution/execution_utils3.c \
				execution/handle_redirects.c \
				execution/heredoc.c \
				signals/signals.c \
				signals/signals_heredoc.c \
				signals/signals_child.c \
				builtins/builtins_utils.c \
				builtins/echo.c \
				builtins/cd.c \
				builtins/pwd.c \
				builtins/export.c \
				builtins/export_utils.c \
				builtins/unset.c \
				builtins/env.c \
				builtins/exit.c \
				builtins/exit_utils.c \
				)
OBJS       		= $(SRCS:.c=.o)
LIBFT_DIR   	= ./libft
LIBFT       	= $(LIBFT_DIR)/complete_libft.a
READLINE_PATH	= vendor/readline/
RLFLAG 			= -L$(READLINE_PATH)/lib -lreadline

all: $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) > /dev/null
	
%.o: %.c minishell.h
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(LIBFT) $(OBJS)
	@echo "Compiling..."
	@$(CC) $(CFLAGS) $(OBJS) $(RLFLAG) $(LIBFT) -o $(NAME)

valgrind: 
	@echo "{\n   leak readline\n   Memcheck:Leak\n...\n   fun:readline\n}\n{\n   leak add_history\n   Memcheck:Leak\n...\n   fun:add_history\n}" > readline.supp
	@valgrind --suppressions=readline.supp --leak-check=full -s --track-origins=yes --show-leak-kinds=all --track-fds=yes ./$(NAME)

clean:
	@echo "Removing objects..."
	@$(MAKE) clean -C $(LIBFT_DIR) > /dev/null
	@rm -f $(OBJS)

fclean: clean
	@echo "Removing executable..."
	@$(MAKE) fclean -C $(LIBFT_DIR) > /dev/null
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
