/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 23:50:41 by hbouqssi          #+#    #+#             */
/*   Updated: 2022/08/16 19:44:02 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*crd_res_helper(t_data *data, char *cmd, char *var_name)
{
	int	j;

	j = 0;
	data->dollar_counter = 0;
	while (cmd[data->g_index] && cmd[data->g_index] == '$')
	{
		data->dollar_counter++;
		var_name[j++] = cmd[data->g_index++];
	}
	while (cmd[data->g_index] && ft_isalnum(cmd[data->g_index]))
		var_name[j++] = cmd[data->g_index++];
	var_name[j] = '\0';
	return (var_name);
}

char	*crd_res(t_data *data, char *cmd, char *var_name, char *res)
{
	int	j;

	data->g_index = 0;
	while (cmd[data->g_index])
	{
		j = 0;
		var_name = crd_res_helper(data, cmd, var_name);
		if (data->dollar_counter > 1 || data->dollar_counter == 0
			|| (data->dollar_counter == 1
				&& !var_name[data->dollar_counter]))
			res = ft_strjoin(res, var_name);
		else
			res = ft_strjoin(res, check_res(var_name, data->env));
		j = 0;
		while (cmd[data->g_index] && cmd[data->g_index] != '$'
			&& !ft_isalnum(cmd[data->g_index])
			&& check_res(var_name, data->env))
			var_name[j++] = cmd[data->g_index++];
		var_name[j] = '\0';
		res = ft_strjoin(res, var_name);
	}
	return (res);
}
