/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 01:11:05 by hbouqssi          #+#    #+#             */
/*   Updated: 2022/07/23 17:06:30 by ykhadiri         ###   ########.fr       */
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
			printf("NASA\n");
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
		// free(name);
		name = tmp;
		// free(ptr );
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
		printf(GRN "RANI HNA : %s\n" WHT, buffer);
	}
	else
		name = get_dollar_name(buffer, &i);
	*k = i;
	return (name);
}

char	*expand_herdocs(char *buffer, t_env *lenv)
{
	char	*before_dollar;
	char	*env_name;
	char	*after_dollar;
	int		i;
	size_t	len;

	i = 0;
	before_dollar = ft_strdup("");
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '$' && (ft_isalnum(buffer[i + 1]) == 1 || buffer[i
				+ 1] == '_'))
		{
			before_dollar = ft_substr(buffer, 0, i);
			env_name = check_name_hdc(buffer, &i);
			after_dollar = after_dollar_value(buffer, i);
			len = dollar_val(&buffer, env_name, before_dollar, lenv);
			buffer = ft_strjoin(buffer, after_dollar);
			i = len - 1;
		}
		i++;
	}
	return (buffer);
}

char	*treat_heredocs(char *delimeter, t_env *lenv)
{
	char	*line;
	char	*buffer;

	buffer = ft_strdup("");
	while (1)
	{
		line = readline(BLU ">" WHT);
		if (ft_strcmp(line, delimeter) == 0)
			break ;
		line = ft_strjoin(line, "\n");
		buffer = ft_strjoin(buffer, line);
		// free(line);
	}
	buffer = expand_herdocs(buffer, lenv);
	return (buffer);
}
