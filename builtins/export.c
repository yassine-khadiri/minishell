/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:59:22 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/07/25 00:18:26 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_update_val(t_data *data, char *var_name, int i)
{
	if (!ft_strncmp(extract_var_name(data->env[i]),
			extract_var_name(var_name),
			ft_strlen(extract_var_name(data->env[i])))
		&& ft_strlen(extract_var_name(var_name))
		- ft_strlen(extract_var_name(data->env[i])) == 1
		&& var_name[ft_strlen(extract_var_name(var_name)) - 1] == '+')
	{
		if (!update_append(data->env[i], var_name))
			return (0);
		data->env[i] = update_append(data->env[i], var_name);
		return (1);
	}
	else if (!ft_strcmp(extract_var_name(data->env[i]),
			extract_var_name(var_name)))
	{
		if (check_equal_sign(var_name))
		{
			data->env[i] = var_name;
			return (1);
		}
		return (-1);
	}
	return (2);
}

int	update_val(t_data *data, char *var_name)
{
	int	i;
	int	ret;

	i = 0;
	while (data->env[i])
	{
		ret = exec_update_val(data, var_name, i);
		if (ret == 2)
			i++;
		else
			return (ret);
	}
	return (0);
}

int	check_env_var(char *env_var)
{
	int		i;
	char	*extracted_var;

	i = 0;
	if (!ft_isalpha(env_var[0]) && env_var[0] != '_')
		return (1);
	extracted_var = extract_var_name(env_var);
	if (!ft_strcmp(extracted_var, "_"))
		return (-1);
	else if (check_dash_err(extracted_var) || !is_validated(extracted_var,
			env_var))
		return (1);
	return (0);
}

void	exec_export(t_data *data, char *var_name)
{
	int	j;

	j = 0;
	if (check_env_var(var_name) == 1)
		printf("minishell: export: `%s': not a valid identifier\n", var_name);
	else if (check_env_var(var_name) == 0)
	{
		if (update_val(data, var_name))
			return ;
		else
		{
			while (data->env[j])
				j++;
			if (!ignore_something(var_name))
				data->env[j] = var_name;
			else
				data->env[j] = ignore_something(var_name);
			data->env[++j] = NULL;
		}
	}
}

int	ft_export(t_data *data, t_command *cmd)
{
	int		i;
	char	*var_name;

	if (!ft_strcmp(cmd->cmd_array[0], "export") && !cmd->cmd_array[1])
	{
		display_export(data);
		return (0);
	}
	i = 1;
	while (cmd->cmd_array[i])
	{
		var_name = ft_strdup(cmd->cmd_array[i]);
		exec_export(data, var_name);
		i++;
	}
	return (1);
}
