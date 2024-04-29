/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 14:15:26 by aljulien          #+#    #+#             */
/*   Updated: 2024/04/29 17:13:08 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec(char *cmd, char **env, int *pipe_fd)
{
	char	**s_cmd;
	char	*path;
	int		i;

	i = 0;
	cmd = check_spaces_in_quotes(cmd, -1);
	if (!cmd)
		return (exit_handler_and_free_arrays(cmd, pipe_fd));
	s_cmd = ft_split(cmd, 32);
	if (!s_cmd)
		return (exit_handler_and_free_double(s_cmd, pipe_fd, 1));
	s_cmd = handle_space_in_grep(s_cmd, pipe_fd);
	path = get_path(s_cmd[0], env, -1);
	if (path != NULL)
		i = execve(path, s_cmd, env);
	if (i == -1 || path == NULL)
	{
		free(cmd);
		return (exit_handler_and_free_double(s_cmd, pipe_fd, 2));
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
