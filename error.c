/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:45:40 by aljulien          #+#    #+#             */
/*   Updated: 2024/04/20 16:26:23 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	input_error(int ac)
{
	if (ac != 5)
		exit_handler(1);
}

void	pid_error(pid_t pid)
{
	if (pid == -1)
		exit(EXIT_FAILURE);
}

void	exit_handler(int n_exit)
{
	if (n_exit == 1)
	{
		ft_putstr_fd("./pipex infile cmd cmd outfile", 2);
		exit(EXIT_FAILURE);
	}
	if (n_exit == 2)
		write(2, "c", 2);
}

int	open_file(char *file, int in_or_out)
{
	int	ret;

	ret = 0;
	if (in_or_out == 0)
		ret = open(file, O_RDONLY, 0777);
	else if (in_or_out == 1)
		ret = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	return (ret);
}
