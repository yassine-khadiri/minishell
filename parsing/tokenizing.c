/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouqssi <hbouqssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 10:18:25 by hbouqssi          #+#    #+#             */
/*   Updated: 2022/08/06 18:33:41 by hbouqssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*check_remove_dollars(char **env, char *cmd)
{
	char	*var_name;
	char 	*cp_var_name;
	char	*res;
	char	*cp_res;
	int		i;
	int		j;
	int		dollar_counter;

	i = 0;
	var_name = malloc(sizeof(char) * 1000);
	res = malloc(sizeof(char) * ft_strlen(cmd));
	if (!var_name || !res)
		return (0);
	cp_res = res;
	cp_var_name = var_name;
	while (cmd[i])
	{
		j = 0;
		dollar_counter = 0;
		while (cmd[i] && cmd[i] == '$')
		{
			dollar_counter++;
			cp_var_name[j++] = cmd[i++];
		}
		while (cmd[i] && cmd[i] != '$')
			cp_var_name[j++] = cmd[i++];
		cp_var_name[j] = '\0';
		if (dollar_counter > 1 || dollar_counter == 0 || (dollar_counter == 1
				&& !cp_var_name[dollar_counter]))
			cp_res = ft_strjoin(cp_res, cp_var_name);
		else
			cp_res = ft_strjoin(cp_res, check_res(cp_var_name, env));
	}
	cp_res[ft_strlen(cp_res)] = '\0';
	free(var_name);
	free(res);
	return (cp_res);
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

int	c_q_word(t_token *token)
{
	t_token	*tmp;
	int		len;

	tmp = token;
	len = 0;
	while (tmp && tmp->type == DBQUOTE)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

char	**final_tokens(t_token **token, char **env)
{
	t_token	*tokens;
	t_token *new_tokens;
	char	*tmp, *cp_tmp;
	int		i;

	tokens = *token;
	new_tokens = NULL;
	i = 0;
	while (tokens)
	{
		if (tokens->type == DBQUOTE || tokens->type == WORD
			|| tokens->type == QUOTE)
		{
			tmp = malloc(sizeof(char) * c_q_word(tokens));
			if (!tmp)
				return (0);
			cp_tmp = tmp;
			while (tokens && (tokens->type == DBQUOTE || tokens->type == WORD
					|| tokens->type == QUOTE))
			{
				if (tokens->type == WORD)
				{
					if (!ft_strcmp(tokens->value, "$?"))
					{
						printf("%d", g_dollar_question);
						g_dollar_question = 0;
					}
					if (!ft_strcmp(tokens->value, "$")
						&& (tokens->next->type == DBQUOTE
							|| tokens->next->type == QUOTE))
						tokens->value = ft_strtrim(tokens->value, "$");
					else
						tokens->value = check_remove_dollars(env,
								tokens->value);
				}
				else if (tokens->type == DBQUOTE)
					tokens->value = check_remove_dollars(env, tokens->value);
				cp_tmp = ft_strjoin(cp_tmp, tokens->value);
				tokens = tokens->next;
			}
			free(tmp);
			add_back(&new_tokens, create_token(WORD, cp_tmp));
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
