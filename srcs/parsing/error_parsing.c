/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmanouk <clmanouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:27:22 by clmanouk          #+#    #+#             */
/*   Updated: 2024/10/10 15:27:27 by clmanouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_print_error(char *str, int i, int bool)
{
	if (bool == 0)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `newline'",
			2);
		return ;
	}
	while (i > 0)
	{
		if (logical_operator(str[i]))
			break ;
		i--;
	}
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (logical_operator(str[i]))
		write(2, &str[i], 1);
	else
		write(2, "<", 1);
	write(2, "'\n", 2);
}

int	ft_file_unclose(t_parsing *parsing)
{
	int	count;

	int (i) = 0;
	while (parsing->input[i])
	{
		count = 0;
		if (files_operator(parsing->input[i]))
		{
			while (files_operator(parsing->input[i])
				|| space(parsing->input[i]))
			{
				if (files_operator(parsing->input[i]))
					count++;
				if (count > 2)
					return (ft_print_error(parsing->input, i, 1), FAIL);
				i++;
			}
			if (!parsing->input[i])
				return (ft_print_error(parsing->input, i, 0), FAIL);
			if (parsing->input[i] == '|')
				return (ft_print_error(parsing->input, i, 1), FAIL);
		}
		i++;
	}
	return (SUCCESS);
}

int	special_char_input(t_parsing *parsing)
{
	int	i;

	i = 0;
	while (parsing->input[i])
	{
		if (parsing->input[i] == 92 || parsing->input[i] == '&')
			return (ft_putendl_fd("Error: forbidden character", 2), FAIL);
		i++;
	}
	return (ft_file_unclose(parsing));
}

int	files_error(t_parsing *parsing)
{
	int (i) = 0;
	while (parsing->input[i])
	{
		while (space(parsing->input[i]))
			i++;
		if (special_char_input(parsing) == FAIL)
			return (-1);
		if (files_operator(parsing->input[i]))
		{
			i++;
			if (parsing->input[i])
			{
				if (files_operator(parsing->input[i]))
					i++;
				while (space(parsing->input[i]))
					i++;
				if (files_operator(parsing->input[i]) || !parsing->input[i])
					return (ft_print_error(parsing->input, i, 1), -1);
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
		return (ft_putendl_fd("syntax error near unexpected token `|'", 2), -1);
	while (parsing->tokens->next != NULL)
	{
		if (parsing->tokens->type == PIPES
			&& parsing->tokens->next->type == PIPES)
			return (ft_putendl_fd("syntax error near unexpected token `|'", 2),
				-1);
		parsing->tokens = parsing->tokens->next;
	}
	if (parsing->tokens && parsing->tokens->type == PIPES)
		return (ft_putendl_fd("error: unclose", 2), -1);
	return (SUCCESS);
}
