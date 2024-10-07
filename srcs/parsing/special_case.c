/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_case.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:37:17 by nde-chab          #+#    #+#             */
/*   Updated: 2024/10/07 17:22:19 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	special_char_input(t_parsing *parsing)
{
	int	i;

	i = 0;
	while (parsing->input[i])
	{
		if (parsing->input[i] == 92 || parsing->input[i] == '&')
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}
