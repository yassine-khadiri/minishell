/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 10:18:25 by hbouqssi          #+#    #+#             */
/*   Updated: 2022/08/10 01:38:44 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*check_remove_dollars(char **env, char *cmd)
{
	char	*var_name;
	char	*res;
	char	*tmp;
	int		i;
	int		j;
	int		dollar_counter;

	i = 0;
	var_name = malloc(sizeof(char) * 1000);
	add(&g_tools.garbage, var_name);
	res = malloc(sizeof(char) * ft_strlen(cmd));
	add(&g_tools.garbage, res);
	if (!var_name || !res)
		return (0);
	while (cmd[i])
	{
		j = 0;
		dollar_counter = 0;
		while (cmd[i] && cmd[i] == '$')
		{
			dollar_counter++;
			var_name[j++] = cmd[i++];
		}
		while (cmd[i] && cmd[i] != '$')
			var_name[j++] = cmd[i++];
		var_name[j] = '\0';
		tmp = res;
		if (dollar_counter > 1 || dollar_counter == 0 || (dollar_counter == 1
				&& !var_name[dollar_counter]))
			res = ft_strjoin(tmp, var_name);
		else
			res = ft_strjoin(tmp, check_res(var_name, env));
	}
	res[ft_strlen(res)] = '\0';
	return (res);
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
	add_back(tokens, create_token(N_line, "NEWLINE"));
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
	t_token	*new_tokens;
	int		i;
	char	*tmp;

	tokens = *token;
	new_tokens = NULL;
	i = 0;
	while (tokens)
	{
		if (tokens->type == DBQUOTE || tokens->type == WORD
			|| tokens->type == QUOTE)
		{
			tmp = malloc(sizeof(char) * c_q_word(tokens));
			add(&g_tools.garbage, tmp);
			if (!tmp)
				return (0);
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
				tmp = ft_strjoin(tmp, tokens->value);
				tokens = tokens->next;
			}
			add_back(&new_tokens, create_token(WORD, tmp));
		}
		if (tokens->type != WSPACE)
			add_back(&new_tokens, create_token(tokens->type, tokens->value));
		if (tokens)
			tokens = tokens->next;
	}
	*token = new_tokens;
	return (NULL);
}
