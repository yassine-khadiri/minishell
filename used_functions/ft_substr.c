/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 23:04:28 by hbouqssi          #+#    #+#             */
/*   Updated: 2022/08/10 01:18:35 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	if (dst == src || !n)
		return (dst);
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	while (i < n)
		d[i++] = '\0';
	return (d);
}

static size_t	ft_getlength(char const *s, unsigned int start, size_t len)
{
	size_t	slen;

	slen = ft_strlen(s) - start;
	if (len < slen)
		return (len);
	else
		return (slen);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	new_length;

	if (!s)
		return (NULL);
	if ((size_t)start > (size_t)ft_strlen(s))
		return (ft_strdup(""));
	new_length = ft_getlength(s, start, len);
	dest = (char *)malloc(sizeof(char) * new_length + 1);
	add(&g_tools.garbage, dest);
	if (dest == NULL)
		return (NULL);
	ft_memcpy(dest, s + start, new_length);
	dest[len] = '\0';
	return (dest);
}
