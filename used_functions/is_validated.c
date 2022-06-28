/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_validated.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 11:30:21 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/06/28 19:08:22 by ykhadiri         ###   ########.fr       */
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

int	is_validated(char *var_name)
{
	int	i;
	int	j;

	i = 0;
	while (ft_isalpha(var_name[i]) || var_name[i] == '_'
		|| ft_isdigit(var_name[i]))
		i++;
	j = 0;
	while (var_name[j])
		j++;
	if (var_name[--j] == '+' && var_name[--j] != '+')
		i++;
	if (ft_strlen(var_name) == i)
		return (1);
	return (0);
}
