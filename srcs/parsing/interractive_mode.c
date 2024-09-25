/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interractive_mode.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmanouk <clmanouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:04:35 by clmanouk          #+#    #+#             */
/*   Updated: 2024/09/25 11:31:45 by clmanouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_sig(int signum)
{
	if (signum == SIGINT) // CTRL-C
	{
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
void	set_signal_action(void)
{
	struct sigaction act;
	ft_bzero(&act, sizeof(act));
	act.sa_handler = &handle_sig;
	act.sa_flags = SA_RESTART;
	sigaction(SIGINT, &act, NULL);
	signal(SIGQUIT, SIG_IGN); // CTRL -\ ne fait rien
}