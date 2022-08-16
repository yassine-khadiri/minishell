/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 23:50:41 by hbouqssi          #+#    #+#             */
/*   Updated: 2022/08/16 03:51:06 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// char	*crd_res_helper(char *cmd, char **env, char *res, char *var_name)
// {
// 	char	*tmp;
// 	int		j;

// 	tmp = malloc(sizeof(tmp) * 1000);
// 	if (!tmp)
// 		return (NULL);
// 	j = 0;
// 	res = ft_strjoin(res, check_res(var_name, env));
// 	while (cmd[i] && cmd[i] != '$' && !ft_isalnum(cmd[i])
// 		&& check_res(var_name, env))
// 		var_name[j++] = cmd[i++];
// 	var_name[j] = '\0';
// 	res = ft_strjoin(res, var_name);
// }

char	*crd_res(char *cmd, char *var_name, char *res, char **env)
{
	int	dollar_counter;
	int	i;
	int	j;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		dollar_counter = 0;
		while (cmd[i] && cmd[i] == '$')
		{
			dollar_counter++;
			var_name[j++] = cmd[i++];
		}
		while (cmd[i] && ft_isalnum(cmd[i]))
			var_name[j++] = cmd[i++];
		var_name[j] = '\0';
		if (dollar_counter > 1 || dollar_counter == 0 || (dollar_counter == 1
				&& !var_name[dollar_counter]))
			res = ft_strjoin(res, var_name);
		else
		{
			res = ft_strjoin(res, check_res(var_name, env));
		}
		j = 0;
		while (cmd[i] && cmd[i] != '$' && !ft_isalnum(cmd[i])
			&& check_res(var_name, env))
			var_name[j++] = cmd[i++];
		var_name[j] = '\0';
		res = ft_strjoin(res, var_name);
	}
	return (res);
}