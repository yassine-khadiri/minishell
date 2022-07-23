/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 16:37:45 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/07/23 16:38:05 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_val_env_var1(char **env, char *env_variable)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strcmp(extract_var_name(env[i]), env_variable))
			return (env[i] + ft_strlen(env_variable) + 1);
		i++;
	}
	return (NULL);
}

char	*check_res(char *var_name, char **env)
{
	if (get_val_env_var1(env, var_name))
		var_name = get_val_env_var1(env, var_name);
	else
		var_name = "";
	return (var_name);
}
