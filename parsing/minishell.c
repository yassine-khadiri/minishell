
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouqssi <hbouqssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 10:22:37 by hbouqssi          #+#    #+#             */
/*   Updated: 2022/06/20 15:27:06 by hbouqssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_data *data;
	t_token *tokens;
	t_env *lenv = NULL;
	lenv = create_env_list(lenv, env);

	(void)tokens;
	data = (t_data *)malloc(sizeof(t_data));
	if (argc > 1)
	{
		printf(RED "the prog works without args\n");
		exit(1);
	}
	while (1)
	{
		data->command = readline(BLU "minishell$ " WHT);
		if (!data->command)
			return (-1);
		add_history(data->command);
		data->token_res = ft_tokenizer(&tokens, data->command);
		data->syntax_res = syntax_errors(data->token_res);
		if ((data->syntax_res) != 1)
		{
			ft_parse(tokens, lenv);
		}
	}
	return (0);
}