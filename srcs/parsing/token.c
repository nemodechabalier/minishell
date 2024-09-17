/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmanouk <clmanouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:30:39 by clmanouk          #+#    #+#             */
/*   Updated: 2024/09/17 18:02:38 by clmanouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#include "../includes/minishell.h"

int	find_(char c)
{
	if (c == '"')
		return (1);
	else if (c == '|')
		return (1);
	else if (c == '>')
		return (1);
	else if (c == '<')
		return (1);
	else
		return (0);
}

int	handle_input(t_parsing *parsing)
{
	readline(parsing->input);
	if (parsing->input != NULL && *parsing->input != NULL)
		add_history(parsing->input);
	return (0);
}

int	handle_dquote(t_parsing *parsing)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (parsing->input[i])
	{
		if (parsing->input[i] == '"')
			count++;
		i++;
	}
	if (count % 2 == 0)
		return (1);
	return (0);
}

