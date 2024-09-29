/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:24:35 by clmanouk          #+#    #+#             */
/*   Updated: 2024/09/29 18:28:03 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	files_error(t_parsing *parsing)
{
	int(i) = 0;
	while (parsing->input[i])
	{
		while (parsing->input[i] == ' ')
			i++;
		if (special_char_input(parsing) == FAIL)
			return (printf("syntax error\n"), -1);
		if (files_operator(parsing->input[i]))
		{
			i++;
			if (parsing->input[i] == '\0')
				return (printf("syntax error\n"), -1);
			if (files_operator(parsing->input[i])
				&& files_operator(parsing->input[i + 1]))
				return (printf("syntax error\n"), -1);
			else if (parsing->input[i])
			{
				if (files_operator(parsing->input[i]))
					i++;
				while (parsing->input[i] == ' ')
					i++;
				if (files_operator(parsing->input[i]) || !parsing->input[i])
					return (printf("syntax error\n"), -1);
			}
		}
		if (parsing->input[i])
			i++;
	}
	return (pars_token(parsing));
}

int	pipe_error(t_parsing *parsing)
{
	if (!parsing->tokens)
		return (FAIL);
	if (parsing->tokens && parsing->tokens->type == PIPES)
		return (printf("syntax error\n"), -1);
	while (parsing->tokens->next != NULL)
	{
		if (parsing->tokens->type == PIPES
			&& parsing->tokens->next->type == PIPES)
			return (printf("syntax error\n"), -1);
		parsing->tokens = parsing->tokens->next;
	}
	if (parsing->tokens && parsing->tokens->type == PIPES)
		return (printf("syntax error\n"), -1);
	return (SUCCESS);
}
