/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_other_builtins.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 16:59:05 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/08/14 04:31:42 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_val_env_var(char **env, char *env_variable)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], env_variable, ft_strlen(env_variable)))
			return (env[i] + ft_strlen(env_variable) + 1);
		i++;
	}
	return (NULL);
}

char	**ft_get_spllited_path_env(t_data *data)
{
	data->splitted_path = ft_split(get_val_env_var(data->env, "PATH"), ':');
	return (data->splitted_path);
}

int	ex_other_built(char *path, t_command *cmd, t_data *data)
{
	if (!access(path, X_OK))
	{
		data->pid1 = fork();
		if (data->pid1 < 0)
			return (0);
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, handler);
		if (data->pid1 == 0)
		{
			signal(SIGINT, SIG_DFL);
			execve(path, cmd->cmd_array, data->env);
			exit(1);
		}
		waitpid(data->pid1, &data->status, 0);
		if (data->status == 2)
			printf("\n");
		signal(SIGINT, handler);
		g_tools.g_dollar_question = WEXITSTATUS(data->status);
		if (data->status == 3)
			g_tools.g_dollar_question = 131;
		return (1);
	}
	return (0);
}

int	execution_other_builtins(t_data *data, t_command *cmd)
{
	char	*path;
	char	*tmp;
	int		i;

	i = 0;
	if (!data->splitted_path)
		return (0);
	while (data->splitted_path[i])
	{
		path = ft_strjoin(data->splitted_path[i], "/");
		tmp = path;
		path = ft_strjoin(tmp, cmd->cmd_array[0]);
		if (ex_other_built(path, cmd, data))
			break ;
		i++;
	}
	return (1);
}
