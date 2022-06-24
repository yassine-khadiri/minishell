/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_String.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 15:49:02 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/06/24 19:47:01 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

int is_String(char *string)
{
    int i;
    int j;

    i = 0;
    while (ft_isalpha(string[i]) || string[i] == '_'
            || ft_isdigit(string[i]))
        i++;
    j = 0;
    while (string[j])
        j++;
	if (string[--j] == '+' && string[--j] != '+')
		i++;
    if (ft_strlen(string) == i)
        return (1);
    return (0);
}