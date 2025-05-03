NAME = minishell
LIBFT_DIR = libraries/libft
LIBFT = $(LIBFT_DIR)/libft.a

# Directories
SRC_DIR = srcs
MEMORY_DIR = $(SRC_DIR)/memory
BUILTIN_DIR = $(SRC_DIR)/builtin_src
EXEC_DIR = $(SRC_DIR)/exec_src
PARSING_DIR = $(SRC_DIR)/parsing
OBJ_DIR = obj
INC_DIR = includes

# Source files
SRCS = $(SRC_DIR)/utilis.c \
       $(EXEC_DIR)/executor.c \
       $(EXEC_DIR)/child_process.c \
       $(EXEC_DIR)/builtin_exec.c \
       $(EXEC_DIR)/pipeline.c \
       $(EXEC_DIR)/find_path.c \
       $(EXEC_DIR)/utils.c \
       $(EXEC_DIR)/redirections.c \
       $(BUILTIN_DIR)/cd.c \
       $(BUILTIN_DIR)/echo.c \
       $(BUILTIN_DIR)/pwd.c \
       $(BUILTIN_DIR)/exit.c \
       $(BUILTIN_DIR)/env.c \
       $(BUILTIN_DIR)/unset.c \
       $(BUILTIN_DIR)/export.c

SRC_MEM = $(MEMORY_DIR)/allocate_data.c

# Parsing source files
SRC_PARS = $(PARSING_DIR)/minishell.c \
           $(PARSING_DIR)/lexer_handler_qoutes.c \
           $(PARSING_DIR)/lexer_handlers_operator.c \
           $(PARSING_DIR)/lexer_handlers_word.c \
           $(PARSING_DIR)/lexer_dollar_handlers.c \
           $(PARSING_DIR)/gitline.c \
           $(PARSING_DIR)/ft_utlis.c \
           $(PARSING_DIR)/ft_lenstr.c \
           $(PARSING_DIR)/ft_spliter.c \
           $(PARSING_DIR)/token_type_utils.c \
           $(PARSING_DIR)/ft_node.c \
           $(PARSING_DIR)/ft_free.c \
           $(PARSING_DIR)/manage_signal.c \
           $(PARSING_DIR)/start_shell.c \
           $(PARSING_DIR)/heredoc.c 

# Combine all source files
SRCS += $(SRC_PARS)
SRCS += $(SRC_MEM)

# Object files (replacing the directory path with OBJ_DIR)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

CC = cc -Wall -Wextra -Werror
RM = rm -rf
CFLAGS = -g #-Wall -Wextra -Werror 
INCLUDES = -I$(INC_DIR) -I$(LIBFT_DIR)

all: $(OBJ_DIR) $(LIBFT) $(NAME)

# Create obj directories if they don't exist
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/builtin_src
	@mkdir -p $(OBJ_DIR)/exec_src
	@mkdir -p $(OBJ_DIR)/parsing
	@mkdir -p $(OBJ_DIR)/memory

$(LIBFT):
	@make --no-print-directory -C $(LIBFT_DIR)
	@make --no-print-directory -C $(LIBFT_DIR) bonus

# Pattern rule for object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -lreadline -o $(NAME)
	@./.script.sh

clean:
	@$(RM) $(OBJ_DIR)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean
	@echo "\033[32m✔\033[0m Clean completed."

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean
	@echo "\033[32m✔\033[0m Full clean completed."

re: fclean all
