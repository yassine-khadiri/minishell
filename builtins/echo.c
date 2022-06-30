/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 12:28:52 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/06/30 17:16:45 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_var(char *var_name, char **env)
{
	var_name = ft_strtrim(var_name, "$");
	if (get_val_env_var(env, var_name))
		printf("%s\n", get_val_env_var(env, var_name));
	else
		printf("\n");
}

int	ft_echo(t_data *data, int index)
{
	if (!data->spllited_cmd_buf[index + 1])
		printf("\n");
	else if (data->spllited_cmd_buf[++index][0] == '$')
		check_var(data->spllited_cmd_buf[index], data->env);
	else if (!ft_strcmp(data->spllited_cmd_buf[index], "-n"))
		printf("%s", ft_strtrim(data->spllited_cmd_buf[++index], "\""));
	else
		printf("%s\n", ft_strtrim(data->spllited_cmd_buf[index], "\""));
	return (0);
}
