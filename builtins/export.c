/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:59:22 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/06/22 20:08:47 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	without_name_hh(char *var_env)
{
	int	i;

	i = 0;
	while (var_env[i])
	{
		if (var_env[i] == '-')
			return (1);
		i++;
	}
	return (0);
}

int	check_exported_var_env(char *var_env)
{
	int	i;

	i = 0;
	if (!without_name_hh(var_env)
		&& (ft_isalpha(var_env[0]) || var_env[0] == '_'))
	{
		while (var_env[i])
		{
			if (var_env[i] == '=')
				return (0);
			i++;
		}
	}
	printf("minishell: export: `%s': not a valid identifier\n", var_env);
	return (1);
}

int	ft_export(t_data *data, int index)
{
	int		i;
	char	*var_name;

	i = 0;
	var_name = ft_strdup(data->spllited_cmd_buf[++index]);
	if (!check_exported_var_env(var_name))
	{
		while (data->env[i])
			i++;
		data->env[i] = var_name;
		data->env[++i] = NULL;
	}
	return (0);
}
