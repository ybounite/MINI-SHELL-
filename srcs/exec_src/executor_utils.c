#include "../../includes/minishell.h"

/* Setup child process pipe redirections */
void	setup_child_pipes(int prev_fd, int *pipe_fd, int has_next_command)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (has_next_command)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
}

/* Handle redirections and return a clean command */
int	handle_redirections(char *cmd, char **clean_cmd)
{
	int		i;
	int		in_quotes;
	char	*token_start;
	char	redirect_type[3];
	char	tmp;

	i = 0;
	in_quotes = 0;
	token_start = cmd;
	*clean_cmd = ft_strdup("");
	if (!*clean_cmd)
		return (0);
	while (cmd[i])
	{
		// Toggle quote state
		if ((cmd[i] == '"' || cmd[i] == '\'') && (i == 0 || cmd[i - 1] != '\\'))
			in_quotes = (in_quotes == cmd[i]) ? 0 : cmd[i];
		// Process redirections outside quotes
		if (!in_quotes && (cmd[i] == '>' || cmd[i] == '<'))
		{
			// Save text before redirection
			if (token_start != &cmd[i])
			{
				tmp = cmd[i];
				cmd[i] = '\0';
				if (*clean_cmd[0] && token_start[0])
					*clean_cmd = ft_strjoin_free(*clean_cmd, " ");
				if (token_start[0])
					*clean_cmd = ft_strjoin_free(*clean_cmd, token_start);
				cmd[i] = tmp;
			}
			// Get redirection type (> or < or >> or <<)
			ft_bzero(redirect_type, 3);
			redirect_type[0] = cmd[i];
			if (cmd[i + 1] && cmd[i] == cmd[i + 1])
			{
				redirect_type[1] = cmd[i + 1];
				i++;
			}
			// Move to filename, skipping spaces
			i++;
			while (cmd[i] && cmd[i] == ' ')
				i++;
			// Check for syntax error
			if (!cmd[i])
			{
				printf("syntax error near unexpected token `newline'\n");
				free(*clean_cmd);
				*clean_cmd = NULL;
				return (0);
			}
			// Extract and process filename
			token_start = &cmd[i];
			while (cmd[i] && cmd[i] != ' ' && cmd[i] != '<' && cmd[i] != '>')
				i++;
			tmp = cmd[i];
			cmd[i] = '\0';
			if (!apply_redirections(redirect_type, token_start))
			{
				free(*clean_cmd);
				*clean_cmd = NULL;
				return (0);
			}
			cmd[i] = tmp;
			token_start = &cmd[i];
			continue ;
		}
		i++;
	}
	// Add remaining text to clean command
	if (*token_start && token_start < &cmd[i])
	{
		if (*clean_cmd[0])
			*clean_cmd = ft_strjoin_free(*clean_cmd, " ");
		*clean_cmd = ft_strjoin_free(*clean_cmd, token_start);
	}
	return (1);
}
