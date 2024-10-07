/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:47:25 by clmanouk          #+#    #+#             */
/*   Updated: 2024/10/07 17:22:19 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
