/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:49:51 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/07/18 14:59:29 by ykhadiri         ###   ########.fr       */
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
		cmdline = cmd->cmdline;
		cmd->cmd_array  = malloc(sizeof(char *) * (ft_lstsize(cmdline) + 1));
		if (!cmd->cmd_array)
			exit(1); // remove later
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
	// (void) data;
	fill_struct(cmd);
	// int i;
	// t_command *tmp;
	// tmp = cmd;
	// while (tmp) {
	// 	for (i= 0; tmp->cmd_array[i]; i++)
	// 	{
			
	// 		printf("%s\n", tmp->cmd_array[i]);
	// 	}
	// 	printf("%s\n", tmp->cmd_array[i]);
	// 	if (tmp->next)
	// 		printf("| ");
	// 	tmp = tmp->next;
	// }
	if (cmd_founded_y_n(data, cmd) == -1)
		return ;
	// if (pipe_founded(data) && ft_pipe(data))
	// 	return ;
	// rdr_execution(data);
	builtins_execution(data, cmd);
}
