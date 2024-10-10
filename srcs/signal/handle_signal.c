/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmanouk <clmanouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:30:02 by clmanouk          #+#    #+#             */
/*   Updated: 2024/10/10 15:30:04 by clmanouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_signal_action(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = &handle_sig;
	act.sa_flags = SA_RESTART;
	sigaction(SIGINT, &act, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_sig(int signum)
{
	if (signum == SIGINT)
	{
		if (g_verif == 1)
		{
			close(STDIN_FILENO);
			g_verif = 5;
		}
		else
		{
			count_line(1);
			ft_printf("\n");
			if (g_verif == 2 || g_verif == 5)
				rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			g_verif = 5;
		}
	}
	else if (signum == SIGQUIT)
	{
		printf("Quit (core dumped)\n");
		close(STDIN_FILENO);
	}
}
