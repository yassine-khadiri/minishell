/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouqssi <hbouqssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 10:18:25 by hbouqssi          #+#    #+#             */
/*   Updated: 2022/07/28 17:57:31 by hbouqssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sub_tokens(t_token **tokens, int *i, char *str)
{
	
	if (str[*i] == '|')
		*i += is_pipe(tokens, &str[*i]);
	else if (str[*i] == '<')
		*i += is_redin(tokens, &str[*i]);
	else if (str[*i] == '>')
		*i += is_redout(tokens, &str[*i]);
	else if (str[*i] == ';')
		*i += semicolon(tokens, &str[*i]);
	else if (str[*i] == ' ')
		*i += is_space(tokens, &str[*i]);
}

t_token	*ft_tokenizer(t_token **tokens, char *str)
{
	int	i;
	int	temp;

	i = 0;
	temp = 0;
	*tokens = initialize_list();
	while (str[i])
	{
		sub_tokens (tokens, &i, str);
		if (not_word(str[i], " |<>;"))
			i += word(tokens, &str[i]);
	}
	add_back(tokens, create_token(N_line, ft_strdup("NEWLINE")));
	return (*tokens);
}
