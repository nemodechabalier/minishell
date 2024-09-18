/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:30:39 by clmanouk          #+#    #+#             */
/*   Updated: 2024/09/18 19:08:21 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	logical_operator(char c)
{
	if (c == '|')
		return (1);
	else if (c == '>')
		return (1);
	else if (c == '<')
		return (1);
	else
		return (0);
}

int	files_operator(char c)
{
	if (c == '>')
		return (1);
	else if (c == '<')
		return (1);
	return (0);
}

int	handle_input(t_parsing *parsing)
{
	while (1)
	{
		parsing->input = readline("Minishell beta 1.0$ ");
		if (!parsing->input)
		{
			printf("\n");
			break ;
		}
		if (*parsing->input)
		{
			add_history(parsing->input);
		}
		pars_token(parsing);
		printf("input : \n%s\ntoken :\n", parsing->input);
		print_token(parsing);
		ft_free_list(&parsing->tokens);
		free(parsing->input);
	}
	return (0);
}

int	handle_quote(t_parsing *parsing, int start, int end)
{
	int		i;
	int		count;
	char	c;

	i = start;
	count = 0;
	while (parsing->input[i] && i < end)
	{
		if (parsing->input[i] == 27 || parsing->input[i] == '"')
		{
			c = parsing->input[i];
			break ;
		}
		i++;
	}
	if (end == i)
		return (0);
	i = start;
	while (parsing->input[i] && i < end)
	{
		if (parsing->input[i] == c)
			count++;
		i++;
	}
	return (count % 2);
}
