/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparlak <vparlak@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 16:24:17 by vparlak           #+#    #+#             */
/*   Updated: 2022/12/24 04:46:15 by vparlak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	size_t	len_str;

	str = (char *)s;
	len_str = ft_strlen(str);
	while (len_str >= 0)
	{
		if (str[len_str] == (char)c)
			return (str + len_str);
		else if (len_str == 0)
			return (NULL);
		if (len_str > 0)
			len_str--;
	}
	return (NULL);
}
