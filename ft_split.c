/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 14:58:43 by aljulien          #+#    #+#             */
/*   Updated: 2024/04/18 17:01:00 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

static int	count_word(const char *str, char c)
{
	size_t	i;
	int		nb_word;
	int		indic;

	i = 0;
	nb_word = 0;
	indic = 0;
	while (str[i] != '\0')
	{
		if (indic == 0 && str[i] != c)
		{
			indic = 1;
			nb_word++;
		}
		else if (str[i] == c)
			indic = 0;
		i++;
	}
	return (nb_word);
}

static char	**ft_free(char **s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
	s = 0;
	return (s);
}

static char	*fill_word(const char *str, int start, int end)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((end - start + 1) * sizeof(char));
	if (!word || !str)
		return (NULL);
	while (start < end)
	{
		word[i] = str[start];
		i++;
		start++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	size_t		i;
	size_t		j;
	int			indic;
	char		**split;

	i = -1;
	j = 0;
	indic = -1;
	split = malloc((count_word(s, c) + 1) * sizeof(char *));
	if (!s || !split)
		return (NULL);
	split[count_word(s, c)] = 0;
	while (++i <= ft_strlen(s))
	{
		if (s[i] != c && indic < 0)
			indic = i;
		else if ((s[i] == c || (i == ft_strlen(s))) && indic >= 0)
		{
			split[j] = fill_word(s, indic, i);
			if (!split[j++])
				return (ft_free((char **)split));
			indic = -1;
		}
	}
	return (split);
}
