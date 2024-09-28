/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_case.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmanouk <clmanouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:37:17 by nde-chab          #+#    #+#             */
/*   Updated: 2024/09/26 16:22:09 by clmanouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	backslash_input(t_parsing *parsing)
{
	int i;
	
	i = 0;
	while (parsing->input[i])
	{
		if (parsing->input[i] == 47)
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}