/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 18:57:10 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/07/14 16:33:34 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_term(void)
{
	struct termios	t;

	tcgetattr(0, &t);
	t.c_lflag &= ~ECHOCTL; // khssk t3raf kifax &=
	tcsetattr(0, TCSANOW, &t);
}

void	data_initializer(t_data *data, char **env)
{
	data->g_std._stdin = dup(0);
	data->g_std._stdout = dup(1);
	if (!env[0])
	{
		data->env = malloc(sizeof(char *) * 2);
		data->env[0] = "PATH=";
		data->env[1] = NULL;
	}
	else
		data->env = env;
	data->splitted_path = ft_get_spllited_path_env(data);
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;
	t_token	*tokens;
	t_env	*lenv;

	tokens = NULL;
	lenv = NULL;
	lenv = create_env_list(lenv, env);
	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	data_initializer(data, env);
	(void)argv;
	if (argc > 1)
	{
		printf(RED "the prog works without args\n");
		exit(1);
	}
	setup_term();
	minishel_start(data, tokens, lenv);
	return (0);
}
