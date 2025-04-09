NAME = minishell
CC = cc
CFLAGSE = -Wall -Wextra -Werror -g

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC = minishell.c satart_shell.c gitline.c ft_utlis.c ft_lenstr.c ft_spliter.c ft_node.c 

OBJ = $(SRC:.c=.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGSE) $(OBJ) $(LIBFT) -o $(NAME) -lreadline

clean :
	rm -f $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all