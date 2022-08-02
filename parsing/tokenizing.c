/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouqssi <hbouqssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 10:18:25 by hbouqssi          #+#    #+#             */
/*   Updated: 2022/08/02 01:49:46 by hbouqssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


t_token *ft_tokenizer(t_token **tokens, char *str)
{
	int i;
    
	i = 0;
    int temp = 0;
   
    *tokens = initialize_list();
	while (str[i])
	{
		if (str[i] == '|')
            i += is_pipe(tokens, &str[i]);
		else if (str[i] == ' ')
			i += is_space(tokens, &str[i]);
		else if (str[i] == '<')
            i += is_redin(tokens, &str[i]);
		else if (str[i] == '>')
             i += is_redout(tokens, &str[i]);
		else if (str[i] == ';')
             i += semicolon(tokens, &str[i]);
        else if (str[i] == 34)
        {
           temp = db_quote(tokens, &str[i]);
           if(temp == -1)
           {
                printf ("minishell: syntax error, Missing Double Quote\n");
                return (0);
           }
           i += temp;
                
        }
        else if (str[i] == 39)
            {
                temp = quote(tokens, &str[i]);
                if (temp == -1)
                {
                    printf ("minishell: syntax error, Missing Single Quote\n");
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

int c_q_word(t_token *token)
{
    t_token *tmp;
    int     len;

    tmp = token;
    len = 0;
    while (tmp && tmp->type == DBQUOTE)
    {
        len++;
        tmp = tmp->next;
    }
    return (len);
}

char    **final_tokens(t_token **token)
{
    t_token *tokens;
    int     i;
    char *tmp;
    tokens = *token;
    i = 0;

    t_token *new_tokens = NULL;
    while (tokens)
    {
        if (tokens->type == DBQUOTE || tokens->type == WORD)
        {
            tmp = malloc(sizeof(char) * c_q_word(tokens));
            if (!tmp)
                return (0);
            while (tokens && (tokens->type == DBQUOTE || tokens->type == WORD))
            {
                tmp = ft_strjoin(tmp, tokens->value);
                tokens = tokens->next;
            }
            // free(tmp);
            add_back(&new_tokens, create_token(WORD, tmp));
        }
        if (tokens->type != WSPACE)
            add_back(&new_tokens, create_token(tokens->type, tokens->value));
        if (tokens)
            tokens = tokens->next;
    } 
    // free tokens // *token
    *token = new_tokens;
    return (NULL);
}