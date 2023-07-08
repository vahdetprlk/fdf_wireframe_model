/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparlak <vparlak@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 04:50:25 by vparlak           #+#    #+#             */
/*   Updated: 2022/12/24 23:10:58 by vparlak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len_s1;
	char	*dst;

	len_s1 = ft_strlen(s1) + 1;
	dst = (char *)malloc(len_s1);
	if (dst == NULL)
		return (dst);
	ft_strlcpy(dst, s1, len_s1);
	return (dst);
}
