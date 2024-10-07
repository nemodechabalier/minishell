/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_case.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmanouk <clmanouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:37:17 by nde-chab          #+#    #+#             */
/*   Updated: 2024/10/07 18:50:37 by clmanouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_here_doc(char *input, int position)
{
	int	i;
	int	bool;

	i = 0;
	bool = 0;
	while (input[i] && i < position)
	{
		if (input[i] == '<' && input[i + 1] == '<' && handle_quote(input, 0,
				i) == -1)
			bool = 1;
		while (input[i] != ' ' && input[i])
			i++;
		if (input[i] == ' ' && handle_quote(input, 0, i) == -1)
			bool = 0;
		if (input[i])
			i++;
	}
	return (bool);
}

int	which_quote(char *input, int end)
{
	char	c;

	c = 0;
	int(i) = 0;
	while (input[i] && i < end)
	{
		if (input[i] == 39 || input[i] == '"')
		{
			c = input[i];
			i++;
			while (input[i] && i < end)
			{
				if (input[i] == c)
				{
					c = 0;
					break ;
				}
				i++;
			}
		}
		if (input[i])
			i++;
	}
	return (c);
}

int	interpret_var(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '$' && which_quote(input, i) != 39 && is_here_doc(input,
				i) != 0)
			return (1);
		i++;
	}
	return (0);
}
