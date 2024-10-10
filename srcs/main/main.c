/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:47:25 by clmanouk          #+#    #+#             */
/*   Updated: 2024/10/10 16:31:33 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		g_verif = 0;

void	handle_input(t_parsing *parsing, t_data *data)
{
	char	*rest;

	rest = NULL;
	set_signal_action();
	while (1)
	{
		if (g_verif != 5)
			parsing->input = rest;
		dup_2_std(data);
		if (g_verif == 5)
			data->exit_status = 130;
		g_verif = 2;
		if (!parsing->input)
			parsing->input = readline("Minishell 1.0$ ");
		if (g_verif == 5)
			data->exit_status = 130;
		count_line(1);
		if (!parsing->input)
			break ;
		g_verif = 0;
		rest = take_end_of_l(parsing->input);
		if (*parsing->input)
			do_minishell(parsing, data);
		free_after_exec(data);
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	(void)av;
	(void)ac;
	data = init_data(env);
	if (!data)
		return (-1);
	data->parsing = init_parsing();
	handle_input(data->parsing, data);
	ft_free_data(&data);
	rl_clear_history();
}
