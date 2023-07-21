/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparlak <vparlak@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 19:05:19 by vparlak           #+#    #+#             */
/*   Updated: 2023/07/21 20:32:45 by vparlak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stddef.h>

int	ft_printf(const char *format, ...);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int	ft_putchar_fd(char c, int fd);
int	ft_puthex_fd(unsigned long hex, int fd, int is_upper);
int	ft_putstr_fd(char *s, int fd);
int	ft_putnbr_fd(long n, int fd);

#endif
