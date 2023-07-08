/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparlak <vparlak@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:19:11 by vparlak           #+#    #+#             */
/*   Updated: 2023/06/14 20:58:54 by vparlak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
