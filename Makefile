NAME = minishell
LIBFT_DIR = libraries/libft
LIBFT = $(LIBFT_DIR)/libft.a

# Directories
SRC_DIR = srcs
MEMORY_DIR = $(SRC_DIR)/memory
GETLINE_DIR = libraries/getline
BUILTIN_DIR = $(SRC_DIR)/builtin_src
EXEC_DIR = $(SRC_DIR)/exec_src
PARSING_DIR = $(SRC_DIR)/parsing
EXPAND_DIR = $(SRC_DIR)/expand
OBJ_DIR = obj
INC_DIR = includes

# Source files
SRCS = $(EXEC_DIR)/executor.c \
	   $(EXEC_DIR)/child_process.c \
	   $(EXEC_DIR)/builtin_exec.c \
	   $(EXEC_DIR)/pipeline.c \
	   $(EXEC_DIR)/find_path.c \
	   $(EXEC_DIR)/utils.c \
	   $(EXEC_DIR)/redirections.c \
	   $(EXEC_DIR)/pipeline_utils.c \
	   $(EXEC_DIR)/pipeline_utils2.c \
	   $(EXEC_DIR)/pipeline_commands.c \
	   $(EXEC_DIR)/command_handling.c \
	   $(BUILTIN_DIR)/cd.c \
	   $(BUILTIN_DIR)/echo.c \
	   $(BUILTIN_DIR)/pwd.c \
	   $(BUILTIN_DIR)/exit.c \
	   $(BUILTIN_DIR)/env.c \
	   $(BUILTIN_DIR)/unset.c \
	   $(BUILTIN_DIR)/export.c \
	   $(BUILTIN_DIR)/export_utils.c \
	   $(BUILTIN_DIR)/export_utils2.c \
	   $(BUILTIN_DIR)/sort_env.c \
	   $(BUILTIN_DIR)/cd_utils.c \

SRC_MEM = $(MEMORY_DIR)/allocate_data.c

# Getline source files
SRC_GETLINE = $(GETLINE_DIR)/get_next_line.c 
#$(GETLINE_DIR)/get_next_line_utils.c

# Parsing source files
SRC_PARS = $(PARSING_DIR)/minishell.c \
		   $(PARSING_DIR)/gitline.c \
		   $(PARSING_DIR)/start_shell.c \
		   $(PARSING_DIR)/ft_utilis.c \
		   $(PARSING_DIR)/token_utils.c\
		   $(PARSING_DIR)/handler_syntax_error.c \
		   $(PARSING_DIR)/syntax_error.c \
		   $(PARSING_DIR)/ft_skip_whit_string.c \
		   $(PARSING_DIR)/lexer_handlers_operator.c \
		   $(PARSING_DIR)/lexer_handlers_word.c \
		   $(PARSING_DIR)/ft_node.c \
		   $(PARSING_DIR)/spliter.c \
		   $(PARSING_DIR)/heredoc.c \
		   $(PARSING_DIR)/heredoc_utlis.c \
		   $(PARSING_DIR)/expand_heredoc.c \
		   $(PARSING_DIR)/creatr_file_name.c \
		   $(PARSING_DIR)/error_herdoc.c \
		   $(PARSING_DIR)/destroy_allocation.c \
		   $(PARSING_DIR)/manage_signal.c \
		   $(EXPAND_DIR)/expand_variables.c \
		   $(EXPAND_DIR)/get_variable.c \
		   $(EXPAND_DIR)/expand_string_utils.c \
		   $(EXPAND_DIR)/expand_string.c \
		   $(EXPAND_DIR)/ft_add_expand_variable.c \
		#    $(PARSING_DIR)/expand_utils.c 

# Combine all source files
SRCS += $(SRC_PARS)
SRCS += $(SRC_MEM)
SRCS += $(SRC_GETLINE)  # Add getline sources to the compilation

# Object files
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(filter $(SRC_DIR)/%,$(SRCS)))
OBJS += $(patsubst $(GETLINE_DIR)/%.c,$(OBJ_DIR)/getline/%.o,$(filter $(GETLINE_DIR)/%,$(SRCS)))

CC = cc
RM = rm -rf
CFLAGS = -g -Wall -Wextra -Werror 
INCLUDES = -I$(INC_DIR) -I$(LIBFT_DIR) -I$(GETLINE_DIR)

all: $(OBJ_DIR) $(LIBFT) $(NAME)

# Create obj directories if they don't exist
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/builtin_src
	@mkdir -p $(OBJ_DIR)/exec_src
	@mkdir -p $(OBJ_DIR)/parsing
	@mkdir -p $(OBJ_DIR)/memory
	@mkdir -p $(OBJ_DIR)/getline

$(LIBFT):
	@make --no-print-directory -C $(LIBFT_DIR)
	@make --no-print-directory -C $(LIBFT_DIR) bonus

# Pattern rule for object files in the main src directory
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Correct pattern rule for object files in getline directory
$(OBJ_DIR)/getline/%.o: $(GETLINE_DIR)/%.c
	@mkdir -p $(dir $@)  # Ensures the 'getline' directory exists
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Add to your Makefile

test_expansion: $(OBJS) tests/test_expansion.c
	$(CC) $(CFLAGS) -o test_expansion $(OBJS) tests/test_expansion.c $(LIBS)
	./test_expansion
	
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
