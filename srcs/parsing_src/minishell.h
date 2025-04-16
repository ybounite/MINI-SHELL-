/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamezoua <bamezoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 13:49:16 by ybounite          #+#    #+#             */
/*   Updated: 2025/04/16 14:35:21 by bamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>

# define YELLOW	"\e[1;33m"
# define RED     "\e[1;31m"
# define GREEN   "\e[1;32m"
# define BLUE    "\e[1;34m"
# define WHITE   "\e[1;37m"
# define MINISPELL "\e[1;32m➜ \e[1;34m minishell\e[0m "
// "\001\e[1;38;5;141m\002[minispell]\001\e[1;33m\002 > \001\033[0m\002"

extern char **environ;

typedef enum {
	CMD, //command 
	OR, // ||
	AND, // && 
	PARENTHESIS, //()
	REDIRECTION,// >> << < >
	BUILTINS, // echo -n cd pwd export unset env exit
	DOUBLE_QUOTE = 34,// "
	SINGLE_QUOTE = 39,// '
	ASTERISK = 42, // *
	PIPE = 124, // |
	// REDIN = 5, // <
	// REDOUT = 6, // >
}	en_status_type;

typedef struct	s_environement_list
{
	en_status_type					type;
	bool							cat;
	char							*value;
	struct	s_environement_list		*next;
}	t_env_lst;

typedef struct s_string
{
	char	*line;
	char	*strcon;
	char	**command;
	bool	is_error;
	int		exit_status;
}	t_string;

typedef struct s_exec_cmd
{
	char	*full_path;
	char	*path;
	char	**dirs;
	pid_t	pid;
	char	*cmd_path;
	char	**cmd_flags;
}	t_exec_cmd;

struct s_string		*data_struc(void);
//mian.c
// ft_free.c
void	free_list(t_env_lst *head);
// 
void	assign_signals_handler();
void	handler(int signum);
/* -------------------------------------------------------------------------- */
/*                       FILE 	=	ft_lestnew.c                           	  */
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
void	start_shell_session(t_string input);
int		handle_input_syntax(t_string *st_string);
char	*handler_string(char *line);
/* -------------------------------------------------------------------------- */
/*                       FILE 	=	gitline.c                                 */
/* -------------------------------------------------------------------------- */
char	*get_line();
/* -------------------------------------------------------------------------- */
/*                       FILE 	=	ft_utlis.c                                */
/* -------------------------------------------------------------------------- */
bool	is_operator(char c);
bool	find_space(char c);
bool	isquotes(char c);
void	ft_skip_whitespace(char *str, int *index);

/* -------------------------------------------------------------------------- */
/*                       FILE 	=	ft_lenstr.c                               */
/* -------------------------------------------------------------------------- */
int		skip_strqoutes(char *str, int *inedx, char quotes);
int		ft_lenword(char *str);

/* -------------------------------------------------------------------------- */
/*                       FILE 	=	 ft_spliter.c                             */
/* -------------------------------------------------------------------------- */
void	ft_spliter(t_env_lst **list, char *line);
/* -------------------------------------------------------------------------- */
/*                       FILE 	=	ft_node.c      	                          */
/* -------------------------------------------------------------------------- */
t_env_lst	*ft_newnode(char *cmd, en_status_type state);
void		lstadd_back(t_env_lst **head, t_env_lst *new);
void		ft_add_newtoken(t_env_lst **head, char *token, en_status_type state);
void		print_lst_tokens(t_env_lst *head);
# endif