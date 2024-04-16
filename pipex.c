/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 14:15:26 by aljulien          #+#    #+#             */
/*   Updated: 2024/04/16 14:18:17 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec(char *cmd, char **env)
{
	char	**s_cmd;
	char	*path;
	int		path_in_cmd;
	int i = 0;
	
	s_cmd = ft_split(cmd, ' ');
	path_in_cmd = path_in_command(cmd);
	if (path_in_cmd == 0)
		path = get_path(s_cmd[0], env);
	else
	{
		
		path = cmd;
		return ;
	}
	
	i = execve(path, s_cmd, env);
	if (i == -1)
	{
		ft_putstr_fd("pipex: command not found ", 2);
		ft_putstr_fd(s_cmd[0], 2);
		ft_free_tab(s_cmd);
		exit(0);
	}
}

void child2(char **av, int *pipe_fd, char **env)
{
    int fd;
	
    fd = open_file(av[4], 1);
    dup2(fd, 1);
    dup2(pipe_fd[0], 0);
    close(pipe_fd[1]);
	exec(av[3], env);
}

void child1(char **av, int *p_fd, char **env)
{
    int fd;

    fd = open_file(av[1], 0);
    dup2(fd, 0);
    dup2(p_fd[1], 1);
    close(p_fd[0]);
	exec(av[2], env);
}
/*
int main(int ac, char **av, char **env)
{
    int pipe_fd[2];
	pid_t	pid[2];
    int status;
	int	i;

	i = 0;
    if (ac != 5)
        exit_handler(1);
    if (pipe(pipe_fd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
	while (i < 2)
	{
		pid[i] = fork();
		if (pid[i] == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid[i] == 0)
			child1(av, pipe_fd, env);
		i++;	
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
    waitpid(pid[0], &status, 0);
	waitpid(pid[1], &status, 0);
	return (0);
}*/

int	main(int ac, char **av, char **env)
{
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status;
	
	if (ac != 5)
		exit_handler(1);
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid1 = fork();
	
	if ((open_file(av[1], 0) != -1))
    {
		if (pid1 == -1) 
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		
		else if (pid1 == 0)
		{
			
			child1(av, pipe_fd, env);
		}
	}
	
	pid2 = fork();
	
	if ((open_file(av[4], 0) != -1))
	{
		
		if (pid2 == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid2 == 0)
		{
			child2(av, pipe_fd, env);
		}
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	return (EXIT_SUCCESS);
}
