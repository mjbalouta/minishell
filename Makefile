CC          	= cc
CFLAGS      	= -Wall -Wextra -Werror -I$(LIBFT_DIR) -g
NAME        	= minishell
SRCS			= main.c init.c
OBJS       		= $(SRCS:.c=.o)
LIBFT_DIR   	= ./libft
LIBFT       	= $(LIBFT_DIR)/complete_libft.a
READLINE_PATH	= vendor/readline/
RLFLAG 			= -L$(READLINE_PATH)/lib -lreadline

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@echo "Compiling..."
	@$(CC) $(CFLAGS) $(OBJS) $(RLFLAG) $(LIBFT) -o $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) > /dev/null

%.o: %.c minishell.h
	@$(CC) $(CFLAGS) -c $< -o $@

valgrind: 
	@echo "{\n   leak readline\n   Memcheck:Leak\n...\n   fun:readline\n}\n{\n   leak add_history\n   Memcheck:Leak\n...\n   fun:add_history\n}" > readline.supp
	@valgrind --suppressions=readline.supp --leak-check=full -s --show-leak-kinds=all ./$(NAME)

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