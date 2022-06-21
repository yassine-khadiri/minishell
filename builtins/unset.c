/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:56:08 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/06/21 19:14:49 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_unset(t_data *data, int index)
{
	int		i;

	i = 0;
	while (data->env[i])
	{
		if (!ft_strcmp(data->env[i], data->env[++index]))
		{
			data->env[i] = NULL;
			return (0);
		}
		i++;
	}
	return (0);
}

