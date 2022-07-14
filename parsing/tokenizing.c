/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 10:18:25 by hbouqssi          #+#    #+#             */
/*   Updated: 2022/07/14 16:20:04 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*ft_tokenizer(t_token **tokens, char *str)
{
	int	i;
	int	temp;

	i = 0;
	temp = 0;
	*tokens = initialize_list();
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (str[i] == '|')
			i += is_pipe(tokens, &str[i]);
		// else if (str[i] == ' ')
		// 	i += is_space(tokens, &str[i]);
		else if (str[i] == '<')
			i += is_redin(tokens, &str[i]);
		else if (str[i] == '>')
			i += is_redout(tokens, &str[i]);
		// else if (str[i] == '$')
		//      i += dollar(tokens, &str[i]);
		else if (str[i] == ';')
			i += semicolon(tokens, &str[i]);
		else if (str[i] == 34)
		{
			temp = db_quote(tokens, &str[i]);
			if (temp == -1)
			{
				printf("minishell: syntax error, Missing Double Quote\n");
				return (0);
			}
			i += temp;
		}
		else if (str[i] == 39)
		{
			temp = quote(tokens, &str[i]);
			if (temp == -1)
			{
				printf("minishell: syntax error, Missing Single Quote\n");
				return (0);
			}
			i += temp;
		}
		else if (not_word(str[i], " |\"<'>;"))
			i += word(tokens, &str[i]);
	}
	add_back(tokens, create_token(N_line, ft_strdup("NEWLINE")));
	return (*tokens);
}
