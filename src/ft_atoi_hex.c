/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparlak <vparlak@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 18:25:44 by vparlak           #+#    #+#             */
/*   Updated: 2023/09/16 19:03:30 by vparlak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_test(int c)
{
	int	i;

	i = 0;
	while (i < 16)
	{
		if ("0123456789ABCDEF"[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	ft_atoi_hex(const char *str)
{
	int	sign;
	int	result;

	sign = 1;
	result = 0;
	if (!str)
		return (0);
	if (!ft_strncmp("0x", str, 2))
		str += 2;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
	{
		sign *= -1;
		str++;
	}
	else if (*str == '+')
		str++;
	if (*str == '-' || *str == '+')
		return (0);
	while (ft_test(*str) != -1)
		result = (result * 16) + ft_test(*str++);
	return (result * sign);
}
