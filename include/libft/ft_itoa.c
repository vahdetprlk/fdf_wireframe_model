/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparlak <vparlak@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 12:10:44 by vparlak           #+#    #+#             */
/*   Updated: 2022/12/29 02:33:07 by vparlak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_baselen(int n)
{
	int		tmp;
	size_t	base_len;

	tmp = n;
	base_len = 0;
	if (n == 0)
		return (1);
	while (tmp)
	{
		tmp /= 10;
		base_len++;
	}
	return (base_len);
}

char	*ft_itoa(int n)
{
	size_t	len;
	char	*nbr_chr;
	long	nbr;

	nbr = n;
	len = ft_baselen(nbr);
	if (n < 0)
	{
		len++;
		nbr = -nbr;
	}
	nbr_chr = (char *)malloc(sizeof(char) * len + 1);
	if (!nbr_chr)
		return (NULL);
	nbr_chr[len] = '\0';
	while (nbr > 0)
	{
		nbr_chr[--len] = nbr % 10 + '0';
		nbr /= 10;
	}
	if (n < 0)
		nbr_chr[0] = '-';
	if (n == 0)
		nbr_chr[0] = '0';
	return (nbr_chr);
}
