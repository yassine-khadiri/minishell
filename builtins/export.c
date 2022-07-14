/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:59:22 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/07/14 16:19:57 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	exec_update_val(char *var_name, char *env)
// {
// 	if (!ft_strncmp(extract_var_name(env),
// 			extract_var_name(var_name), ft_strlen(extract_var_name(env)))
// 		&& ft_strlen(extract_var_name(var_name))
// 		- ft_strlen(extract_var_name(env)) == 1
// 		&& var_name[ft_strlen(extract_var_name(var_name)) - 1] == '+')
// 	{
// 		if (!update_append(env, var_name))
// 			return (0);
// 		env = update_append(env, var_name);
// 		return (1);
// 	}
// 	else if (!ft_strcmp(extract_var_name(env),
// 			extract_var_name(var_name)))
// 	{
// 		if (check_equal_sign(var_name))
// 		{
// 			env = var_name;
// 			return (1);
// 		}
// 		return (-1);
// 	}
// 	return (0);
// }

int	update_val(char **env, char *var_name)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(extract_var_name(env[i]),
						extract_var_name(var_name),
						ft_strlen(extract_var_name(env[i]))) &&
			ft_strlen(extract_var_name(var_name))
				- ft_strlen(extract_var_name(env[i])) == 1
				&& var_name[ft_strlen(extract_var_name(var_name)) - 1] == '+')
		{
			if (!update_append(env[i], var_name))
				return (0);
			env[i] = update_append(env[i], var_name);
			return (1);
		}
		else if (!ft_strcmp(extract_var_name(env[i]),
							extract_var_name(var_name)))
		{
			if (check_equal_sign(var_name))
			{
				env[i] = var_name;
				return (1);
			}
			return (-1);
		}
		i++;
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
		if (update_val(data->env, var_name))
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

int	ft_export(t_data *data)
{
	int		i;
	char	*var_name;

	if (!ft_strcmp(data->spllited_cmd_buf[0], "export")
		&& !data->spllited_cmd_buf[1])
	{
		display_export(data);
		return (0);
	}
	i = 1;
	while (data->spllited_cmd_buf[i])
	{
		var_name = ft_strdup(data->spllited_cmd_buf[i]);
		exec_export(data, var_name);
		i++;
	}
	return (0);
}
