/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:07:27 by nde-chab          #+#    #+#             */
/*   Updated: 2024/10/07 17:37:52 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ft_realloc(char **strs, int *size)
{
	char	**new;
	int		i;

	i = 0;
	*size = *size * 2;
	new = malloc((*size) * sizeof(char *));
	if (!new)
		return (NULL);
	while (new[i])
	{
		new[i] = strs[i];
		i++;
	}
	new[i] = NULL;
	free(strs);
	return (new);
}
