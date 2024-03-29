/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 23:04:29 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/08/13 20:24:25 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_old_pwd(t_data *data)
{
	char	*tmp;
	int		i;

	i = -1;
	tmp = NULL;
	while (data->env[++i])
	{
		if (!ft_strcmp(extract_var_name(data->env[i]), "PWD"))
			tmp = ft_strjoin("OLD", data->env[i]);
		else if (tmp && !ft_strcmp(extract_var_name(data->env[i]), "OLDPWD"))
		{
			if (ft_strcmp(tmp, data->env[i]))
				data->env[i] = tmp;
			break ;
		}
	}
	return (1);
}

int	edit_pwd(t_data *data)
{
	int		i;
	char	*tmp;

	i = -1;
	get_old_pwd(data);
	while (data->env[++i])
	{
		tmp = extract_var_name(data->env[i]);
		if (!ft_strcmp(tmp, "PWD"))
		{
			data->env[i] = ft_strjoin("PWD=", getcwd(data->getpath,
						sizeof(data->getpath)));
			break ;
		}
	}
	return (0);
}

int	ft_cd(t_data *data, t_command *cmd, int index)
{
	if (!cmd->cmd_array[index + 1])
		cmd->cmd_array[index + 1] = get_val_env_var(data->env, "HOME");
	if (chdir(cmd->cmd_array[index + 1]) == -1)
	{
		write(2, RED "minishell: ", 19);
		write(2, cmd->cmd_array[index + 1],
			ft_strlen(cmd->cmd_array[index + 1]));
		write(2, ": No such file or directory\n" BLU, 36);
		return (0);
	}
	edit_pwd(data);
	return (1);
}
