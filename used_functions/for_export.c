/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 18:22:13 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/06/28 19:55:00 by ykhadiri         ###   ########.fr       */
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
	char	*extracted_var_name;
	int		i;

	i = 0;
	if (check_equal_sign(string) || check_equal_sign(string) == -1)
		return (NULL);
	extracted_var_name = malloc(sizeof(char) * (check_equal_sign(string) + 1));
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
	env = ft_strjoin(env, next_val);
	return (env);
}

void	display_export(t_data *data)
{
	int	i;
	int	len = 0;
	char	*tmp;

	while (data->env[len])
		len++;
	i = 0;
	while (i < len - 1)
	{
		// if (ft_strcmp(extract_var_name(data->env[i]), extract_var_name(data->env[i + 1])) > 0)
		// {
		// 	tmp = ft_strdup(data->env[i]);
		// 	data->env[i] = data->env[i + 1];
		// 	data->env[i + 1] = tmp;
		// }
		if (data->env[i][0] > data->env[i + 1][0])
		{
			tmp = ft_strdup(data->env[i]);
			data->env[i] = data->env[i + 1];
			data->env[i + 1] = tmp;
		}
		printf("declare -x %s\n", data->env[i]);	
		i++;
	}
}