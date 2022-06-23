/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:59:22 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/06/23 18:24:15 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*extract_var_name(char *string)
{
	char	*extracted_var_name;
	int		i;

	i = 0;
	while (string[i])
	{
		if (string[i] == '=')
			break ;
		i++;
	}
	extracted_var_name = malloc(sizeof(char) * (i + 1));
	if (!extracted_var_name)
		return (NULL);
	i = 0;
	while (string[i])
	{
		extracted_var_name[i] = string[i];
		if (string[i] == '=')
		{
			extracted_var_name[i] = '\0';
			return (extracted_var_name);
		}
		i++;
	}
	return (NULL);
}

int	update_val(char **env, char *var_name)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (!ft_strcmp(extract_var_name(env[i]), extract_var_name(var_name)))
		{
			env[i] = var_name;
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
	int	i;

	i = 0;
	if (!without_name_hh(var_env)
		&& (ft_isalpha(var_env[0]) || var_env[0] == '_'))
	{
		while (var_env[i])
		{
			if (var_env[i] == '=')
				return (0);
			i++;
		}
	}
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
			data->env[i] = var_name;
			data->env[++i] = NULL;
		}
	}
	return (0);
}
