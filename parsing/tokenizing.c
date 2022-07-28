/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 10:18:25 by hbouqssi          #+#    #+#             */
/*   Updated: 2022/07/28 17:11:09 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sub_tokens(t_token **tokens, int *i, char *str)
{
	// while (str[*i] == ' ' || str[*i] == '\t')
	// 	i += 1;
	
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

// int	for_dbquotes(t_token **tokens, int *i, char *str, int *temp)
// {
// 	if (str[*i] == 34)
// 	{
// 		*temp = db_quote(tokens, &str[*i]);
// 		if (*temp == -1)
// 			return (70);
// 		*i += *temp;
// 		return (0);
// 	}
// 	return (0);
// }

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
		// if (for_dbquotes (tokens, &i, str, &temp) == 70)
		// 	return (printf("minishell: syntax error, Missing Db_Quotes\n"),
		// 		NULL);
		// else if (str[i] == 39)
		// {
		// 	temp = quote(tokens, &str[i]);
		// 	if (temp == -1)
		// 		return (printf("minishell: syntax error, Missing S_Quotes\n"),
		// 			NULL);
		// 	i += temp;
		// }
		if (not_word(str[i], " |<>;"))
			i += word(tokens, &str[i]);
	}
	add_back(tokens, create_token(N_line, ft_strdup("NEWLINE")));
	// while(tokens != NULL)
    //    {
    //       printf("type :    |%d|\n", (*tokens)->type);
    //       printf("Value :   |%s|\n", (*tokens)->value);
    //       printf("--------\n");
    //       (*tokens) = (*tokens)->next;
    //    }
	return (*tokens);
}
