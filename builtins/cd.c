/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 23:04:29 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/08/07 22:42:01 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_old_pwd(t_data *data)
{
	char	*tmp_1;
	char	*tmp_2;
	int		i;

	i = -1;
	tmp_1 = NULL;
	while (data->env[++i])
	{
		tmp_2 = extract_var_name(data->env[i]);
		if (!ft_strcmp(tmp_2, "PWD"))
			tmp_1 = ft_strjoin("OLD", data->env[i]);
		else if (tmp_1 && !ft_strcmp(tmp_2, "OLDPWD"))
		{
			if (ft_strcmp(tmp_1, data->env[i]))
				data->env[i] = tmp_1;
			break ;
		}
	}
	free(tmp_1);
	free(tmp_2);
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
			data->env[i] = ft_strjoin("PWD=",
					getcwd(data->getpath, sizeof(data->getpath)));
			break ;
		}
	}
	free(tmp);
	return (0);
}

int	ft_cd(t_data *data, t_command *cmd, int index)
{
	if (!cmd->cmd_array[index + 1])
		cmd->cmd_array[index + 1] = get_val_env_var(data->env, "HOME");
	if (chdir(cmd->cmd_array[index + 1]) == -1)
		return (0);
	edit_pwd(data);
	return (1);
}
