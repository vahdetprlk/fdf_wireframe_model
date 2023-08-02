/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparlak <vparlak@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 19:37:31 by vparlak           #+#    #+#             */
/*   Updated: 2023/07/21 22:19:18 by vparlak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	str1;
	unsigned char	str2;

	while (n-- && (*s1 || *s2))
	{
		str1 = (unsigned char)*s1++;
		str2 = (unsigned char)*s2++;
		if (str1 != str2)
			return (str1 - str2);
	}
	return (0);
}

int	ft_putchar_fd(char c, int fd)
{
	return (write(fd, &c, 1));
}

int	ft_putstr_fd(char *s, int fd)
{
	int	count;

	count = 0;
	while (*s)
		count += ft_putchar_fd(*s++, fd);
	return (count);
}

int	ft_puthex_fd(unsigned long hex, int fd, int is_upper)
{
	int	count;

	count = 0;
	if (hex < 16)
	{
		if (!is_upper)
			count += write(fd, &"0123456789abcdef"[hex % 16], 1);
		else
			count += write(fd, &"0123456789ABCDEF"[hex % 16], 1);
	}
	if (hex >= 16)
	{
		count += ft_puthex_fd(hex / 16, fd, is_upper);
		count += ft_puthex_fd(hex % 16, fd, is_upper);
	}
	return (count);
}

int	ft_putnbr_fd(long n, int fd)
{
	long	nbr;
	int		count;

	count = 0;
	nbr = n;
	if (nbr < 0)
	{
		count += ft_putchar_fd('-', fd);
		nbr = -nbr;
	}
	if (nbr >= 10)
	{
		count += ft_putnbr_fd(nbr / 10, fd);
	}
	count += ft_putchar_fd(nbr % 10 + '0', fd);
	return (count);
}
