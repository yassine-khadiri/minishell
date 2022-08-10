/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_export_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:14:12 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/08/10 19:01:25 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_extr_var_name(char *string, char *extr_var_name)
{
	int	i;

	i = 0;
	while (string[i])
	{
		extr_var_name[i] = string[i];
		if (string[i] == '=')
		{
			extr_var_name[i] = '\0';
			return (extr_var_name);
		}
		i++;
	}
	return (string);
}

char	*extract_var_name(char *string)
{
	char	*extr_var_name;
	int		i;

	i = check_equal_sign(string);
	if (i)
	{
		extr_var_name = malloc(sizeof(char) * i);
		add(&g_tools.garbage, extr_var_name);
	}
	else
	{
		extr_var_name = malloc(sizeof(char) * ft_strlen(string) + 1);
		add(&g_tools.garbage, extr_var_name);
	}
	if (!extr_var_name)
		return (NULL);
	return (get_extr_var_name(string, extr_var_name));
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

char	*exec_update(char *var_name)
{
	char	*next_val;
	int		i;
	int		j;

	i = 0;
	j = 0;
	next_val = malloc(sizeof(char) * 1000);
	add(&g_tools.garbage, next_val);
	if (!next_val)
		return (NULL);
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
	return (next_val);
}

char	*update_append(char *env, char *var_name)
{
	if (!check_equal_sign(env))
		env = ft_strjoin(env, "=");
	env = ft_strjoin(env, exec_update(var_name));
	return (env);
}
