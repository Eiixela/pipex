/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:05:48 by aljulien          #+#    #+#             */
/*   Updated: 2024/04/16 14:16:08 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_handler(int n_exit)
{
	if (n_exit == 1)
		ft_putstr_fd("./pipex infile cmd cmd outfile", 2);
	if (n_exit == 2)
		ft_putstr_fd("error opening file\n", 2);
	exit(EXIT_FAILURE);
}

int open_file(char *file, int in_or_out)
{
    int ret;

    if (in_or_out == 0)
        ret = open(file, O_RDONLY, 0777);
    else if (in_or_out == 1)
        ret = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    else
        return (-1);
    return ret;
}

void	ft_free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*get_env(char *name, char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	if (!env)
	{
		ft_putstr_fd("Path not found, please stop trying to break my pipex with 'unset PATH'", 2);
		return (NULL);
	}
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

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;
	char	**s_cmd;

	i = -1;
	allpath = ft_split(get_env("PATH", env), ':');
	s_cmd = ft_split(cmd, ' ');
	while (allpath[++i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, s_cmd[0]);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
		{
			ft_free_tab(s_cmd);
			return (exec);
		}
		free(exec);
	}
	ft_free_tab(allpath);
	ft_free_tab(s_cmd);
	return (cmd);
}
