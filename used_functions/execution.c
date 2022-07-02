/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:49:51 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/07/01 11:53:38 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_get_spllited_string(char *str)
{
	char	**get_spllited_string;
	// get_spllited_string = malloc(sizeof(char *) * ft_strlen(str));
	// if(!get_spllited_string)
	// 	return (NULL);
	get_spllited_string = ft_split(str, ' ');
	return (get_spllited_string);
}

void	edit_pwd(char **env)
{
	char	*pwd;
	char	*old_pwd;

	pwd = get_val_env_var(env, "PWD");
	old_pwd = get_val_env_var(env, "OLDPWD");
}

void	execution(t_data *data)
{
	data->spllited_cmd_buf = ft_get_spllited_string(data->command_buf);
	if (cmd_founded_y_n(data) == -1)
		return ;
	if (pipe_founded(data) && ft_pipe(data))
		return ;
	rdr_execution(data);
	builtins_execution(data);
}
