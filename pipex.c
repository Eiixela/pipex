/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 14:15:26 by aljulien          #+#    #+#             */
/*   Updated: 2024/04/26 18:08:50 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec(char *cmd, char **env, int *pipe_fd)
{
	char	**s_cmd;
	char	*path;
	int		i;
	int		j;

	i = 0;
	j = -1;
	cmd = check_spaces_in_quotes(cmd);
	s_cmd = ft_split(cmd, 32);
	while (s_cmd[++j])
	{
		s_cmd[j] = get_spaces_in_quotes_back(s_cmd[j]);
		s_cmd[j] = remove_quotes(s_cmd[j]);
	}
	path = get_path(s_cmd[0], env);
	if (path != NULL)
		i = execve(path, s_cmd, env);
	if (i == -1 || path == NULL)
	{
		ft_putstr_fd("pipex: command not found ", 2);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		ft_free_tab(s_cmd);
		exit(0);
	}
}

void	child2(char **av, int *pipe_fd, char **env)
{
	int	fd;

	fd = open_file(av[4], 1);
	if (fd == -1)
	{
		ft_putstr_fd("Out_file : Permission denied", 2);
		exit(EXIT_FAILURE);
	}
	dup2(fd, 1);
	close (fd);
	dup2(pipe_fd[0], 0);
	close(pipe_fd[1]);
	exec(av[3], env, pipe_fd);
}

void	child1(char **av, int *p_fd, char **env)
{
	int	fd;

	fd = open_file(av[1], 0);
	if (fd == -1)
	{
		ft_putstr_fd("Input_file : Permission denied", 2);
		close (p_fd[0]);
		close(p_fd[1]);
		exit(EXIT_FAILURE);
	}
	if (!env && (path_in_command(av[3]) != 0))
		exit(EXIT_FAILURE);
	dup2(fd, 0);
	close(fd);
	dup2(p_fd[1], 1);
	close(p_fd[0]);
	exec(av[2], env, p_fd);
}

int	main(int ac, char **av, char **env)
{
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status;

	input_error(ac);
	if (pipe(pipe_fd) == -1)
		exit(EXIT_FAILURE);
	pid1 = fork();
	pid_error(pid1);
	if (pid1 == 0)
		child1(av, pipe_fd, env);
	pid2 = fork();
	pid_error(pid2);
	if (pid2 == 0)
		child2(av, pipe_fd, env);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	return (EXIT_SUCCESS);
}
