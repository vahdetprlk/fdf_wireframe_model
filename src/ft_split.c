/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparlak <vparlak@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:50:31 by vparlak           #+#    #+#             */
/*   Updated: 2023/09/17 14:40:20 by vparlak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>

static void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const char	*s;
	char		*d;

	d = (char *)dst;
	s = (const char *)src;
	if (!d && !s)
		return (NULL);
	while (n--)
		*d++ = *s++;
	return (dst);
}

static size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	len_src;
	size_t	len;

	len_src = 0;
	while (src[len_src] != '\0')
		len_src++;
	if (dstsize)
	{
		if (len_src >= dstsize)
			len = dstsize - 1;
		else
			len = len_src;
		ft_memcpy(dst, src, len);
		dst[len] = '\0';
	}
	return (len_src);
}

static size_t	ft_nb_words(char const *s, char c)
{
	size_t	i;
	size_t	nb_words;

	if (!s[0])
		return (0);
	i = 0;
	nb_words = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c)
		{
			nb_words++;
			while (s[i] && s[i] == c)
				i++;
			continue ;
		}
		i++;
	}
	if (s[i - 1] != c)
		nb_words++;
	return (nb_words);
}

static void	ft_get_next_word(char **next_word, size_t *next_word_len, char c)
{
	size_t	i;

	*next_word += *next_word_len;
	*next_word_len = 0;
	i = 0;
	while (**next_word && **next_word == c)
		(*next_word)++;
	while ((*next_word)[i])
	{
		if ((*next_word)[i] == c)
			return ;
		(*next_word_len)++;
		i++;
	}
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	char	*next_word;
	size_t	next_word_len;
	size_t	i;

	if (!s)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * (ft_nb_words(s, c) + 1));
	if (!tab)
		return (NULL);
	i = 0;
	next_word = (char *)s;
	next_word_len = 0;
	while (i < ft_nb_words(s, c))
	{
		ft_get_next_word(&next_word, &next_word_len, c);
		tab[i] = (char *)malloc(sizeof(char) * (next_word_len + 1));
		if (!tab[i])
			return (ft_free_tab(tab));
		ft_strlcpy(tab[i], next_word, next_word_len + 1);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
