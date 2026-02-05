#include "minishell.h"

static char *path_down(char *arg, t_map *env)
{
	char *end;

	end = ft_strrchr(arg, '/');
	if (!end)
		return (free(arg), NULL);
	*end = '\0';
	if (!*arg)
		return (free(arg), ft_strdup(env->get(env, "PWD")));
	return (arg);
}
char *process_cd_path (char *arg, t_map *env)
{
	char *temp;

	if (!arg)
		return (NULL);
	if (arg[0] == '/')
		temp =  ft_strdup(arg);
	else
	{
		if (!ft_strcmp(arg, "."))
			temp = ft_strdup(env->get(env, "PWD"));
		else if (!ft_strcmp(arg, ".."))
			temp =  path_down(ft_strdup(env->get(env, "PWD")), env);
		else
			temp = ft_strdup(arg);
	}
	return (temp);
}