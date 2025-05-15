/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 09:10:58 by ybounite          #+#    #+#             */
/*   Updated: 2025/05/15 12:48:14 by ybounite         ###   ########.fr       */
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

typedef struct s_expand_data
{
	bool						quotes[2];
	bool						*is_spliting;
	int							*i;
	char						*result;
}								t_expand_data;

extern int						g_exit_status;
/* -------------------------------------------------------------------------- */
/*                             syntax_error.c                                 */
/* -------------------------------------------------------------------------- */
void							ft_puterror(char error);
bool							is_first_operation_pipe(char *str);
bool							is_last_operation_pipe(char *str);
int								ft_lenword(char *str);

/* -------------------------------------------------------------------------- */
/*                            handler_syntax_error.c                          */
/* -------------------------------------------------------------------------- */
bool							handler_syntax_error(char *line);
int								lenqoutes(char *str, int *i);
bool							check_syntax_errors(t_env_lst *tokens);
void							ft_error(en_status type);
bool							is_redirection(int type);
char							*get_token_symbol(int type);
bool							redirection_target_error(t_env_lst *curr);


/* -------------------------------------------------------------------------- */
/*                            ft_skip_whit_string.c                           */
/* -------------------------------------------------------------------------- */
void							skip_whiteword(char *str, int *i);
char							ft_skip_whitword(char *str, int *index);
char							ft_skip_whitquotes(char *str, int *index);
char							ft_skip_whitoperator(char *str, int *index);
int								skip_strqoutes(char *str, int *inedx, char quotes);

/* -------------------------------------------------------------------------- */
/*                              expand_variables.c                            */
/* -------------------------------------------------------------------------- */
char							*expand_string(const char *str, bool *is_spliting);


/* -------------------------------------------------------------------------- */
/*                              get_variable.c                                */
/* -------------------------------------------------------------------------- */
char							*get_variable_name(const char *str, int *i);
char							*get_variable_value(char *var_name);

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
void							set_signals_for_execution(void);
void							set_signals_for_heredoc(void);
void							reset_signals(void);
void							handler_heredoc_sig(int signum);

/* -------------------------------------------------------------------------- */
/*                                STRING UTILITIES                            */
/* -------------------------------------------------------------------------- */

char							*ft_strjoin_free(char *s1, char *s2);
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
/*                               allocate_data.c                              */
/* -------------------------------------------------------------------------- */
void							*ft_malloc(size_t size, short option);
void							memory_released(t_list **head);

/* -------------------------------------------------------------------------- */
/*                              get_line.c                                    */
/* -------------------------------------------------------------------------- */
char							*get_line(void);
/* -------------------------------------------------------------------------- */
/*                              spliter.c                                     */
/* -------------------------------------------------------------------------- */
char							**spliter(char *line);
int								ft_lenoperator(char *str, int *index);
void							skip_whiteword(char *str, int *i);
/* -------------------------------------------------------------------------- */
/*                              spliter_utils.c                                      */
/* -------------------------------------------------------------------------- */
void							ft_count_whitchar(char *line, int *index,
								int *count, char c);
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
/* -------------------------------------------------------------------------- */
/*                              start_shell.c                                */
/* -------------------------------------------------------------------------- */
int								handle_input_syntax(t_string *st_string);
void							start_shell_session(t_string input);
bool							has_invalid_redirection_sequence(t_env_lst *list);

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



/* -------------------------------------------------------------------------- */
/*                              heredoc.c 									  */
/* -------------------------------------------------------------------------- */
int								handler_heredoc(t_env_lst *list);
int								handle_forked_process(char *delimiter, bool dolar);
int								read_and_process_heredoc_input(char *delimiter, bool expand);
char							*ft_expand(char *line);
bool							is_heredoc(t_env_lst *list);

//
char							*ft_remove_quotes(char *str);
bool							is_quotes_thes_str(char *str);

/* -------------------------------------------------------------------------- */
/*                              heredoc_utlis.c								  */
/* -------------------------------------------------------------------------- */
int								open_heredoc(void);
bool							ft_isheredoc(t_env_lst *list);
char							*find_delimiter(t_env_lst *list,
									int *is_expand);
bool							ft_clculate_heredoc(t_env_lst *list);

/* -------------------------------------------------------------------------- */
/*                              expand_heredoc.c       	                      */
/* -------------------------------------------------------------------------- */
char							*expand_heredoc(char *str);
/* -------------------------------------------------------------------------- */
/*                               error_herdoc.c    	                          */
/* -------------------------------------------------------------------------- */
void							error_herdoc(char *delimiter);
bool							ft_clculate_heredoc(t_env_lst	*list);

/* -------------------------------------------------------------------------- */
/*                              creatr_file_name.c  	                      */
/* -------------------------------------------------------------------------- */
char							*creatr_file_name(int fd);
char							*create_temp_file();
int								open_heredoc();

/* -------------------------------------------------------------------------- */
/*                              destroy_allocation.c 						  */
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
// char							*get_env_value(char *var_name,
// 									t_string *st_string);

/* -------------------------------------------------------------------------- */
/*                              VARIABLE EXPANSION                            */
/* -------------------------------------------------------------------------- */
int								expand_variables(t_env_lst **list);
char							*ft_strjoin_char(char *str, char c);

/* ************************************************************************** */
/*                               BUILTIN COMMANDS                              */
/* ************************************************************************** */
/* -------------------------------------------------------------------------- */
/*                              cbuiltin_exec.c                               */
/* -------------------------------------------------------------------------- */
void							builtin_echo(char **args, t_string *st_string);
char							*get_env_value(char *var_name, t_string *st_string);
int								is_n_flag(char *s);

/* -------------------------------------------------------------------------- */
/*                             pipeline.c                                     */
/* -------------------------------------------------------------------------- */
void							setup_child_pipe(int **child_pipe, int *pipe_fd, int i, int cmd_count);
void							execute_pipeline(t_string *st_string);



/* -------------------------------------------------------------------------- */
/*                              pipeline_commands.c                           */
/* -------------------------------------------------------------------------- */
void						process_command(t_process_args *args);
t_pipeline_data				*init_pipeline_data(t_string *st_string);
int							handle_directory_error(char **args);
int	handle_directory_error(char **args);
/* -------------------------------------------------------------------------- */
/*                             pipeline_utils2.c                              */
/* -------------------------------------------------------------------------- */
void						wait_for_children(pid_t *pids, int cmd_count);
void						handler_sigint(int signum);
void						manage_child_process(t_string *st_string, int prev_fd,
								int *child_pipe, char **args);
void						handle_pipe_fds(int *pipe_fd, int *prev_fd, int i,
								int cmd_count);
/* -------------------------------------------------------------------------- */
/*                             pipeline_utils.c                              */
/* -------------------------------------------------------------------------- */
void						setup_command_pipe(int *pipe_fd, t_env_lst **list,
								int i, int cmd_count);
void						update_exit_status(int status);
int							setup_pipe(int pipe_fd[2], t_env_lst *list);
void						handle_parent_process(int *prev_fd, int *pipe_fd,
								pid_t pid, int *status);
//  child_process.c 
int	handle_permission_error(char **args);
int	handle_no_file_error(char **args);
void	setup_redirections(int prev_fd, int *pipe_fd);

int	handle_cmd_not_found(char **args);

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

/* ************************************************************************** */
/*                              PIPELINE_UTILS                              */
/* ************************************************************************** */

int								setup_pipe(int pipe_fd[2], t_env_lst *list);
int								create_process(pid_t *pid);
void							handle_parent_process(int *prev_fd,
									int *pipe_fd, pid_t pid, int *status);
void							update_exit_status(int status);
char							*collapse_spaces(const char *str);
/* -------------------------------------------------------------------------- */
/*                              command_handling.c                          */
/* -------------------------------------------------------------------------- */
int								handle_direct_path(char **args);
void							handle_command_path(char **args,
									t_string *st_string);


/* -------------------------------------------------------------------------- */
/*                              cd.c        				                  */
/* -------------------------------------------------------------------------- */
bool	size_cd(char **args);
void	builtin_cd(char **args, t_string *st_string);
/* -------------------------------------------------------------------------- */
/*                              cd_utils.c        				              */
/* -------------------------------------------------------------------------- */
void	update_oldpwd(char *old_pwd, t_string *st_string);
void	update_pwd(t_string *st_string);
void	update_pwd_env(t_string *st_string);
char	*handle_home(void);
char	*get_oldpwd(t_string *st_string);
/* -------------------------------------------------------------------------- */
/*                              cd_utils.c        				              */
/* -------------------------------------------------------------------------- */
int	env_len(t_string *st_string);
int	update_existing_entry(char *key, int key_len, char *entry,
	t_string *st_string);
void	add_new_entry(char *entry, t_string *st_string);
void	builtin_export(char **args, t_string *st_string);
/* -------------------------------------------------------------------------- */
/*                              export_utils.c       				          */
/* -------------------------------------------------------------------------- */
char	**create_env_copy(t_string *st_string);
void	print_env_entry(char *entry);
void	print_export(t_string *st_string);
char	*extract_key(char *arg, int *key_len);
char	*create_entry(char *arg, int key_len);

/* -------------------------------------------------------------------------- */
/*                              export_utils2.c       				          */
/* -------------------------------------------------------------------------- */
void	add_or_update(char *arg, t_string *st_string);
/* -------------------------------------------------------------------------- */
/*                             sort_env.c            				          */
/* -------------------------------------------------------------------------- */
void	sort_env(char **env);
/* -------------------------------------------------------------------------- */
/*                             ft_add_expand_variable.c           	          */
/* -------------------------------------------------------------------------- */
bool	is_equal(char *str);
void	ft_add_expand_variable(t_env_lst **node_ptr, char *variable);
/* -------------------------------------------------------------------------- */
/*                             expand_string.c            	                  */
/* -------------------------------------------------------------------------- */
char	*expand_string(const char *str, bool *is_spliting);
/* -------------------------------------------------------------------------- */
/*                             expand_string_utils.c           	              */
/* -------------------------------------------------------------------------- */
char	*handle_single_quote(char *result, const char *str, int *i, bool *in_sq);
char	*handle_double_quote(char *result, const char *str, int *i, bool *in_dq);




#endif