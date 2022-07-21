/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 23:04:29 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/07/21 01:41:24 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	edit_pwd(t_data *data)
{
	char	*tmp;
	int		i;

	i = -1;
	while (data->env[++i])
	{
		if (!ft_strcmp(extract_var_name(data->env[i]), "PWD"))
		{
			tmp = malloc(sizeof(char) * ft_strlen(data->env[i]));
			if (!tmp)
				return (0);
			tmp = ft_strjoin("OLD", data->env[i]);
		}
		else if (!ft_strcmp(extract_var_name(data->env[i]), "OLDPWD"))
		{
			if (ft_strcmp(tmp, data->env[i]))
			data->env[i] = tmp;
			break ;
		}
	}
	i = -1;
	while (data->env[++i])
	{
		if (!ft_strcmp(extract_var_name(data->env[i]), "PWD"))
			data->env[i] = ft_strjoin("PWD=",
					getcwd(data->getpath, sizeof(data->getpath)));
	}
	return (0);
}

int	ft_cd(t_data *data, t_command *cmd, int index)
{
	data->old_pwd = malloc(sizeof(char)
			* ft_strlen(getcwd(data->getpath, sizeof(data->getpath))));
	if (!data->old_pwd)
		return (0);
	data->old_pwd = getcwd(data->getpath, sizeof(data->getpath));
	if (chdir(cmd->cmd_array[++index]) == -1)
	{
		printf("cd: %s: No such file or directory\n", cmd->cmd_array[index]);
		return (0);
	}
	edit_pwd(data);
	return (1);
}
