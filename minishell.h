/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 18:57:48 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/06/24 19:47:36 by ykhadiri         ###   ########.fr       */
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
# include <stdlib.h>
# include <stdbool.h>
# include <signal.h>
# include <fcntl.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_global
{
	int	_stdin;
	int	_stdout;
}	t_global;

typedef struct s_data
{
	char		*command_buf;
	char		**spllited_cmd_buf;
	char		getpath[1000];
	char		**env;
	char		**splitted_path;
	const char	*fd_name;
	t_global	g_std;
}	t_data;

// typedef struct s_pipe
// {
// 	int fd[2];
// 	pid_t	first_pid;
// 	pid_t	second_pid;
// 	int		infile;
// 	int		outfile;
// 	int		fd[2];
// 	char	*path;
// 	char	**command_args;
// 	char	**command_paths;
// 	char	*command;
// }	t_pipe;

// used_functions :)
void	minishel_start(t_data *data);
int		ft_strlen(const char *s);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		is_String(char *string);
char	*ft_strtrim(char const *s1, char const *set);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);
char	*ft_strjoin_space(char *s1, char *s2);
char	*ft_strjoin(char *s1, char *s2);
void	execution(t_data *data);
char	**ft_split(const char *s, char c);
void	execution_other_builtins(t_data *data);
void	execution_pipe_cmd(char *av, char **env);
char	**ft_get_spllited_path_env(t_data *data);
char	*get_val_env_var(char **env, char *env_variable);
int		ft_pipe(char *str, char **env);
int		cmd_founded_y_n(t_data *data);
int		pipe_founded(t_data *data);
void	exec(t_data *data);

// redirections
// -- output redirection
void	output_rdr_std_appnd(t_data *data, int flag);
char	*verify_rdr(t_data *data);
int		rdr_execution(t_data *data);
char	**get_splitted_cmd(char **data);
const char	*get_file_name(t_data *data);

// -- output redirection
void	input_rdr_std_appnd(t_data *data);

// interactive_modes :)
void	ft_ctl_c(void);
void	ft_ctl_d(t_data *cmds);
void	ft_ctl_slash(void);

int		builtins_execution(t_data *data);

// pwd Command :)
int	ft_pwd(t_data *data);

// echo Command :)
int	ft_echo(t_data *data, int index);

// export Command :)
int		get_env_size(char **env);
int		ft_export(t_data *data, int index);

// unset Command :)
int		ft_unset(t_data *data, int index);

// env Command :)
int		ft_env(char **env);
#endif
