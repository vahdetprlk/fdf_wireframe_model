/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparlak <vparlak@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 22:32:01 by vparlak           #+#    #+#             */
/*   Updated: 2023/06/15 23:54:46 by vparlak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	size_t	dstsize;

	dstsize = ft_strlen(s1) + ft_strlen(s2) + 1;
	dst = (char *)malloc(dstsize);
	if (dst == NULL)
		return (NULL);
	ft_strlcpy(dst, s1, dstsize);
	ft_strlcat(dst, s2, dstsize);
	return (dst);
}
