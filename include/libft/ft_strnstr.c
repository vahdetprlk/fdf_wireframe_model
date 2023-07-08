/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparlak <vparlak@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 09:54:08 by vparlak           #+#    #+#             */
/*   Updated: 2022/12/23 21:44:45 by vparlak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	len_needle;

	len_needle = ft_strlen(needle);
	if (!len_needle)
		return ((char *)haystack);
	while (*haystack != '\0' && len-- >= len_needle)
	{		
		if (!ft_memcmp(haystack++, needle, len_needle))
			return ((char *)--haystack);
	}
	return (NULL);
}
