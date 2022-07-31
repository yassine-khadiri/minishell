/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 16:02:52 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/07/21 15:18:49 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		len_s1;
	int		i;
	char	*tab;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	tab = (char *)malloc((len_s1 + ft_strlen(s2) + 1) * sizeof(char));
	i = 0;
	if (tab == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		tab[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i] != '\0')
		tab[len_s1++] = s2[i++];
	tab[len_s1] = '\0';
	return (tab);
}
