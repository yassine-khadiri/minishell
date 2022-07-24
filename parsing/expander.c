/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouqssi <hbouqssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 01:11:05 by hbouqssi          #+#    #+#             */
/*   Updated: 2022/07/24 19:21:44 by hbouqssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*after_dollar_value(char *command1, int i)
{
	char	*after_dollar;
	int		j;
	int		start;

	j = 0;
	start = i;
	while (command1[i++] != '\0')
		j++;
	after_dollar = ft_substr(command1, start, j);
	return (after_dollar);
}

size_t	dollar_val(char **comd, char *name, char *old_comd, t_env *envl)
{
	char	*tmp;
	int		len;

	len = 0;
	while (envl != NULL)
	{
		if (ft_strcmp(name, envl->name) == 0)
		{
			len = ft_strlen(old_comd) + ft_strlen(envl->value);
			tmp = ft_strjoin(old_comd, envl->value);
			free(*(comd));
			*(comd) = tmp;
			break ;
		}
		else
		{
			len = 1;
			tmp = ft_strjoin(old_comd, "");
			free(*(comd));
			*(comd) = tmp;
		}
		envl = envl->next;
	}
	return (len);
}

void	ft_new_str(char *str, int index)
{
	while (str[index] != '\0')
	{
		str[index] = str[index + 1];
		index++;
	}
}

char	*get_dollar_name(char *command, int *j)
{
	char	*name;
	char	*ptr;
	char	*tmp;
	int		i;

	i = *j;
	name = ft_strdup("");
	while (command[i] != '\0' && (ft_isalnum(command[i]) == 1
			|| command[i] == '_'))
	{
		ptr = ft_substr(command, i, 1);
		tmp = ft_strjoin(name, ptr);
		name = tmp;
		i++;
	}
	*j = i;
	return (name);
}

char	*check_name_hdc(char *buffer, int *k)
{
	char	*name;
	int		i;

	i = *k;
	if (ft_isalnum(buffer[i + 1]) == 1 || buffer[i + 1] == '_')
		ft_new_str(buffer, i);
	if (ft_isdigit(buffer[i]) == 1)
	{
		name = ft_substr(buffer, i++, 1);
	}
	else
		name = get_dollar_name(buffer, &i);
	*k = i;
	return (name);
}
