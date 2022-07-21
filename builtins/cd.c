/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 23:04:29 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/07/21 00:57:06 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	edit_pwd(t_data *data)
{
	int	i;
	puts(data->old_pwd);
// (void)old_pwd;
	// puts(old_pwd);
	i = 0;
		// puts("HERE");
	char	*tmp;
	while (data->env[i])
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
			break;
		}
		i++;
	}
	i = 0;
	while (data->env[i])
	{
		if (!ft_strcmp(extract_var_name(data->env[i]), "PWD"))
		data->env[i] = ft_strjoin("PWD=", getcwd(data->getpath, sizeof(data->getpath)));
		// else if (!ft_strcmp(extract_var_name(data->env[i]), "OLDPWD"))
		// {
		// 	// puts("HERE");
		// data->env[i] = ft_strjoin("OLDPWD=", data->old_pwd);
		// }
		// if (data->env[i + 1] == NULL)
		// {
		// 	data->env[i + 1] = ft_strjoin("OLDPWD=", old_pwd);
		// 	data->env[i + 2] = NULL;
		// 	return (1);
		// }
		i++;
	}
	return (0);
}

int	ft_cd(t_data *data, t_command *cmd, int index)
{
	data->old_pwd = malloc(sizeof(char) * ft_strlen(getcwd(data->getpath, sizeof(data->getpath))));
	if (!data->old_pwd)
		return (0);
	data->old_pwd = getcwd(data->getpath, sizeof(data->getpath));
	// puts(get_old_cwd);
	if (chdir(cmd->cmd_array[++index]) == -1)
	{
		printf("cd: %s: No such file or directory\n", cmd->cmd_array[index]);
		return (0);
	}
	edit_pwd(data);
	return (1);
}