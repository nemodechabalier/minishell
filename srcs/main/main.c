/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:47:25 by clmanouk          #+#    #+#             */
/*   Updated: 2024/09/18 16:10:01 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	(void)av;
	(void)ac;
	t_data *data;
	data = init_all(env);
	if (!data)
		return (-1);
	handle_input(data->parsing);
	ft_free_data(&data);
}