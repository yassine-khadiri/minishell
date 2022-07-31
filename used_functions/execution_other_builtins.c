/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_other_builtins.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 16:59:05 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/07/31 16:13:19 by ykhadiri         ###   ########.fr       */
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

int	execution_other_builtins(t_data *data, t_command *cmd)
{
	char	*path;
	char	*tmp;
	int		pid;
	int		i;

	i = 0;
	while (data->splitted_path[i])
	{
		path = ft_strjoin(data->splitted_path[i], "/");
		tmp = path;
		path = ft_strjoin(tmp, cmd->cmd_array[0]);
		free(tmp);
		if (!access(path, X_OK))
		{
			pid = fork();
			if (pid < 0)
				return (free(path), 0);
			if (pid == 0)
			{
				execve(path, cmd->cmd_array, data->env);
				free(path);
				exit(1);
			}
			free(path);
			waitpid(pid, &data->status, 0);
			g_dollar_question = WEXITSTATUS(data->status); 
			break ;
		}
		free(path);
		i++;
	}
	return (1);
}
