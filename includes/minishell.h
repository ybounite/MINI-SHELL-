/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamezoua <bamezoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 09:10:58 by ybounite          #+#    #+#             */
/*   Updated: 2025/05/13 13:09:57 by bamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ************************************************************************** */
/*                                   INCLUDES                                 */
/* ************************************************************************** */
# include "../libraries/getline/get_next_line.h"
# include "../libraries/libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

/* ************************************************************************** */
/*                                   DEFINES                                  */
/* ************************************************************************** */
# define YELLOW "\e[1;33m"
# define RED "\e[1;31m"
# define GREEN "\e[1;32m"
# define BLUE "\e[1;34m"
# define WHITE "\e[1;37m"
# define MINISPELL "\e[1;32m➜ \e[1;34m minishell\e[0m "

/* ************************************************************************** */
/*                                 DATA TYPES                                 */
/* ************************************************************************** */
typedef enum en_type
{
	CMD,                // command
	REDIRECTION,        // generic redirection
	INPUT_REDIRECTION,  // <
	OUTPUT_REDIRECTION, // >
	APPEND_REDIRECTION, // >>
	HERE_DOCUMENT,      // <<
	BUILTINS,           // builtin commands
	DOUBLE_QUOTE = 34,  // "
	DOLLAR = 36,        // $
	SINGLE_QUOTE = 39,  // '
	ASTERISK = 42,      // *
	PIPE = 124,         // |
}								en_status;

/* Linked list structure for token stream */
typedef struct s_environement_list
{
	en_status					type;
	bool						cat;
	char						*value;
	struct s_environement_list	*next;
}								t_env_lst;

/* Main shell data structure */
typedef struct s_string
{
	char						*line;
	int							size;
	char						**tokens;
	bool						is_error;
	bool						is_pipe;
	bool						is_redirection;
	bool						is_builtin;
	bool						is_parenthesis;
	bool						is_heredoc;
	char						**expand_args;
	char						*heredoc_file;
	int							heredoc_fd;
	int							exit_status;
	char						**g_envp;
	bool						ischild;
	t_env_lst					*head;
	int							signals_flag;
}								t_string;

typedef struct s_process_args
{
	t_string					*st_string;
	t_env_lst					**list;
	int							*prev_fd;
	pid_t						*pids;
	int							i;
	int							cmd_count;
}								t_process_args;

typedef struct s_pipeline_data
{
	int							prev_fd;
	t_env_lst					*list;
	pid_t						*pids;
	int							cmd_count;
}								t_pipeline_data;

/* ************************************************************************** */
/*                               GLOBAL FUNCTIONS                             */
/* ************************************************************************** */
struct s_string					*data_struc(void);
char							*get_line(void);
int								handle_input_syntax(t_string *st_string);
void							start_shell_session(t_string input);

/* ************************************************************************** */
/*                              MEMORY MANAGEMENT                             */
/* ************************************************************************** */
void							*ft_malloc(size_t size, short option);
void							memory_released(t_list **head);
void							free_list(t_env_lst *head);
void							ft_free_split(char **split);
void							ft_destroylist(t_env_lst *list);

/* ************************************************************************** */
/*                               SIGNAL HANDLING                              */
/* ************************************************************************** */
void							assign_signals_handler(void);
void							setup_signals(void);
void							handler(int signum);
void							set_signals_for_execution(void);
void							set_signals_for_heredoc(void);
void							reset_signals(void);
void							handler_heredoc_sig(int signum);

/* ************************************************************************** */
/*                               STRING UTILITIES                             */
/* ************************************************************************** */
char							*ft_strjoin_char(char *str, char c);
bool							is_operator(char c);
bool							find_space(char c);
bool							isquotes(char c);
bool							isemtyqoutes(char *str, int i);
void							ft_skip_whitespace(char *str, int *index);
int								skip_strqoutes(char *str, int *inedx,
									char quotes);
int								ft_lenword(char *str);
char							*ft_remove_quotes(char *str);
bool							is_quotes_thes_str(char *str);
char							*collapse_spaces(const char *str);

/* ************************************************************************** */
/*                               SYNTAX CHECKING                              */
/* ************************************************************************** */
void							ft_puterror(char error);
bool							is_first_operation_pipe(char *str);
bool							is_last_operation_pipe(char *str);
bool							handler_syntax_error(char *line);
int								lenqoutes(char *str, int *i);
int								lenoperator(char *str, int *i);

/* ************************************************************************** */
/*                                 LEXER/PARSER                               */
/* ************************************************************************** */
/* Splitter Functions */
char							**spliter(char *line);
int								ft_lenoperator(char *str, int *index);
void							skip_whiteword(char *str, int *i);
int								lentcommand(char *line);
char							ft_skip_whitword(char *str, int *index);
char							ft_skip_whitquotes(char *str, int *index);
char							ft_skip_whitoperator(char *str, int *index);

/* Token Functions */
void							tokenize(char **tokins, t_env_lst **list);
en_status						get_redirection_type_from_str(char *str);
en_status						get_token_type(char *str);
t_env_lst						*ft_newnode(char *cmd, en_status state);
void							lstadd_back(t_env_lst **head, t_env_lst *new);
void							ft_add_newtoken(t_env_lst **head, char *token,
									en_status state);
void							print_lst_tokens(t_env_lst *head);

/* Handler Functions */
int								lentword(char *str, int start);
void							handler_words(t_env_lst **list, char *str,
									int *i, en_status state);
void							handler_operator(t_env_lst **list, char *str,
									int *i, en_status state);
int								lenofwords_qoutes(char *str, int start);
void							handler_qoutes(t_env_lst **list, char *str,
									int *i, en_status state);
void							process_quoted_string_with_expansion(t_env_lst **list,
									char *str, int *i, en_status state);

/* ************************************************************************** */
/*                               VARIABLE EXPANSION                           */
/* ************************************************************************** */
char							*expand_string(const char *str,
									bool *is_spliting);
char							*get_variable_name(const char *str, int *i);
char							*get_variable_value(char *var_name);
int								expand_variables(t_env_lst **list);
char							*get_env_value(char *var_name,
									t_string *st_string);
int								is_valid_key(char *s);

/* ************************************************************************** */
/*                                  HEREDOC                                   */
/* ************************************************************************** */
int								handler_heredoc(t_env_lst *list);
int								handle_forked_process(char *delimiter,
									bool dolar);
int								read_and_process_heredoc_input(char *delimiter,
									bool expand);
char							*ft_expand(char *line);
bool							is_heredoc(t_env_lst *list);

/* Heredoc Utils */
int								open_heredoc(void);
bool							ft_isheredoc(t_env_lst *list);
char							*find_delimiter(t_env_lst *list,
									int *is_expand);
bool							ft_clculate_heredoc(t_env_lst *list);
char							*expand_heredoc(char *str);
void							error_herdoc(char *delimiter);
char							*creatr_file_name(int fd);
char							*create_temp_file(void);

/* ************************************************************************** */
/*                                  EXECUTION                                 */
/* ************************************************************************** */
/* Command Execution */
void							execute_command(t_string *st_string);
void							execute_pipeline(t_string *st_string);
int								is_builtin(char *cmd);
void							execute_builtin(char **args,
									t_string *st_string);
int								has_pipe(t_env_lst *list);
char							**git_array(t_env_lst **list);

/* Redirection Handling */
int								redirections(char **args);
int								handle_output_redirection(char **args, int *i);

/* Pipeline Utilities */
t_pipeline_data					*init_pipeline_data(t_string *st_string);
void							process_command(t_process_args *args);
int								setup_pipe(int pipe_fd[2], t_env_lst *list);
int								create_process(pid_t *pid);
void							handle_parent_process(int *prev_fd,
									int *pipe_fd, pid_t pid, int *status);
void							update_exit_status(int status);
void							wait_for_children(pid_t *pids, int cmd_count);
void							setup_command_pipe(int *pipe_fd,
									t_env_lst **list, int i, int cmd_count);
void							manage_child_process(t_string *st_string,
									int prev_fd, int *child_pipe, char **args);
void							handle_pipe_fds(int *pipe_fd, int *prev_fd,
									int i, int cmd_count);
void							setup_child_pipe(int **child_pipe, int *pipe_fd,
									int i, int cmd_count);

/* Child Process Handling */
void							handle_child_process(char **args, int prev_fd,
									int *pipe_fd, t_string *st_string);
void							handle_command_path(char **args,
									t_string *st_string);
char							*find_path(char *cmd, char **envp);
int								handle_directory_error(char **args);
int								handle_permission_error(char **args);
int								handle_no_file_error(char **args);

/* ************************************************************************** */
/*                               BUILTIN COMMANDS                             */
/* ************************************************************************** */
void							builtin_echo(char **args, t_string *st_string);
void							builtin_cd(char **args, t_string *st_string);
void							builtin_pwd(void);
void							builtin_exit(char **args, t_string *st_string);
void							builtin_unset(char **args, t_string *st_string);
void							builtin_export(char **args,
									t_string *st_string);
void							builtin_env(t_string *st_string);

/* CD Utilities */
char							*get_oldpwd(t_string *st_string);
void							update_oldpwd(char *old_pwd,
									t_string *st_string);
void							update_pwd(t_string *st_string);
void							update_pwd_env(t_string *st_string);
char							*handle_home(void);

/* Export Utilities */
char							**create_env_copy(t_string *st_string);
void							print_env_entry(char *entry);
void							print_export(t_string *st_string);
char							*extract_key(char *arg, int *key_len);
char							*create_entry(char *arg, int key_len);
void							sort_env(char **env);
int								env_len(t_string *st_string);
void							add_or_update(char *arg, t_string *st_string);
int								update_existing_entry(char *key, int key_len,
									char *entry, t_string *st_string);
void							add_new_entry(char *entry, t_string *st_string);

#endif