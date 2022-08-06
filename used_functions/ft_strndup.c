/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouqssi <hbouqssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 18:28:28 by hbouqssi          #+#    #+#             */
/*   Updated: 2022/08/06 18:56:39 by hbouqssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strndup(const char *s1, int size)
{
	char	*s;
	int		i;
	i = 0;
	s = (char *)malloc(sizeof(char) * (size + 1));
	if(!s)
		return (0);
	while (s1[i] != '\0' && i < size)
	{
		s[i] = s1[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}
