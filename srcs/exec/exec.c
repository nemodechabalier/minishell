/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:44:52 by nde-chab          #+#    #+#             */
/*   Updated: 2024/09/23 17:11:41 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_exec(t_cmd *cmd, t_data *data)
{
	(void)data;
	if (cmd->skip == 2)
	{
		ft_putstr_fd(cmd->cmds[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		ft_free_data(&data);
		exit(EXIT_FAILURE);
	}
	else if (cmd->skip == 1)
	{
		ft_free_data(&data);
		exit(EXIT_FAILURE);
	}
	else if (execve(cmd->path_cmd, cmd->cmds, cmd->env) == -1)
	{
		perror(cmd->cmds[0]);
		ft_free_data(&data);
		exit(EXIT_FAILURE);
	}
	return(FAIL);
}

int	before_exec(t_cmd *cmd, t_data *data)
{
	cmd->pid = fork();
	if (cmd->pid == -1)
		return (FAIL);
	else if (cmd->pid == 0)
		ft_exec(cmd, data);
	return (SUCCESS);
}