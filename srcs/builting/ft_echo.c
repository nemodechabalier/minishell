/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:27:19 by clmanouk          #+#    #+#             */
/*   Updated: 2024/10/08 16:08:26 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_echo_n(t_cmd *cmd)
{
	int	i;

	i = 2;
	while (cmd->cmds[i])
	{
		ft_putstr_fd(cmd->cmds[i], 1);
		i++;
		if (cmd->cmds[i])
			write(1, " ", 1);
	}
}

void	ft_echo(t_cmd *cmd)
{
	int	i;

	i = 1;
	if (!cmd->cmds[1])
		return (ft_putendl_fd("", 1));
	if (!ft_strncmp(cmd->cmds[1], "-n", 2))
		ft_echo_n(cmd);
	else
	{
		while (cmd->cmds[i])
		{
			ft_putstr_fd(cmd->cmds[i], 1);
			i++;
			if (cmd->cmds[i])
				write(1, " ", 1);
		}
		write(1, "\n", 1);
	}
}
