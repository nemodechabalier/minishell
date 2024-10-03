/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:01:30 by nde-chab          #+#    #+#             */
/*   Updated: 2024/10/03 13:14:56 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builting(t_cmd *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strncmp("cd", cmd->cmd, 100))
		return (1);
	if (!ft_strncmp("echo", cmd->cmd, 100))
		return (1);
	if (!ft_strncmp("env", cmd->cmd, 100))
		return (1);
	if (!ft_strncmp("exit", cmd->cmd, 100))
		return (1);
	if (!ft_strncmp("export", cmd->cmd, 100))
		return (1);
	if (!ft_strncmp("pwd", cmd->cmd, 100))
		return (1);
	if (!ft_strncmp("unset", cmd->cmd, 100))
		return (1);
	return (0);
}

int	ft_exec_builting(t_cmd *cmd, t_data *data)
{
	if (!ft_strncmp("cd", cmd->cmd, 100))
		return (ft_cd(cmd->cmds[1]), 1);
	if (!ft_strncmp("echo", cmd->cmd, 100))
		return (printf("echo"), 1);
	if (!ft_strncmp("env", cmd->cmd, 100))
		return (ft_env(data), 1);
	if (!ft_strncmp("exit", cmd->cmd, 100))
		return (ft_exit(), 1);
	if (!ft_strncmp("export", cmd->cmd, 100))
		return (printf("export"), 1);
	if (!ft_strncmp("pwd", cmd->cmd, 100))
		ft_pwd();
	if (!ft_strncmp("unset", cmd->cmd, 100))
		return (printf("unset"), 1);
	return (0);
}