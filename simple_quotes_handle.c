/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_quotes_handle.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:50:56 by aljulien          #+#    #+#             */
/*   Updated: 2024/04/26 18:08:09 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*check_spaces_in_quotes(char *s)
{
	int		i;
	char	*final;

	i = -1;
	final = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!final)
		return (NULL);
	while (s[++i] != '\0')
	{
		if (s[i] == 39)
		{
			final[i] = s[i];
			while (s[++i] != 39)
			{
				if (s[i] == 32)
					final[i] = -32;
				else
					final[i] = s[i];
			}
			final[i] = s[i];
		}
		else
			final[i] = s[i];
	}
	return (final);
}

char	*get_spaces_in_quotes_back(char *s)
{
	int		i;
	char	*final;

	i = -1;
	final = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!final)
		return (NULL);
	while (s[++i] != '\0')
	{
		if (s[i] == 39)
		{
			final[i] = s[i];
			while (s[++i] != 39)
			{
				if (s[i] == -32)
					final[i] = 32;
				else
					final[i] = s[i];
			}
			final[i] = s[i];
		}
		else
			final[i] = s[i];
	}
	return (final);
}

char	*remove_quotes(char *s)
{
	char	*final;
	int		i;
	int		j;

	final = malloc((ft_strlen(s) + 1) * sizeof(char));
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == 39)
			i++;
		else
		{
			final[j] = s[i];
			i++;
			j++;
		}
	}
	while (j <= i)
	{
		final[j] = '\0';
		j++;
	}
	return (final);
}
