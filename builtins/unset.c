/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:56:08 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/06/22 18:14:51 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_unset(t_data *data, int index)
{
	int		i;
	char	*var_name;

	var_name = ft_strdup(data->spllited_cmd_buf[++index]);
	i = 0;
	while (data->env[i])
	{
		if (!ft_strncmp(data->env[i], var_name, ft_strlen(var_name)))
		{
			data->env[i] = NULL;
			break ;
		}
		i++;
	}
	return (0);
}
