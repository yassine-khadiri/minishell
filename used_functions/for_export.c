/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 18:22:13 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/06/30 14:31:14 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_equal_sign(char *env_var)
{
	int	i;

	i = 1;
	while (env_var[i])
	{
		if (env_var[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

char	*extract_var_name(char *string)
{
	char	*extr_var_name;
	int		i;

	i = check_equal_sign(string);
	if (i)
		extr_var_name = malloc(sizeof(char) * i);
	else
		extr_var_name = malloc(sizeof(char) * ft_strlen(string) + 1);
	if (!extr_var_name)
		return (NULL);
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
	extr_var_name = string;
	return (extr_var_name);
}

char	*ignore_something(char *var_name)
{
	char	*new_var;
	bool	val;
	int		i;
	int		j;

	i = -1;
	j = -1;
	val = false;
	new_var = malloc(sizeof(char) * ft_strlen(var_name));
	if (!new_var)
		return (NULL);
	while (var_name[++i])
	{
		if (var_name[i] == '+' && var_name[i + 1] == '=')
		{
			val = true;
			++i;
		}
		new_var[++j] = var_name[i];
	}
	new_var[++j] = '\0';
	if (val)
		return (new_var);
	return (NULL);
}

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
	if (!check_equal_sign(env))
		env = ft_strjoin(env, "=");
	env = ft_strjoin(env, next_val);
	return (env);
}

void	sort_data(t_data *data, int len, int step)
{
	int		i;
	int		j;
	char	*tmp;

	while (step < len - 1)
	{
		i = 0;
		while (i < len - step - 1)
		{
			j = 0;
			while (data->env[i][j])
			{
				if (data->env[i][j] == data->env[i + 1][j])
					j++;
				else if (data->env[i][j] > data->env[i + 1][j])
				{
					tmp = data->env[i];
					data->env[i] = data->env[i + 1];
					data->env[i + 1] = tmp;
					break ;
				}
				else
					break ;
			}
			i++;
		}
		step++;
	}
}

void	display_export(t_data *data)
{
	int		i;
	int		len;
	int		step;

	step = 0;
	len = 0;
	while (data->env[len])
		len++;
	sort_data(data, len, step);
	i = 0;
	while (data->env[i])
		printf("declare -x %s\n", data->env[i++]);
}
