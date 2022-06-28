/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:59:22 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/06/28 11:25:43 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	update_val(char **env, char *var_name)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], extract_var_name(var_name),
				ft_strlen(extract_var_name(var_name))))
		{
			env[i] = var_name;
			return (1);
		}
		else if (!ft_strncmp(env[i], var_name,
				ft_strlen(extract_var_name(env[i])))
			&& ft_strlen(extract_var_name(var_name))
			- ft_strlen(extract_var_name(env[i])) == 1)
		{
			if (!update_append(env[i], var_name))
				return (0);
			env[i] = update_append(env[i], var_name);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_dash_err(char *env_var)
{
	int	i;

	i = 0;
	if (!env_var)
		return (0);
	while (env_var[i])
	{
		if (env_var[i] == '-')
			return (1);
		i++;
	}
	return (0);
}

int	check_env_var(char *env_var)
{
	int		i;
	char	*extracted_var;

	if (!check_equal_sign(env_var))
		return (-1);
	else if (check_equal_sign(env_var) == -1)
		return (1);
	i = 0;
	extracted_var = extract_var_name(env_var);
	if (check_dash_err(extracted_var)
		|| !is_validated(extracted_var))
		return (1);
	return (0);
}

void	exec_export(t_data *data, char *var_name)
{
	int	j;

	j = 0;
	if (check_env_var(var_name) == 1)
		printf("minishell: export: `%s': \
				not a valid identifier\n", var_name);
	else if (check_env_var(var_name) == 0)
	{
		if (update_val(data->env, var_name))
			update_val(data->env, var_name);
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
	int		j;
	char	*var_name;

	i = 1;
	while (data->spllited_cmd_buf[i])
	{
		j = 0;
		var_name = ft_strdup(ft_strtrim(data->spllited_cmd_buf[i], "\\"));
		exec_export(data, var_name);
		i++;
	}
	return (0);
}
