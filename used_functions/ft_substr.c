/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 23:04:28 by hbouqssi          #+#    #+#             */
/*   Updated: 2022/07/14 16:20:19 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *ft_substr(char const *s, unsigned int start, size_t len)
{
	char *dest;
	unsigned int i;
	size_t j;
	if (!s)
		return (NULL);
	j = ft_strlen(s);
	if (j < start)
		return (ft_strdup("\0"));
	if (len >= j)
		if (!(dest = (char *)malloc(sizeof(char) * ((j - start) + 1))))
			return (NULL);
	if (len < j)
		if (!(dest = (char *)malloc(sizeof(char) * (len + 1))))
			return (NULL);
	i = start;
	j = 0;
	while (s[i] != '\0' && j < len)
	{
		dest[j] = s[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (dest);
}