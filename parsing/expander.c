/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                       	:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 19:22:28 by hbouqssi          #+#    #+#             */
/*   Updated: 2022/08/10 01:39:41 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*check_remove_dollars(char **env, char *cmd)
{
	char	*var_name;
	char	*res;

	res = malloc(sizeof(char) * ft_strlen(cmd));
	var_name = malloc(sizeof(char) * 1000);
	if (!var_name || !res)
		return (0);
	add(&g_tools.garbage, var_name);
	add(&g_tools.garbage, res);
	res = crd_res(cmd, var_name, res, env);
	res[ft_strlen(res)] = '\0';
	return (res);
}

char	*expand_readline_herdoc(t_data *data, char *cmd)
{
	char	*tmp;
	char	*res;

	tmp = malloc(sizeof(char) * 1000);
	res = malloc(sizeof(char) * 1000);
	if (!tmp || !res)
		return (NULL);
	add(&g_tools.garbage, tmp);
	add(&g_tools.garbage, res);
	res = expand_readline_herdoc_helper(cmd, tmp, res, data);
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
		if (!ft_strcmp(line, delimeter))
			break ;
		line = ft_strjoin(expand_readline_herdoc(data, line), "\n");
		// line = ft_strjoin(line, "\n");
		data->buffer_herdoc = ft_strjoin(data->buffer_herdoc, line);
	}
	// puts(data->buffer_herdoc);
	return (delimeter);
}
