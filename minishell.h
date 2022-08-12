/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouqssi <hbouqssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 18:57:48 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/08/12 01:57:14 by hbouqssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# define BLK "\e[0;30m"
# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"
# define MAG "\e[0;35m"
# define CYN "\e[0;36m"
# define WHT "\e[0;37m"

# include <unistd.h>
# include <stdio.h>
# include <termios.h>
# include <stdlib.h>
# include <stdbool.h>
# include <signal.h>
# include <fcntl.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_tokens
{
	NONE,
	WSPACE,
	PIPE,
	HERDOC,
	APPEND,
	REDIN,
	REDOUT,
	DBQUOTE,
	QUOTE,
	WORD,
	DOLLAR,
	N_line,
	SEMICOLON,
}							t_types;

typedef enum e_sep
{
	e_pipe,
	e_line,
}							t_sep;

typedef struct s_token
{
	int						type;
	char					*value;
	struct s_token			*next;
	struct s_token			*prev;
}							t_token;

typedef struct s_global
{
	int						_stdin;
	int						_stdout;
}							t_global;

typedef struct s_redirection
{
	int						type;
	char					*file;
	struct s_redirection	*next;
}							t_redirection;

typedef struct s_cmdline
{
	char					*cmd;
	struct s_cmdline		*next;
}							t_cmdline;

typedef struct s_command
{
	t_cmdline				*cmdline;
	t_redirection			*redirection;
	t_sep					separator;
	char					**cmd_array;
	struct s_command		*next;
}							t_command;

typedef struct s_env
{
	char					*name;
	char					*value;
	struct s_env			*next;
}							t_env;

typedef struct s_data
{
	char					*command_buf;
	char					getpath[1000];
	char					*old_pwd;
	char					*buffer_herdoc;
	char					**env;
	char					**splitted_path;
	char					mode;
	char					*tmp;
	int						syntax_res;
	char					*file_path;
	int						fd[2];
	int						pid1;
	int						pid2;
	int						*pids;
	int						**pipes;
	int						status;
	int						g_index;
	int						dollar_counter;
	int						fd_h;
	int						nb_cmds;
	t_token					*tokens;
	t_command				*cmd;
	t_env					*lenv;
	t_global				g_std;
}							t_data;

// Garbage Collector !!!

typedef struct s_node
{
	void					*pointer;
	struct s_node			*next;
}							t_node;

typedef struct s_globals
{
	int						g_dollar_question;
	t_node					*garbage;
}							t_globals;

extern t_globals			g_tools;

void						add(t_node **garbage, void *pointer);
void						free_all(t_node *garbage);

// End Garbage Collector !!

// used_functions :)
int							check_env_var(char *env_var);
void						show_err_msg(t_command *cmd);
t_command					*ft_parse(t_data *data, t_token *tokens);
int							ft_isdigit(int c);
int							ft_isalnum(int c);
t_env						*initial_env_node(char *name, char *value);
void						add_env_node(t_env *env_l, char *name, char *value);
t_env						*create_env_list(t_env *l_env, char **env);
int							is_space(t_token **tokens, char *str);
int							is_pipe(t_token **tokens, char *str);
int							is_redin(t_token **tokens, char *str);
int							is_redout(t_token **tokens, char *str);
int							not_word(char c, char *str);
int							db_quote(t_token **tokens, char *str);
int							quote(t_token **tokens, char *str);
int							word(t_token **tokens, char *str);
int							dollar(t_token **tokens, char *str);
int							semicolon(t_token **tokens, char *str);
t_token						*initialize_list(void);
char						*crd_res(char *cmd, char *var_name,
								char *res, char **env);
char						*expand_readline_herdoc_helper(char *cmd, char *tmp,
								char *res, t_data *data);
t_token						*create_token(int type, char *value);
int							none_error(t_token *tokens, t_token *head);
int							redir_error(t_token *tokens, t_token *head);
int							pipe_error(t_token *tokens, t_token *head);
t_redirection				*initalize_redirections(t_data *data,
								t_cmdline *cmd, int type, char *value);
void						push_redirections(t_redirection **head,
								t_redirection *new_redirection);
void						add_separator(t_command *cmd, t_token *tokens);
t_command					*initialize_command(t_cmdline *cmdline,
								t_redirection *redirections,
								t_token *tokens);
void						fill_command(t_command **head, t_command *command);
char						*after_dollar_value(char *command1, int i);
size_t						dollar_val(char **comd, char *name, char *old_comd,
								t_env *envl);
void						ft_new_str(char *str, int index);
char						*get_dollar_name(char *command, int *j);
char						*check_name_hdc(char *buffer, int *k);
char						*expand_herdocs(char *buffer, t_env *lenv);
char						*treat_heredocs(t_data *data, char *delimeter);
char						*ft_strndup(const char *s1, int size);
int							syntax_errors(t_token *tokens);
t_token						*new_line(char *n_type, char *value);
int							semicolon(t_token **tokens, char *str);
void						free_list(t_token *lst);
int							redir_error(t_token *tokens, t_token *head);
void						push_rdr(t_redirection **head,
								t_redirection *new_redirection);
int							ft_quotes(char *string);
int							tab_size(char **cmd_args);
t_token						*is_last(t_token *last);
void						add_back(t_token **lst, t_token *new);
t_token						*create_token(int type, char *value);
char						*check_remove_dollars(char **env, char *cmd);
t_token						*ft_tokenizer(t_token **tokens, char *str);
int							for_squotes(t_token **tokens, int *i,
								char *str, int *temp);
int							for_dbquotes(t_token **tokens, int *i,
								char *str, int *temp);
int							c_q_word(t_token *token);
void						sub_tokens(t_token **tokens, int *i, char *str);
char						*ft_substr(char const *s, unsigned int start,
								size_t len);
void						minishel_start(t_data *data);
int							ft_strlen(const char *s);
int							ft_isalpha(int c);
int							ft_isdigit(int c);
int							is_validated(char *var_name, char *env_var);
char						*ft_strtrim(char const *s1, char const *set);
int							ft_strcmp(char *s1, char *s2);
int							ft_strncmp(const char *s1, const char *s2,
								size_t n);
char						*ft_strdup(const char *s1);
char						*ft_strjoin_space(char *s1, char *s2);
char						*ft_strjoin(char *s1, char *s2);
void						execution(t_data *data, t_command *cmd);
char						**ft_split(const char *s, char c);
int							execution_other_builtins(t_data *data,
								t_command *cmd);
char						**ft_get_spllited_path_env(t_data *data);
char						*get_val_env_var(char **env, char *env_variable);
int							ft_pipe(t_data *data, t_command *cmd);
int							cmd_founded_y_n(t_data *data, t_command *cmd);
int							case_1(t_data *data, t_command *cmd, char *path);
int							case_2(t_data *data, t_command *cmd, char *path);
char						*extract_path(t_command *cmd);
int							pipe_founded(t_token *tokens);
char						*check_var(char *var_name, char **env);
void						print_mssj(char *str, char mode);
char						*ft_itoa(int n);
int							ft_lstsize(t_cmdline *lst);
char						*ft_strrchr(const char *s, int c);
int							ft_atoi(const char *str);
char						**final_tokens(t_data *data,
								t_token **token, char **env);
void						data_initializer(t_data *data, char **env);
void						handler(int signm);
char						*exec_herdoc(t_data *data, t_cmdline *cmd,
								t_redirection *redir);
int							error_mssj(t_data *data, t_command *cmd);
void						free_tokens(t_token *tokens);

// redirections
// -- output redirection
void						output_rdr_std_appnd(t_data *data, t_command *cmd,
								int flag);
char						*verify_rdr(t_data *data);
int							rdr_execution(t_data *data, t_command *cmd);

// -- output redirection
void						input_rdr_std_appnd(t_data *data, t_command *cmd,
								char *str);

// pipe Command :)
int							execution_pipe_cmd(t_data *data, t_command *cmd);
int							get_nb_cmds(t_command *cmd);
int							exec1(t_data *data, t_command *cmd, int in);

// interactive_modes :)
void						ft_ctl_c(void);
void						ft_ctl_d(t_data *cmds);
void						ft_ctl_slash(void);

int							builtins_execution(t_data *data, t_command *cmd);

// pwd Command :)
int							ft_pwd(t_data *data);

// echo Command :)
int							ft_echo(t_data *data, t_command *cmd, int index);
char						*check_res(char *var_name, char **env);

// cd Command :)
int							ft_cd(t_data *data, t_command *cmd, int index);
int							edit_pwd(t_data *data);

// export Command :)
int							get_env_size(char **env);
int							ft_export(t_data *data, t_command *cmd);
char						*extract_var_name(char *string);
char						*ignore_something(char *var_name);
int							check_equal_sign(char *env_var);
char						*update_append(char *env, char *var_name);
void						display_export(t_data *data);
int							check_dash_err(char *env_var);
int							update_val(t_data *data, char *var_name);

// unset Command :)
int							ft_unset(t_data *data, t_command *cmd, int index);

// env Command :)
int							ft_env(char **env);

// exit Command :)
int							ft_exit(t_command *cmd);
#endif
