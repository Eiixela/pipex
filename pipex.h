/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:05:35 by aljulien          #+#    #+#             */
/*   Updated: 2024/03/26 15:12:23 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h> 
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>

//pipex.c
void		exec(char *cmd, char **env);
void		child(char **av, int *p_fd, char **env);
void		parent(char **av, int *p_fd, char **env);
int			main(int ac, char **av, char **env);

//utils.c
void		exit_handler(int n_exit);
int			open_file(char *file, int in_or_out);
void		ft_free_tab(char **tab);
char		*get_env(char *name, char **env);
char		*get_path(char *cmd, char **env);

//split.c
char		**ft_split(char const *s, char c);
size_t		ft_strlen(const char *s);

//libft_utils.c
int			ft_strcmp(char *s1, char *s2);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_substr(char const *s, unsigned int start, size_t len);
void		ft_putstr_fd(char *s, int fd);
char		*ft_strdup(const char *s);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);

#endif