/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 18:28:28 by hbouqssi          #+#    #+#             */
/*   Updated: 2022/08/10 01:19:45 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strndup(const char *s1, int size)
{
	char	*s;
	int		i;

	i = 0;
	s = (char *)malloc(sizeof(char) * (size + 1));
	add(&g_tools.garbage, s);
	while (s1[i] != '\0' && i < size)
	{
		s[i] = s1[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}
