/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmanouk <clmanouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:24:35 by clmanouk          #+#    #+#             */
/*   Updated: 2024/09/26 18:52:51 by clmanouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	first_operator(t_parsing *parsing)
{
	int	i;

	i = 0;
	while (parsing->input[i])
	{
		while (parsing->input[i] == ' ')
			i++;
		if (logical_operator(parsing->input[i]))
		{
			i++;
			if (parsing->input[i] == '\0' || logical_operator(parsing->input[i]))
				return (printf("syntax error\n"), -1);
			else
				pars_token(parsing);
		}
		i++;
	}
	return (1);
}

int	handle_var_double_quote(t_parsing *parsing)
{
	int i;
	char **split;
	
	i = 0;
	split = split_input_d_quote(parsing);
	//expandre la var d'env
}