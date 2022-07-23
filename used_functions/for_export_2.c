/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_export_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:14:40 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/07/23 17:38:04 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sort_data_helper(t_data *data, int i)
{
	char	*tmp;
	int		j;

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
}

void	sort_data(t_data *data, int len, int step)
{
	int		i;

	while (step < len - 1)
	{
		i = 0;
		while (i < len - step - 1)
		{
			sort_data_helper(data, i);
			i++;
		}
		step++;
	}
}

void	display_export(t_data *data)
{
	int	i;
	int	len;
	int	step;

	step = 0;
	len = 0;
	while (data->env[len])
		len++;
	sort_data(data, len, step);
	i = 0;
	while (data->env[i])
	{
		printf("declare -x %s=\"%s\"\n", extract_var_name(data->env[i]),
			get_val_env_var(data->env, extract_var_name(data->env[i])));
		i++;
	}
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
