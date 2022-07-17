/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:49:51 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/07/17 19:22:13 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_get_spllited_string(char *str)
{
	char	**get_spllited_string;

	// get_spllited_string = malloc(sizeof(char *) * ft_strlen(str));
	// if(!get_spllited_string)
	// 	return (NULL);
	get_spllited_string = ft_split(str, ' ');
	return (get_spllited_string);
}

void	edit_pwd(char **env)
{
	char	*pwd;
	char	*old_pwd;

	pwd = get_val_env_var(env, "PWD");
	old_pwd = get_val_env_var(env, "OLDPWD");
}

char	**fill_struct(t_cmdline *cmds)
{
	printf("HERE1\n");
	int		i;
	char	**arr_cmds;

	i = 0;
	arr_cmds = malloc((sizeof(char *) + 1) * ft_lstsize(cmds));
	if (!arr_cmds)
		return (NULL);
	while (cmds)
	{
		arr_cmds[i] = cmds->cmd;
		cmds = cmds->next;
	}
	arr_cmds[i] = NULL;
	// while (*arr_cmds)
	// 	printf("%s\n", *arr_cmds++);
	return (arr_cmds);
}

void	execution(t_data *data)
{
	// data->spllited_cmd_buf = ft_get_spllited_string(data->command_buf);
	printf("HERE0\n");
	// printf("%d\n", ft_lstsize(data->cmd->cmdline));
	// data->arr_cmds = malloc(sizeof(char *) * ft_lstsize(data->cmd->cmdline));
	// if (!data->arr_cmds)
	// 	return (NULL);
	data->arr_cmds = fill_struct(data->cmd->cmdline);
	printf("HERE2\n");
	// while (*data->arr_cmds)
	// 	printf("%s\n", *data->arr_cmds++);
	if (cmd_founded_y_n(data) == -1)
		return ;
	if (pipe_founded(data) && ft_pipe(data))
		return ;
	rdr_execution(data);
	builtins_execution(data);
}
