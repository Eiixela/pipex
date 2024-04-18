/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aux_pf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 11:35:45 by adiaz-be          #+#    #+#             */
/*   Updated: 2023/12/23 13:10:56 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_strlen_pf(const char *str)
{
	size_t	c;

	if (!str)
		return (0);
	c = 0;
	while (str[c])
		c++;
	return (c);
}

void	ft_bzero_pf(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n > 0)
	{
		*ptr = 0;
		ptr++;
		n--;
	}
}

void	*ft_calloc_pf(size_t number, size_t size)
{
	void	*dest;

	dest = malloc (number * size);
	if (dest == NULL)
		return (NULL);
	ft_bzero_pf(dest, number * size);
	return (dest);
}

static size_t	ft_len(unsigned long long n, char *base)
{
	size_t				len;
	unsigned long long	base_len;

	len = 1;
	base_len = ft_strlen_pf(base);
	while (n >= base_len)
	{
		n /= base_len;
		len++;
	}
	return (len);
}

char	*ft_aux_pf(unsigned long long n, char *base)
{
	char	*str;
	int		num_len;
	int		base_len;

	num_len = ft_len(n, base);
	base_len = ft_strlen_pf(base);
	str = ft_calloc_pf((num_len + 1), sizeof(char));
	if (!str)
		return (NULL);
	while (num_len)
	{
		num_len--;
		str[num_len] = base[n % base_len];
		n /= base_len;
	}
	return (str);
}
