/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_space.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 16:01:54 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/08/10 01:18:05 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_space(char *s1, char *s2)
{
	int		len_s1;
	int		i;
	char	*tab;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1) + 1;
	tab = (char *)malloc((len_s1 + ft_strlen(s2) + 1) * sizeof(char));
	add(&g_tools.garbage, tab);
	i = 0;
	if (tab == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		tab[i] = s1[i];
		i++;
	}
	tab[i] = ' ';
	i = 0;
	while (s2[i] != '\0')
		tab[len_s1++] = s2[i++];
	tab[len_s1] = '\0';
	free(s1);
	return (tab);
}
