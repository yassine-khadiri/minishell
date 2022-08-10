/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 19:22:28 by hbouqssi          #+#    #+#             */
/*   Updated: 2022/08/10 01:39:41 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_readline_herdoc(char **env, char *cmd)
{
	char	*tmp;
	char	*res;
	int		i;
	int		j;
	int		dollar_counter;

	i = 0;
	tmp = malloc(sizeof(char) * 1000);
	add(&g_tools.garbage, tmp);
	res = malloc(sizeof(char) * 1000);
	add(&g_tools.garbage, res);
	while (cmd[i])
	{
		j = 0;
		dollar_counter = 0;
		if (cmd[i] != '$')
		{
			while (cmd[i] && cmd[i] != '$')
				tmp[j++] = cmd[i++];
			tmp[j] = '\0';
			res = ft_strjoin(res, tmp);
			if (!cmd[i + 1])
			{
				res[ft_strlen(res)] = '\0';
				return (res);
			}
		}
		j = 0;
		while (cmd[i] && cmd[i] == '$')
		{
			dollar_counter++;
			tmp[j++] = cmd[i++];
		}
		while (cmd[i] && cmd[i] != '$')
		{
			if (!ft_isalnum(cmd[i]))
				break ;
			tmp[j++] = cmd[i++];
		}
		tmp[j] = '\0';
		if (dollar_counter > 1 || dollar_counter == 0 || (dollar_counter == 1
				&& !tmp[dollar_counter]))
			res = ft_strjoin(res, tmp);
		else
			res = ft_strjoin(res, check_res(tmp, env));
	}
	res[ft_strlen(res)] = '\0';
	return (res);
}

char	*treat_heredocs(t_data *data, char *delimeter)
{
	char	*line;

	data->buffer_herdoc = ft_strdup("");
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
