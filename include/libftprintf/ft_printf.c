/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparlak <vparlak@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:37:30 by vparlak           #+#    #+#             */
/*   Updated: 2023/03/13 17:15:31 by vparlak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_check_specifier(const char *format, va_list args, int *count)
{
	while (*format)
	{
		if (!ft_strncmp(format, "%p", 2) || !ft_strncmp(format, "%d", 2)
			|| !ft_strncmp(format, "%i", 2) || !ft_strncmp(format, "%u", 2)
			|| !ft_strncmp(format, "%x", 2) || !ft_strncmp(format, "%X", 2))
		{
			ft_print_any(args, (char *)format, count);
			format++;
		}
		else if (!ft_strncmp(format, "%s", 2) || !ft_strncmp(format, "%c", 2)
			|| !ft_strncmp(format, "%%", 2))
		{
			ft_print_any_2(args, (char *)format, count);
			format++;
		}
		else if (!ft_strncmp(format, "%", 1))
			format++;
		else
			*count += ft_putchar_fd(*format, 1);
		format++;
	}
	return ((char *)format);
}

void	ft_print_any_2(va_list args, char *format, int *count)
{
	char	*str;

	if (!ft_strncmp(format, "%s", 2))
	{
		str = va_arg(args, char *);
		if (str)
		*count += ft_putstr_fd(str, 1);
		else
		*count += ft_putstr_fd("(null)", 1);
	}
	if (!ft_strncmp(format, "%c", 2))
		*count += ft_putchar_fd(va_arg(args, int), 1);
	if (!ft_strncmp(format, "%%", 2))
		*count += ft_putchar_fd('%', 1);
}

void	ft_print_any(va_list args, char *format, int *count)
{
	if (!ft_strncmp(format, "%p", 2))
	{
		*count += ft_putstr_fd("0x", 1);
		*count += ft_puthex_fd(va_arg(args, unsigned long), 1, 0);
	}
	if (!ft_strncmp(format, "%d", 2) || !ft_strncmp(format, "%i", 2))
		*count += ft_putnbr_fd(va_arg(args, int), 1);
	if (!ft_strncmp(format, "%u", 2))
		*count += ft_putnbr_fd(va_arg(args, unsigned int), 1);
	if (!ft_strncmp(format, "%x", 2))
		*count += ft_puthex_fd(va_arg(args, unsigned int), 1, 0);
	if (!ft_strncmp(format, "%X", 2))
		*count += ft_puthex_fd(va_arg(args, unsigned int), 1, 1);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		*count;
	int		i;

	i = 0;
	count = &i;
	va_start(args, format);
		format = ft_check_specifier(format, args, count);
	va_end(args);
	return (i);
}
