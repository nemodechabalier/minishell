/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:34:36 by nde-chab          #+#    #+#             */
/*   Updated: 2024/09/25 16:18:20 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		strs[i] = NULL;
		i++;
	}
	free(strs);
	strs = NULL;
}

void	free_after_exec(t_data *data)
{
	//close_exec(data->exec);
	if (data->exec)
		ft_free_exec(&data->exec);
	data->exec = NULL;
	if (data->parsing->tokens)
		ft_free_list(&data->parsing->tokens);
	data->parsing->tokens = NULL;
	if (data->parsing->input)
		free(data->parsing->input);
	data->parsing->input = NULL;
}
