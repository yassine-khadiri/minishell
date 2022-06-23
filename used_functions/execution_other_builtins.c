/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_other_builtins.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 16:59:05 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/06/23 17:06:12 by ykhadiri         ###   ########.fr       */
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

void	execution_other_builtins(t_data *data)
{
	char	*path;
	int		pid;
	int		i;

	i = 0;
	while (data->splitted_path[i])
	{
		path = ft_strjoin(data->splitted_path[i], "/");
		path = ft_strjoin(path, data->spllited_cmd_buf[0]);
		if (!access(path, X_OK))
		{
			pid = fork(); // don't forget protection
			if (pid == 0)
				execve(path, data->spllited_cmd_buf, data->env);
			else
				waitpid(pid, NULL, 0);
		}
		i++;
	}
}
