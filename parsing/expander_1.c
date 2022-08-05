/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 19:22:28 by hbouqssi          #+#    #+#             */
/*   Updated: 2022/08/05 19:16:02 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_readline_herdoc(char **env, char *cmd)
{
	char	*var_name;
	char	*res;
	int		i;
	int		j;
	int		dollar_counter;

	i = 0;
	var_name = malloc(sizeof(char) * 1000);
	res = malloc(sizeof(char) * ft_strlen(cmd));
	while (cmd[i])
	{
		j = 0;
		dollar_counter = 0;
		while (cmd[i] && cmd[i] == '$')
		{
			if (cmd[i + 1] == '"')
			{
				res = cmd;
				return(res);
			}
			dollar_counter++;
			var_name[j++] = cmd[i++];
		}
		while (cmd[i] && cmd[i] != '$')
			var_name[j++] = cmd[i++];
		var_name[j] = '\0';
		if (dollar_counter > 1 || dollar_counter == 0 || (dollar_counter == 1
				&& !var_name[dollar_counter]))
					res = ft_strjoin(res, var_name);
		else
			res = ft_strjoin(res, check_res(var_name, env));
	}
	res[ft_strlen(res)] = '\0';
	return (res);	
}

char	*treat_heredocs(t_data *data, char *delimeter)
{
	char	*line;

	data->buffer_herdoc =ft_strdup("");
	while (1)
	{
		line = readline(BLU "> " WHT);
		if (ft_strcmp(line, delimeter) == 0)
			break ;
		line = ft_strjoin(expand_readline_herdoc(data->env, line), "\n");
		data->buffer_herdoc = ft_strjoin(data->buffer_herdoc, line);
	}
	return (delimeter); 
}
