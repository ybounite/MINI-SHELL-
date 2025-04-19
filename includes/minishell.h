#ifndef MINISHELL_H
# define MINISHELL_H

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

# define YELLOW "\e[1;33m"
# define RED "\e[1;31m"
# define GREEN "\e[1;32m"
# define BLUE "\e[1;34m"
# define WHITE "\e[1;37m"
# define MINISPELL "\e[1;32m➜ \e[1;34m minishell\e[0m "
// "\001\e[1;38;5;141m\002[minispell]\001\e[1;33m\002 > \001\033[0m\002"

typedef enum
{
	CMD,               // command
	OR,                // ||
	AND,               // &&
	PARENTHESIS,       //()
	REDIRECTION,       // >> << < >
	BUILTINS,          // echo -n cd pwd export unset env exit
	DOUBLE_QUOTE = 34, // "
	SINGLE_QUOTE = 39, // '
	ASTERISK = 42,     // *
	PIPE = 124,        // |
						// REDIN = 5, // <
						// REDOUT = 6, // >
}								en_status_type;

typedef struct s_environement_list
{
	en_status_type				type;
	bool						cat;
	char						*value;
	struct s_environement_list	*next;
}								t_env_lst;

typedef struct s_string
{
	char						*line;
	char						*strcon;
	char						**command;
	bool						is_error;
	bool						is_pipe;
	bool						is_redirection;
	bool						is_builtin;
	bool						is_parenthesis;
	bool						is_heredoc;
	int							exit_status;
	char						**g_envp;
	t_env_lst					*head;
}								t_string;

typedef struct s_exec_cmd
{
	char						*full_path;
	char						*path;
	char						**dirs;
	pid_t						pid;
	char						*cmd_path;
	char						**cmd_flags;
}								t_exec_cmd;

struct s_string					*data_struc(void);
// mian.c
// ft_free.c
void							free_list(t_env_lst *head);
//
void							assign_signals_handler(void);
void							handler(int signum);
/* -------------------------------------------------------------------------- */
/*                       FILE 	=	ft_lestnew.c                           		*/
/* -------------------------------------------------------------------------- */
// void			lstadd_back(t_env_lst **head, t_env_lst *new);
// t_env_lst		*creatnew_node(char *cmd, en_status_type state, bool cat);
// en_status_type	find_type_state(char c);

/* -------------------------------------------------------------------------- */
/*                       FILE 	=	ft_spilter.c                              */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/*                       FILE 	=	satart_shell.c                            */
/* -------------------------------------------------------------------------- */
void							start_shell_session(t_string input);
int								handle_input_syntax(t_string *st_string);
char							*handler_string(char *line);
/* -------------------------------------------------------------------------- */
/*                       FILE 	=	gitline.c                                 */
/* -------------------------------------------------------------------------- */
char							*get_line(void);
/* -------------------------------------------------------------------------- */
/*                       FILE 	=	ft_utlis.c                                */
/* -------------------------------------------------------------------------- */
bool							is_operator(char c);
bool							find_space(char c);
bool							isquotes(char c);
void							ft_skip_whitespace(char *str, int *index);

/* -------------------------------------------------------------------------- */
/*                       FILE 	=	ft_lenstr.c                               */
/* -------------------------------------------------------------------------- */
int								skip_strqoutes(char *str, int *inedx,
									char quotes);
int								ft_lenword(char *str);

/* -------------------------------------------------------------------------- */
/*                       FILE 	=		ft_spliter.c                             */
/* -------------------------------------------------------------------------- */
void							ft_spliter(t_env_lst **list, char *line);
/* -------------------------------------------------------------------------- */
/*                       FILE 	=	ft_node.c      					              */
/* -------------------------------------------------------------------------- */
t_env_lst						*ft_newnode(char *cmd, en_status_type state);
void							lstadd_back(t_env_lst **head, t_env_lst *new);
void							ft_add_newtoken(t_env_lst **head, char *token,
									en_status_type state);
void							print_lst_tokens(t_env_lst *head);
void							builtin_env(t_string *st_string);
void							setup_signals(void);
void							execute_command(t_string *st_string);
void							ft_free_split(char **split);
char							*ft_strjoin_free(char *s1, char *s2);
int								ft_strcmp(const char *s1, const char *s2);
void							builtin_echo(char **args);
void							builtin_cd(char **args, t_string *st_string);
void							builtin_pwd(void);
void							builtin_exit(char **args);
void							builtin_unset(char **args, t_string *st_string);
void							builtin_export(char **args,
									t_string *st_string);
int								is_valid_key(char *s);
void							execute_pipeline(t_string *st_string);

int								is_builtin(char *cmd);
void							execute_builtin(char **args,
									t_string *st_string);
int								has_pipe(t_env_lst *list);
//
char							**git_array(t_env_lst **list);

#endif
