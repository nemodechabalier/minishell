/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_exec_builting.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmanouk <clmanouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:01:30 by nde-chab          #+#    #+#             */
/*   Updated: 2024/10/07 18:08:48 by clmanouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builting(t_cmd *cmd)
{
	if (!cmd || !cmd->cmd)
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
		return (ft_cd(cmd), 1);
	if (!ft_strncmp("echo", cmd->cmd, 100))
		return (printf("echo"), 1);
	if (!ft_strncmp("env", cmd->cmd, 100))
		return (ft_env(data), 1);
	if (!ft_strncmp("exit", cmd->cmd, 100))
		return (ft_exit(cmd), 1);
	if (!ft_strncmp("export", cmd->cmd, 100))
		return (ft_export(data, cmd), 1);
	if (!ft_strncmp("pwd", cmd->cmd, 100))
		ft_pwd();
	if (!ft_strncmp("unset", cmd->cmd, 100))
		ft_unset(cmd, data);
	return (0);
}
