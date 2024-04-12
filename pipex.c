/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 14:15:26 by aljulien          #+#    #+#             */
/*   Updated: 2024/03/26 15:10:29 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec(char *cmd, char **env)
{
	char	**s_cmd;
	char	*path;

	s_cmd = ft_split(cmd, ' ');
	path = get_path(s_cmd[0], env);
	if (execve(path, s_cmd, env) == -1)
	{
		ft_putstr_fd("pipex: command not found", 2);
		ft_putstr_fd(s_cmd[0], 2);
		ft_free_tab(s_cmd);
		exit(0);
	}
}

void	child(char *cmd, char *file, int *p_fd, char **env)
{
	int	fd;
	int	num_cmd = 1;
	int	num_file = 1;

	fd = open_file(file, 0);
	dup2(fd, 0);
	dup2(p_fd[1], 1);
	close(p_fd[0]);
	exec(cmd, env);
}

int	main(int ac, char **av, char **env)
{
	int		*p_fd[2];
	pid_t	pid[2];
	int		i = 0;
	int		num_cmd = 1; // 1 ti make a while loop to make the children execute at the same time, we have a cmd every 1 input
	int		num_file = -2; // -2 to make a while loop, because input is "infile cmd1 cmd 2 outfile" so we have a ifle every 3 output 

	if (ac != 5)
		exit_handler(1);
	if (pipe(p_fd[i]) == -1)
		exit(-1);
	while (i < 2) // 2 because it's the number of the child process
	{
		pid[i] = fork();
		if (pid[i] == -1)
			exit(-1);
		i++;
	}
	while (i >= 0)
	{
		if (!pid[i])
			child(av[num_cmd + 1], av[num_file + 3], p_fd[i], env);
		i--;
	}
	while (wait(0) != -1 && errno != ECHILD)
}
