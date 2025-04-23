/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 09:10:58 by ybounite          #+#    #+#             */
/*   Updated: 2025/04/23 09:11:42 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ************************************************************************** */
/*                                   INCLUDES                                  */
/* ************************************************************************** */
# include "../libraries/libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <errno.h>

/* ************************************************************************** */
/*                                   DEFINES                                   */
/* ************************************************************************** */
# define YELLOW "\e[1;33m"
# define RED "\e[1;31m"
# define GREEN "\e[1;32m"
# define BLUE "\e[1;34m"
# define WHITE "\e[1;37m"
# define MINISPELL "\e[1;32m➜ \e[1;34m minishell\e[0m "

/* ************************************************************************** */
/*                                 DATA TYPES                                  */
/* ************************************************************************** */

/* Token types for lexical analysis */
typedef enum
{
	CMD,                // command
	OR,                 // ||
	AND,                // &&
	PARENTHESIS,        // ()
	REDIRECTION,        // generic redirection
	INPUT_REDIRECTION,  // <
	OUTPUT_REDIRECTION, // >
	APPEND_REDIRECTION, // >>
	HERE_DOCUMENT,      // <<
	BUILTINS,           // builtin commands
	DOUBLE_QUOTE = 34,  // "
	DOLLAR = 36, // $
	SINGLE_QUOTE = 39,  // '
	ASTERISK = 42,      // *
	PIPE = 124,         // |
}								en_status_type;

/* Linked list structure for token stream */
typedef struct s_environement_list
{
	en_status_type				type;
	bool						cat;
	char						*value;
	struct s_environement_list	*next;
}								t_env_lst;

/* Main shell data structure */
typedef struct s_string
{
	char	*line;          // Input command line
	char	*strcon;        // Processed command line
	char	**command;      // Command arguments
	bool	is_error;       // Error flag
	bool	is_pipe;        // Contains pipe operator
	bool	is_redirection; // Contains redirection
	bool	is_builtin;     // Is a builtin command
	bool	is_parenthesis; // Contains parentheses
	bool	is_heredoc;     // Contains heredoc
	int		exit_status;     // Command exit status
	char	**g_envp;       // Environment variables
	t_env_lst *head;     // Token list head
}								t_string;

/* Command execution structure */
typedef struct s_exec_cmd
{
	char	*full_path;  // Full command path
	char	*path;       // Command path
	char	**dirs;      // Directory paths
	pid_t	pid;        // Process ID
	char	*cmd_path;   // Command path
	char	**cmd_flags; // Command flags
}								t_exec_cmd;

/* ************************************************************************** */
/*                              GLOBAL FUNCTIONS                               */
/* ************************************************************************** */
struct s_string					*data_struc(void);

/* ************************************************************************** */
/*                              MEMORY MANAGEMENT                              */
/* ************************************************************************** */
void							free_list(t_env_lst *head);
void							ft_free_split(char **split);

/* ************************************************************************** */
/*                                SIGNAL HANDLING                              */
/* ************************************************************************** */
void							assign_signals_handler(void);
void							setup_signals(void);
void							handler(int signum);

/* ************************************************************************** */
/*                                STRING UTILITIES                             */
/* ************************************************************************** */
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

/* ************************************************************************** */
/*                               PARSER FUNCTIONS                              */
/* ************************************************************************** */
/* Lexical Analysis */
char							*get_line(void);
char							*handler_string(char *line);
void							ft_spliter(t_env_lst **list, char *line);
en_status_type					find_type_state(char c);
en_status_type					find_states(char *str);

/* Token Management */
t_env_lst						*ft_newnode(char *cmd, en_status_type state);
void							lstadd_back(t_env_lst **head, t_env_lst *new);
void							ft_add_newtoken(t_env_lst **head, char *token,
									en_status_type state);
void							print_lst_tokens(t_env_lst *head);

/* Command Processing */
int								handle_input_syntax(t_string *st_string);
void							start_shell_session(t_string input);

/* ************************************************************************** */
/*                               EXECUTOR FUNCTIONS                            */
/* ************************************************************************** */
void							execute_command(t_string *st_string);
void							execute_pipeline(t_string *st_string);
int								is_builtin(char *cmd);
void							execute_builtin(char **args,
									t_string *st_string);
int								has_pipe(t_env_lst *list);
char							**git_array(t_env_lst **list);


void							heandler_dollar(t_env_lst **list, char *str, int *i,
									en_status_type state);
/* ************************************************************************** */
/*                              REDIRECTION HANDLING                           */
/* ************************************************************************** */
int								redirections(char **args);
int								handle_output_redirection(char **args, int *i);
char							*get_env_value(char *var_name,
									t_string *st_string);

/* ************************************************************************** */
/*                               BUILTIN COMMANDS                              */
/* ************************************************************************** */
void							builtin_echo(char **args, t_string *st_string);
void							builtin_cd(char **args, t_string *st_string);
void							builtin_pwd(void);
void							builtin_exit(char **args);
void							builtin_unset(char **args, t_string *st_string);
void							builtin_export(char **args,
									t_string *st_string);
void							builtin_env(t_string *st_string);

#endif
