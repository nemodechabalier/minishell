/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_case.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:37:17 by nde-chab          #+#    #+#             */
/*   Updated: 2024/10/10 17:43:35 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	space(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

char	*take_end_of_l(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\n' && handle_quote(str, 0, i) == -1)
		{
			str[i] = '\0';
			return (ft_strdup(str + i + 1));
		}
		i++;
	}
	return (NULL);
}

char	*take_rest(char *input, int position)
{
	int	i;

	i = position + 1;
	if (input[i] == '?' || ft_isdigit(input[i]))
		return (ft_strdup(input + i + 1));
	while (input[i - 1])
	{
		if (!isalnum(input[i]) && input[i] != '_')
			return (ft_strdup(input + i));
		i++;
	}
	return (NULL);
}
