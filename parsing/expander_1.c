/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouqssi <hbouqssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 19:22:28 by hbouqssi          #+#    #+#             */
/*   Updated: 2022/07/25 21:58:55 by hbouqssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	}
	buffer = expand_herdocs(buffer, lenv);
	return (buffer);
}
