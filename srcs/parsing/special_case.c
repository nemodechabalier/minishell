/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_case.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmanouk <clmanouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:37:17 by nde-chab          #+#    #+#             */
/*   Updated: 2024/09/28 17:44:14 by clmanouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	special_char_input(t_parsing *parsing)
{
	int i;

	i = 0;
	while (parsing->input[i])
	{
		if (parsing->input[i] == 47 || parsing->input[i] == 92
			|| parsing->input[i] == '&')
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}