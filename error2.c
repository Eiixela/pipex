/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:35:42 by aljulien          #+#    #+#             */
/*   Updated: 2024/04/29 17:18:09 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_all_tab(char **s_cmd, char **allpath)
{
	size_t	i;

	i = 0;
	while (s_cmd[i])
	{
		free(s_cmd[i]);
		i++;
	}
	free(s_cmd);
	i = 0;
	while (allpath[i])
	{
		free(allpath[i]);
		i++;
	}
	free(allpath);
}

void	exit_handler_and_free_double(char **s, int *pipe_fd, int n_exit)
{
	if (n_exit == 1)
	{
		ft_putstr_fd("allocation error, please try again\n", 2);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		ft_free_tab(s);
		exit(EXIT_FAILURE);
	}
	if (n_exit == 2)
	{
		ft_putstr_fd("pipex: command not found\n", 2);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		ft_free_tab(s);
		exit(EXIT_FAILURE);
	}
}

void	exit_handler_and_free_arrays(char *s, int *pipe_fd)
{
	if (!s)
	{
		ft_putstr_fd("allocation error, please try again\n", 2);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		free(s);
		exit(EXIT_FAILURE);
	}
}

char	**handle_space_in_grep(char **s_cmd, int *pipe_fd)
{
	int		j;
	char	*temp;

	j = -1;
	temp = NULL;
	while (s_cmd[++j])
	{
		temp = s_cmd[j];
		s_cmd[j] = get_spaces_in_quotes_back(s_cmd[j], -1);
		free(temp);
		if (!s_cmd[j])
			exit_handler_and_free_double(s_cmd, pipe_fd, 1);
		temp = s_cmd[j];
		s_cmd[j] = remove_quotes(s_cmd[j]);
		free(temp);
		if (!s_cmd[j])
			exit_handler_and_free_double(s_cmd, pipe_fd, 1);
	}
	return (s_cmd);
}

char	*check_command_in_path(char *cmd)
{
	if (access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	return (NULL);
}
