/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparlak <vparlak@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 05:56:11 by vparlak           #+#    #+#             */
/*   Updated: 2022/12/30 15:21:08 by vparlak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;
	size_t	len_str;

	len_str = ft_strlen(s);
	if (start >= len_str)
	{
		dst = (char *)malloc(sizeof(char));
		if (!dst)
			return (NULL);
		*dst = '\0';
	}
	else
	{	
		if ((len_str - start) < len)
			len = len_str - start;
		if (len_str >= len)
			dst = (char *)malloc(len + 1);
		else
			dst = (char *)malloc(len_str + 1);
		if (dst == NULL)
			return (NULL);
		ft_strlcpy(dst, s + start, len + 1);
	}
	return (dst);
}
