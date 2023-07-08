/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparlak <vparlak@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 11:05:00 by vparlak           #+#    #+#             */
/*   Updated: 2023/01/03 01:03:07 by vparlak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	word_counter(char const *s, char c)
{
	size_t	word_counter;

	word_counter = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{	
			word_counter++;
			while (*s && *s != c)
				s++;
		}
	}
	return (word_counter);
}

char	**ft_split(char const *s, char c)
{
	char	**dst;
	size_t	word_size;
	size_t	letter_counter;

	word_size = word_counter(s, c);
	dst = (char **)malloc((word_size + 1) * sizeof(char *));
	if (!dst)
		return (NULL);
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			letter_counter = 0;
			while (*s && *s != c && ++letter_counter)
				s++;
			*dst++ = ft_substr(s - letter_counter, 0, letter_counter);
		}
	}
	*dst = 0;
	return (dst - word_size);
}
