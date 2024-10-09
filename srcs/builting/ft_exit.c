/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:29:24 by clmanouk          #+#    #+#             */
/*   Updated: 2024/10/08 15:37:46 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_is_sup_long(const char *str)
{
	int				i;
	unsigned long	sign;
	unsigned long	result;

	result = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (ft_isdigit(str[i]) == 1)
	{
		result = result * 10 + (str[i++] - '0');
		if (result > __LONG_MAX__)
			return (1);
	}
	return (0);
}

static long	ft_atol(const char *str)
{
	long	i;
	long	sign;
	long	result;

	result = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (ft_isdigit(str[i]) == 1)
		result = result * 10 + (str[i++] - '0');
	return (result * sign);
}

static int	correct_cmd(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '+' || str[0] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

void	ft_exit(t_cmd *cmd)
{
	long	value;

	if (!cmd->cmds[1])
		exit(0);
	if (correct_cmd(cmd->cmds[1]) || ft_is_sup_long(cmd->cmds[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd->cmds[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		exit(2);
	}
	if (cmd->cmds[1] && cmd->cmds[2])
		return (ft_putendl_fd("minishell: exit: too many arguments", 2),
			exit(2));
	value = ft_atol(cmd->cmds[1]);
	ft_putendl_fd("exit", 2);
	exit(value % 256);
}
