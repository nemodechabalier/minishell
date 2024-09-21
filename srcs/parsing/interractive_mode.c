/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interractive_mode.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmanouk <clmanouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:04:35 by clmanouk          #+#    #+#             */
/*   Updated: 2024/09/19 17:42:22 by clmanouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_sig(int signum)
{
	if (signum == SIGINT)
		ft_printf("Minishell beta 1.0$ ");
		
	else if (signum == SIGQUIT)
		ft_printf("Minishell beta 1.0$ ");
}

void	set_signal_action(void)
{
	struct sigaction act;
	ft_bzero(&act, sizeof(act));
	act.sa_handler = &handle_sig;
	sigation(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}