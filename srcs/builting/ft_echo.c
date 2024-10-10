/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:27:19 by clmanouk          #+#    #+#             */
/*   Updated: 2024/10/10 13:04:50 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_flag_n(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	else
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_echo_n(t_cmd *cmd)
{
	int	i;

	i = 2;
	while (cmd->cmds[i] && is_flag_n(cmd->cmds[i]))
		i++;
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
	if (is_flag_n(cmd->cmds[1]))
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
