#include "../../includes/minishell.h"

void	builtin_pwd(void)
{
    char	cwd[PATH_MAX];

    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("%s\n", cwd);
    else
        perror("pwd");
}