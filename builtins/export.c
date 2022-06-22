/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:59:22 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/06/22 17:43:23 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_export(t_data *data, int index)
{
	int		i;

	i = 0;
	while (data->env[i])
		i++;
	data->env[i] = data->spllited_cmd_buf[++index];
	data->env[++i] = NULL;
	return (0);
}
