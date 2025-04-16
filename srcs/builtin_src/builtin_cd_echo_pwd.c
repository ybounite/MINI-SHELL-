#include "../../includes/minishell.h"

static int	is_n_flag(char *s)
{
	int	i;

	if (!s || s[0] != '-' || s[1] != 'n')
		return (0);
	i = 1;
	while (s[i] == 'n')
		i++;
	return (s[i] == '\0');
}

void	builtin_echo(char **args)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	while (args[i] && is_n_flag(args[i]))
	{
		n_flag = 1;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (!n_flag)
		printf("\n");
}

void	builtin_cd(char **args, char ***envp)
{
	char	pwd[1024];
	char	*home;
	char	*target_dir;
	char	*old_pwd;
	char	*old_pwd_env;
	char	new_pwd[1024];
	char	*pwd_env;

	// Get current directory for OLDPWD
	if (getcwd(pwd, sizeof(pwd)) == NULL)
	{
		perror("cd: getcwd error");
		g_last_exit_status = 1;
		return ;
	}
	// Determine target directory
	if (!args[1] || ft_strcmp(args[1], "~") == 0)
	{
		// cd to HOME directory
		home = get_env_value("HOME", *envp);
		if (!home || !*home)
		{
			ft_putendl_fd("cd: HOME not set", 2);
			g_last_exit_status = 1;
			return ;
		}
		target_dir = home;
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		// cd to previous directory (OLDPWD)
		old_pwd = get_env_value("OLDPWD", *envp);
		if (!old_pwd || !*old_pwd)
		{
			ft_putendl_fd("cd: OLDPWD not set", 2);
			g_last_exit_status = 1;
			return ;
		}
		target_dir = old_pwd;
		ft_putendl_fd(target_dir, 1); // Print the directory when using cd -
	}
	else
		target_dir = args[1]; // cd to specified path
	// Change directory
	if (chdir(target_dir) != 0)
	{
		perror("cd");
		g_last_exit_status = 1;
		return ;
	}
	// Update environment variables
	old_pwd_env = ft_strjoin("OLDPWD=", pwd);
	if (old_pwd_env)
	{
		add_or_update(old_pwd_env, envp);
		free(old_pwd_env);
	}
	if (getcwd(new_pwd, sizeof(new_pwd)) != NULL)
	{
		pwd_env = ft_strjoin("PWD=", new_pwd);
		if (pwd_env)
		{
			add_or_update(pwd_env, envp);
			free(pwd_env);
		}
	}
	g_last_exit_status = 0;
}

void	builtin_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("pwd");
}
