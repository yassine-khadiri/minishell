/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:49:51 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/07/18 00:22:39 by ykhadiri         ###   ########.fr       */
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

void	fill_struct(t_command *cmd)
{
	int			i;
	t_cmdline	*cmdline;

	while (cmd)
	{	
		cmd->cmd_array  = malloc(sizeof(char *) * (ft_lstsize(cmd) + 1));
		if (!cmd->cmd_array)
			exit(1); // remove later
		cmdline = cmd->cmdline;
		i = 0;
		while (cmdline)
		{
			cmd->cmd_array[i++] = cmdline->cmd;
			cmdline = cmdline->next;
		}
		cmd->cmd_array[i] = NULL;
		cmd = cmd->next;
	}
}

void	execution(t_data *data, t_command *cmd)
{
	// printf("HERE0\n");
	// printf("%d\n", ft_lstsize(data->cmd->cmdline));
	// data->arr_cmds = malloc(sizeof(char *) * ft_lstsize(data->cmd->cmdline));
	// if (!data->arr_cmds)
	// 	return (NULL);
	// printf("%p\n", cmd); //NULL why hh
	// printf("%p\n", cmd->cmdline);
	(void) data;
	fill_struct(cmd);
	while (cmd) {
		for (int i = 0; cmd->cmd_array[i]; i++)
			printf("%s ", cmd->cmd_array[i]);
		if (cmd->next)
			printf("| ");
		cmd = cmd->next;
	}
	// printf("HERE2\n");
	// printf("HERE1\n");
	// if (cmd_founded_y_n(data) == -1)
	// 	return ;
	// if (pipe_founded(data) && ft_pipe(data))
	// 	return ;
	// rdr_execution(data);
	// builtins_execution(data);
}
