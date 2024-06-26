/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:05:35 by aljulien          #+#    #+#             */
/*   Updated: 2024/04/29 17:17:52 by aljulien         ###   ########.fr       */
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
void		exec(char *cmd, char **env, int *pipe_fd);
void		child1(char **av, int *p_fd, char **env);
int			main(int ac, char **av, char **env);
void		child2(char **av, int *pipe_fd, char **env);

//utils.c
void		exit_handler(int n_exit);
int			open_file(char *file, int in_or_out);
void		ft_free_tab(char **tab);
char		*get_env(char *name, char **env);
char		*get_path(char *cmd, char **env, int i);
int			path_in_command(char *cmd);

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
size_t		ft_strlen(const char *s);
void		pid_error(pid_t pid);
void		input_error(int ac);
void		open_infile_error(void);
char		*get_spaces_in_quotes_back(char *s, int i);
char		*check_spaces_in_quotes(char *s, int i);
char		*remove_quotes(char *s);
void		free_all_tab(char **s_cmd, char **allpath);
void		exit_handler_and_free_double(char **s, int *pipe_fd, int n_exit);
void		exit_handler_and_free_arrays(char *s, int *pipe_fd);
char		**handle_space_in_grep(char **s_cmd, int *pipe_fd);
char		*check_command_in_path(char *cmd);

#endif
