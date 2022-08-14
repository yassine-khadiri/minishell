/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 18:57:10 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/08/14 20:57:25 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_globals	g_tools = {0, 0};

void	setup_term(void)
{
	struct termios	t;

	tcgetattr(0, &t);
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &t);
}

void	data_initializer(t_data *data, char **env)
{
	data->g_std._stdin = dup(STDIN_FILENO);
	data->g_std._stdout = dup(STDOUT_FILENO);
	data->g_std._redin = dup(STDIN_FILENO);
	data->g_std._redout = dup(STDOUT_FILENO);
	if (!env[0])
	{
		data->env = malloc(sizeof(char *) * 2);
		add(&g_tools.garbage, data->env);
		data->env[0] = "PATH=";
		data->env[1] = NULL;
	}
	else
		data->env = env;
	g_tools.g_dollar_question = 0;
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	add(&g_tools.garbage, data);
	if (!data)
		return (0);
	data_initializer(data, env);
	(void)argv;
	if (argc > 1)
	{
		printf(RED "The Program Works Without Args\n");
		exit(1);
	}
	setup_term();
	minishel_start(data);
	free_all(g_tools.garbage);
	return (0);
}
