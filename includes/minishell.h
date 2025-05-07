/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 09:10:58 by ybounite          #+#    #+#             */
/*   Updated: 2025/05/07 19:21:04 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ************************************************************************* */
/*                                   INCLUDES                                */
/* ************************************************************************* */
# include "../libraries/libft/libft.h"
// # include "allocation_manager.h"
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
// # include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include "../libraries/getline/get_next_line.h"
/* ************************************************************************* */
/*                                   DEFINES                                 */
/* ************************************************************************* */
# define YELLOW "\e[1;33m"
# define RED "\e[1;31m"
# define GREEN "\e[1;32m"
# define BLUE "\e[1;34m"
# define WHITE "\e[1;37m"
# define MINISPELL "\e[1;32m➜ \e[1;34m minishell\e[0m "

/* -------------------------------------------------------------------------- */
/*                                 DATA TYPES                                 */
/* -------------------------------------------------------------------------- */

/* Token types for lexical analysis */
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
	char						*strcon;
	int							size;
	char						**tokens;
	bool						is_error;
	bool						is_pipe;
	bool						is_redirection;
	bool						is_builtin;
	bool						is_parenthesis;
	bool						is_heredoc;
	char						*heredoc_file;
	int							heredoc_fd;
	int							exit_status;
	char						**g_envp;
	bool						ischild;
	t_env_lst					*head;
}								t_string;

/* Command execution structure */
/*typedef struct s_exec_cmd
{
	char	*full_path;  // Full command path
	char	*path;       // Command path
	char	**dirs;      // Directory paths
	pid_t	pid;        // Process ID
	char	*cmd_path;   // Command path
	char	**cmd_flags; // Command flags
}								t_exec_cmd;*/
bool							handler_syntax_error(char *line);
char	*expand_string(const char *str);
/* -------------------------------------------------------------------------- */
/*                              GLOBAL FUNCTIONS                              */
/* -------------------------------------------------------------------------- */

struct s_string					*data_struc(void);

/* -------------------------------------------------------------------------- */
/*                              MEMORY MANAGEMENT                             */
/* -------------------------------------------------------------------------- */
void							free_list(t_env_lst *head);
void							ft_free_split(char **split);

/* -------------------------------------------------------------------------- */
/*                                SIGNAL HANDLING                             */
/* -------------------------------------------------------------------------- */

void							assign_signals_handler(void);
void							setup_signals(void);
void							handler(int signum);

/* -------------------------------------------------------------------------- */
/*                                STRING UTILITIES                            */
/* -------------------------------------------------------------------------- */

char							*ft_strjoin_free(char *s1, char *s2);
int								ft_strcmp(const char *s1, const char *s2);
bool							is_operator(char c);
bool							find_space(char c);
bool							isquotes(char c);
bool							isemtyqoutes(char *str, int i);
void							ft_skip_whitespace(char *str, int *index);
int								skip_strqoutes(char *str, int *inedx,
									char quotes);
int								ft_lenword(char *str);
int								is_valid_key(char *s);

/* -------------------------------------------------------------------------- */
/*                               PARSER FUNCTIONS                             */
/* -------------------------------------------------------------------------- */

/* Lexical Analysis */
/* -------------------------------------------------------------------------- */
/*                               allocate_data.c                              */
/* -------------------------------------------------------------------------- */
void							*ft_malloc(size_t size, short option);
void							memory_released(t_list **head);

/* -------------------------------------------------------------------------- */
/*                              get_line.c                                    */
/* -------------------------------------------------------------------------- */
char							*get_line(void);
char							*handler_string(char *line, int size);
void							ft_spliter(t_env_lst **list, char *line);
/* -------------------------------------------------------------------------- */
/*                              spliter.c                                     */
/* -------------------------------------------------------------------------- */
char							**spliter(char *line);
int								ft_lenoperator(char *str, int *index);
void							skip_whiteword(char *str, int *i);
int								lentcommand(char *line);

/* -------------------------------------------------------------------------- */
/*                              token_utils.c                                 */
/* -------------------------------------------------------------------------- */
void							tokenize(char **tokins, t_env_lst **list);
en_status						get_redirection_type_from_str(char *str);
en_status						get_token_type(char *str);

/* Token Management */
t_env_lst						*ft_newnode(char *cmd, en_status state);
void							lstadd_back(t_env_lst **head, t_env_lst *new);
void							ft_add_newtoken(t_env_lst **head, char *token,
									en_status state);
void							print_lst_tokens(t_env_lst *head);

/* Command Processing */
int								handle_input_syntax(t_string *st_string);
void							start_shell_session(t_string input);

/* -------------------------------------------------------------------------- */
/*                              lexer_handlers_word.c                         */
/* -------------------------------------------------------------------------- */
int								lentword(char *str, int start);
void							handler_words(t_env_lst **list, char *str,
									int *i, en_status state);

/* -------------------------------------------------------------------------- */
/*                              lexer_handler_qoutes.c                        */
/* -------------------------------------------------------------------------- */
void							handler_operator(t_env_lst **list, char *str,
									int *i, en_status state);

/* -------------------------------------------------------------------------- */
/*                              lexer_handler_qoutes.c                        */
/* -------------------------------------------------------------------------- */
int								lenofwords_qoutes(char *str, int start);
void							handler_qoutes(t_env_lst **list, char *str,
									int *i, en_status state);
void							process_quoted_string_with_expansion(t_env_lst **list,
									char *str, int *i, en_status state);

/* -------------------------------------------------------------------------- */
/*                              lexer_dollar_handlers.c                       */
/* -------------------------------------------------------------------------- */
int								lendollar(char *str, int start);
char							*handler_expasion(char *var_name);
void							heandler_dollar(t_env_lst **list, char *str,
									int *i, en_status state);
/* -------------------------------------------------------------------------- */
/*                              heredoc.c 					                   */
/* -------------------------------------------------------------------------- */
int								hase_heredoc_rediraection(t_env_lst *head);
int								handle_heredoc(char *delimiter,
									int *heredoc_fd);
int								handler_heredoc(t_env_lst *list);
char							*ft_remove_quotes(char *str);
bool							is_quotes_thes_str(char *str);

/* -------------------------------------------------------------------------- */
/*                              heredoc_utlis.c					                */
/* -------------------------------------------------------------------------- */
int								open_heredoc(void);
bool							ft_isheredoc(t_env_lst *list);
bool	is_heredoc(t_env_lst *list); // delet
char							*find_delimiter(t_env_lst *list,
									int *is_expand);
bool							ft_clculate_heredoc(t_env_lst *list);

/* -------------------------------------------------------------------------- */
/*                              destroy_allocation.c 					        */
/* -------------------------------------------------------------------------- */
void							ft_destroylist(t_env_lst *list);

/* -------------------------------------------------------------------------- */
/*                               EXECUTOR FUNCTIONS                           */
/* -------------------------------------------------------------------------- */
void							execute_command(t_string *st_string);
void							execute_pipeline(t_string *st_string);
int								is_builtin(char *cmd);
void							execute_builtin(char **args,
									t_string *st_string);
int								has_pipe(t_env_lst *list);
char							**git_array(t_env_lst **list);

/* -------------------------------------------------------------------------- */
/*                              REDIRECTION HANDLING                          */
/* -------------------------------------------------------------------------- */
int								redirections(char **args);
int								handle_output_redirection(char **args, int *i);
char							*get_env_value(char *var_name,
									t_string *st_string);

/* -------------------------------------------------------------------------- */
/*                              VARIABLE EXPANSION                            */
/* -------------------------------------------------------------------------- */
void							expand_variables(t_env_lst *list);

char							*ft_strjoin_char(char *str, char c);

/* ************************************************************************** */
/*                               BUILTIN COMMANDS                              */
/* ************************************************************************** */
void							builtin_echo(char **args, t_string *st_string);
void							builtin_cd(char **args, t_string *st_string);
void							builtin_pwd(void);
void							builtin_exit(char **args, t_string *st_string);
void							builtin_unset(char **args, t_string *st_string);
void							builtin_export(char **args,
									t_string *st_string);
void							builtin_env(t_string *st_string);

void							handle_child_process(char **args, int prev_fd,
									int *pipe_fd, t_string *st_string);
char							*find_path(char *cmd, char **envp);

#endif
