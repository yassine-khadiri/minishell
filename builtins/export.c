/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:59:22 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/06/25 18:36:58 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*update_append(char *env, char *var_name)
{
	char	*next_val;
	int		i;
	int		j;

	next_val = malloc(sizeof(char) * 1000);
	if (!next_val)
		return (NULL);
	i = 0;
	j = 0;
	while (var_name[i])
	{
		if (var_name[i] == '=' && var_name[i - 1] != '+')
			return (0);
		else if (var_name[i] == '=' && var_name[i - 1] == '+')
		{
			i++;
			while (var_name[j])
				next_val[j++] = var_name[i++];
			next_val[j] = '\0';
			break ;
		}
		i++;
	}
	env = ft_strjoin(env, next_val);
	return (free(next_val), env);
}

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

int	without_name_hh(char *var_env)
{
	int	i;

	i = 0;
	var_env = extract_var_name(var_env);
	while (var_env[i])
	{
		if (var_env[i] == '-')
			return (1);
		i++;
	}
	return (0);
}

int	check_exported_var_env(char *var_env)
{
	int		i;
	char	*extracted_var;

	i = 0;
	extracted_var = ft_strdup(extract_var_name(var_env));
	if (!without_name_hh(var_env)
		&& extract_var_name(var_env)
		&& is_String(extracted_var)
		&& !ft_isdigit(extracted_var[0]))
		return (0);
	printf("minishell: export: `%s': not a valid identifier\n", var_env);
	return (1);
}

int	ft_export(t_data *data, int index)
{
	int		i;
	char	*var_name;

	i = 0;
	var_name = ft_strdup(data->spllited_cmd_buf[++index]);
	if (!check_exported_var_env(var_name))
	{
		if (update_val(data->env, var_name))
			return (0);
		else
		{
			while (data->env[i])
				i++;
			if (!ignore_something(var_name))
				data->env[i] = var_name;
			else
				data->env[i] = ignore_something(var_name);
			data->env[++i] = NULL;
		}
	}
	return (0);
}
