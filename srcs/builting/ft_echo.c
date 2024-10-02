/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmanouk <clmanouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:27:19 by clmanouk          #+#    #+#             */
/*   Updated: 2024/10/02 14:37:48 by clmanouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_echo(char *str)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] == '-' && str[i + 1] == 'n')
			return (ft_echo_n(str));
		i++;
	}
	printf("coucou\n");
	ft_putendl_fd(str, 1);
}

void	ft_echo_n(char *str)
{
	
	ft_putstr_fd(str, 1);
}