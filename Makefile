NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -I includes

# Libraries
LIBFT_DIR = libraries/libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBS = -L$(LIBFT_DIR) -lft -lreadline

# Directories
SRC_DIR = srcs
BUILTIN_DIR = $(SRC_DIR)/builtin_src
EXEC_DIR = $(SRC_DIR)/exec_src
OBJ_DIR = objs

# Source files
SRC_MAIN = $(SRC_DIR)/minishell.c $(SRC_DIR)/signals.c $(SRC_DIR)/utilis.c

SRC_BUILTIN = $(BUILTIN_DIR)/builtin_cd_echo_pwd.c \
			  $(BUILTIN_DIR)/builtin_exit_env.c \
			  $(BUILTIN_DIR)/builtin_unset.c \
			  $(BUILTIN_DIR)/builtin_export.c \
			  $(BUILTIN_DIR)/builtin_utils.c \
			  $(BUILTIN_DIR)/export_env.c \
			  $(BUILTIN_DIR)/export_print.c

SRC_EXEC = $(EXEC_DIR)/command_executor.c \
		   $(EXEC_DIR)/envvar.c \
		   $(EXEC_DIR)/envvar_utils.c \
		   $(EXEC_DIR)/executor_pipe.c \
		   $(EXEC_DIR)/executor_utils.c \
		   $(EXEC_DIR)/heredoc.c \
		   $(EXEC_DIR)/path_utils.c \
		   $(EXEC_DIR)/redirections.c

# All source files
SRCS = $(SRC_MAIN) $(SRC_BUILTIN) $(SRC_EXEC)

# Create object file paths
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

all: $(NAME)

# Create directories
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Build libft
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

# Build minishell
$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
