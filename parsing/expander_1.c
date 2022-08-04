/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouqssi <hbouqssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 19:22:28 by hbouqssi          #+#    #+#             */
/*   Updated: 2022/08/04 06:07:15 by hbouqssi         ###   ########.fr       */
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

char	*treat_heredocs(t_data *data, char *delimeter)
{
	char	*line;
	int		fd;
	t_redirection *red = NULL;
	data->buffer_herdoc =ft_strdup("");
	while (1)
	{
		line = readline(BLU "> " WHT);
		if (ft_strcmp(line, delimeter) == 0)
		{
			break ;
		}
		line = ft_strjoin(line, "\n");
		data->buffer_herdoc = ft_strjoin(data->buffer_herdoc, line);
	}
	// ! daba khas had lcontent li kayn f buffer_herdoc tlo7ha f dak lfile libghina ncreeyiwh temporarly ( /tmp/chi_9lwa)
	// !!!!!!!!!! ana jrrebt walakin mabghach itkriya liya lfile f /tmp/...
	
	return (delimeter); //!!     -----   returnit 'delimeter' li howa smiya ta3 lfile litikoun gddam hado "<<"
}
