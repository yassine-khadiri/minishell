/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:50:49 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/07/14 16:20:09 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int exec_prog(t_data *data)
// {
//     int pid;
//     pid = fork();
//     if (pid == 0)
//         execve(path, data->spllited_cmd_buf, data->env);
//     return (0);
// }