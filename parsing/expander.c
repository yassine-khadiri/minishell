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

char	*checker_case_1(t_data *data, char *tmp, char *cmd, char *res)
{
	int	j;

	j = 0;
	if (cmd[data->g_index] != '$')
	{
		while (cmd[data->g_index] && cmd[data->g_index] != '$')
			tmp[j++] = cmd[data->g_index++];
		tmp[j] = '\0';
		res = ft_strjoin(res, tmp);
		if (!cmd[data->g_index + 1])
		{
			res[ft_strlen(res)] = '\0';
			return (res);
		}
	}
	return (NULL);
}

char	*checker_case_2(t_data *data, char *tmp, char *cmd)
{
	int	j;

	j = 0;
	while (cmd[data->g_index] && cmd[data->g_index] == '$')
	{
		data->dollar_counter++;
		tmp[j++] = cmd[data->g_index++];
	}
	while (cmd[data->g_index] && cmd[data->g_index] != '$')
	{
		if (!ft_isalnum(cmd[data->g_index]))
			break ;
		tmp[j++] = cmd[data->g_index++];
	}
	tmp[j] = '\0';
	puts(tmp);
	return (tmp);
}

char	*expand_readline_herdoc(t_data *data, char *cmd)
{
	char	*tmp;
	char	*res;

	tmp = malloc(sizeof(char) * 1000);
	res = malloc(sizeof(char) * 1000);
	data->g_index = 0;
	while (cmd[data->g_index])
	{
		data->dollar_counter = 0;
		res = checker_case_1(data, tmp, cmd, res);
		tmp = checker_case_2(data, tmp, cmd);
		if (data->dollar_counter > 1 || data->dollar_counter == 0
			|| (data->dollar_counter == 1
				&& !tmp[data->dollar_counter]))
					res = ft_strjoin(res, tmp);
		else
			res = ft_strjoin(res, check_res(tmp, data->env));
	}
	// res[ft_strlen(res)] = '\0';
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
		line = ft_strjoin(expand_readline_herdoc(data, line), "\n");
		data->buffer_herdoc = ft_strjoin(data->buffer_herdoc, line);
	}
	return (delimeter);
}
