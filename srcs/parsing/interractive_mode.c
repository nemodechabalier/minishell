/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interractive_mode.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:04:35 by clmanouk          #+#    #+#             */
/*   Updated: 2024/10/09 16:35:27 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	handle_sig(int signum)
//{
//	if (signum == SIGINT)
//	{
//		ft_printf("\n");
//		rl_on_new_line();
//		rl_replace_line("", 0);
//		rl_redisplay();
//	}
//}

void	set_signal_action(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = &handle_sig;
	act.sa_flags = SA_RESTART;
	sigaction(SIGINT, &act, NULL);
	signal(SIGQUIT, SIG_IGN);
}

// void	close_heredoc(t_redirection *red)
//{
//	t_redirection	*current;

//	current = red;
//	while (current != NULL)
//	{
//		if (current->file_fd != -1)
//		{
//			close(current->file_fd);
//			unlink(current->file);
//		}
//		current = current->next;
//	}
//}

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
			ft_printf("\n");
			if (g_verif == 2)
				rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
	else if (signum == SIGQUIT)
	{
		printf("Quit (core dumped)\n");
		close(STDIN_FILENO);
	}
}
void	signal_blocking(t_cmd *cmd)
{
	char	buffer[1024];
	int		n_bytes;

	signal(SIGQUIT, handle_sig);
	while ((n_bytes = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0)
	{
		if (n_bytes <= 0)
		{
			break ;
		}
		write(STDOUT_FILENO, buffer, n_bytes);
	}
	kill(cmd->pid, 0);
	signal(SIGQUIT, SIG_IGN);
}

// void	set_signal_action(void)
//{
//	struct sigaction act;

//	ft_bzero(&act, sizeof(act));
//	act.sa_handler = &handle_sig;
//	act.sa_flags = SA_RESTART;
//	sigaction(SIGINT, &act, NULL);
//	signal(SIGQUIT, SIG_IGN);
//}
