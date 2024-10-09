/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_case.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:37:17 by nde-chab          #+#    #+#             */
/*   Updated: 2024/10/08 15:28:23 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*take_rest(char *input, int position)
{
	int	i;

	i = position + 1;
	if (input[i] == '?')
		return (ft_strdup(input + i + 1));
	while (input[i - 1])
	{
		if (!isalnum(input[i]) && input[i] != '_')
			return (ft_strdup(input + i));
		i++;
	}
	return (NULL);
}
