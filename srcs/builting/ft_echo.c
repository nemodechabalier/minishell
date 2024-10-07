/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:27:19 by clmanouk          #+#    #+#             */
/*   Updated: 2024/10/07 17:22:13 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_echo(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '-' && str[i + 1] == 'n')
			return (ft_echo_n(str));
		i++;
	}
	ft_putendl_fd(str, 1);
}

void	ft_echo_n(char *str)
{
	ft_putstr_fd(str, 1);
}
