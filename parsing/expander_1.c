/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouqssi <hbouqssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 19:22:28 by hbouqssi          #+#    #+#             */
/*   Updated: 2022/08/03 03:17:54 by hbouqssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// char	*expand_herdocs(char *buffer, t_env *lenv)
// {
// 	char	*before_dollar;
// 	char	*env_name;
// 	char	*after_dollar;
// 	int		i;
// 	size_t	len;

// 	i = 0;
// 	before_dollar = ft_strdup("");
// 	while (buffer[i] != '\0')
// 	{
// 		if (buffer[i] == '$' && (ft_isalnum(buffer[i + 1]) == 1 || buffer[i
// 					+ 1] == '_'))
// 		{
			
// 		}
// 		i++;
// 	}
// 	return (buffer);
// }

char	*treat_heredocs(char *delimeter)
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
	// buffer = expand_herdocs(buffer);
	return (buffer);
}
