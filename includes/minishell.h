#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libraries/libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

// Only one global variable
extern int	g_last_exit_status;

// Function prototypes
void		builtin_env(char **envp);
void		setup_signals(void);
void		execute_simple_command(char *cmd, char **envp);
// Renamed from execute_command
void		ft_free_split(char **split);
char		*ft_strjoin_free(char *s1, char *s2);
int			ft_strcmp(const char *s1, const char *s2);
void		builtin_echo(char **args);
// void		builtin_cd(char **args, char ***envp);
void		builtin_cd(char **args, char ***envp);
void		builtin_pwd(void);
void		builtin_exit(char **args);
void		builtin_unset(char **args, char ***envp);
void		builtin_export(char **args, char ***envp);
int			is_valid_key(char *s);
void		execute_single_command(char *command, char **envp);
int			handle_builtin(char *command, char **envp);
char		*find_path(char *cmd, char **envp);
int			is_builtin(char *command);
char		*ft_strcpy(char *dst, const char *src);

/* Environment variable functions */
char		*expand_env_variables(char *str, char **envp);
char		*get_env_var_name(const char *str, int *i);
char		*get_env_value(const char *name, char **envp);
char		*append_char(char *str, char c);
char		*process_env_var(char *result, const char *str, int *i,
				char **envp);

/* Export-related functions */
int			env_len(char **envp);
void		add_or_update(char *arg, char ***envp);
int			update_existing_env(char *key, int key_len, char *entry,
				char **envp);
void		add_new_env(char *entry, char ***envp);
void		sort_env(char **env);
char		**create_sorted_env_copy(char **envp);
void		print_env_entry(char *entry);
void		print_export(char **envp);

/* Redirection functions */
int			setup_input_redirect(char *file);
int			setup_output_redirect(char *file);
int			setup_append_redirect(char *file);
int			setup_heredoc(char *delimiter);
int			apply_redirections(char *type, char *file);
void		save_redirections(int *saved_fds);
void		reset_redirections(int *saved_fds);

/* Command Execution */
void		execute_simple_command(char *cmd, char **envp);
// Renamed from execute_command
void		execute_external(char *cmd, char **envp);
void		execute_single_command(char *cmd, char **envp);
// Add this if using Option A
int			handle_redirections(char *cmd, char **clean_cmd);
void		execute_command(char *line, char **envp);

int			is_numeric(char *str);
void		setup_child_pipes(int prev_fd, int *pipe_fd, int has_next_command);

#endif