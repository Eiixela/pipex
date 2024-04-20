/* ************************************************************************** */
/*  */
/*  :::	 ::::::::   */
/*   utils.c	:+:   :+:	:+:   */
/*  +:+ +:+	+:+	*/
/*   By: aljulien <aljulien@student.42.fr>	+#+  +:+	   +#+  */
/*  +#+#+#+#+#+   +#+	*/
/*   Created: 2024/03/26 15:05:48 by aljulien	 #+#  #+#	*/
/*   Updated: 2024/04/20 16:25:11 by aljulien	###   ########.fr	*/
/*  */
/* ************************************************************************** */

#include "pipex.h"

char	*get_env(char *name, char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j);
		if (ft_strcmp(sub, name) == 0)
		{
			free(sub);
			return (env[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}

int	path_in_command(char *cmd)
{
	if (access(cmd, F_OK) == 0)
	{
		return (1);
	}
	else
		return (0);
}

void	free_all(char **s_cmd, char **allpath)
{
	ft_free_tab(s_cmd);
	ft_free_tab(allpath);
}

char	*get_path(char *cmd, char **env)
{
	char	*exec;
	char	**s_cmd;
	char	*path_part;
	char	**allpath;
	int		i;

	i = 0;
	if (cmd[0] == '/')
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	allpath = ft_split(get_env("PATH", env), ':');
	s_cmd = ft_split(cmd, ' ');
	while (allpath[i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, s_cmd[0]);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
		{
			ft_free_tab(s_cmd);
			ft_free_tab(allpath);
			return (exec);
		}
		free(exec);
		i++;
	}
	ft_free_tab(s_cmd);
	ft_free_tab(allpath);
	return (NULL);
}
