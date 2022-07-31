/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouqssi <hbouqssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 19:22:28 by hbouqssi          #+#    #+#             */
/*   Updated: 2022/07/30 22:44:51 by hbouqssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// char	*expand_herdocs(char *buffer)
// {
// 	int i = 0;
// 	while (buffer[i] != '\0')
// 	{
// 		if (buffer[i] == '$' && (ft_isalnum(buffer[i + 1]) == 1 || buffer[i
// 					+ 1] == '_'))
// 		{
// 			// check_res();
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
	puts(buffer);
	// buffer = expand_herdocs(buffer, lenv);
	return (buffer);
}
