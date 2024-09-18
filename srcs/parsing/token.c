/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:27:28 by nde-chab          #+#    #+#             */
/*   Updated: 2024/09/18 19:12:13 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	create_token(t_parsing *parsing, int i, int j)
{
	char	*str;
	t_list	*list;

	str = ft_substr(parsing->input, j, i - j);
	if (!str)
		return (FAIL);
	list = create_new_token(str);
	if (!list)
		return (free(str), FAIL);
	token_add_back(&parsing->tokens, list);
	return (SUCCESS);
}

int	find_token_cmd(t_parsing *parsing, int *i, int j)
{
	while (parsing->input[*i])
	{
		if (logical_operator(parsing->input[*i]) && handle_quote(parsing, j,
				*i) == 0)
		{
			if (create_token(parsing, *i, j) == FAIL)
				return (FAIL);
			else
				return (SUCCESS);
		}
		*i += 1;
	}
	if (handle_quote(parsing, j, *i) == 0)
	{
		if (create_token(parsing, *i, j) == FAIL)
			return (FAIL);
		else
			return (SUCCESS);
	}
	return (ERROR_UNCLOSE);
}

int	pars_token(t_parsing *parsing)
{
	int	i;
	int	j;

	i = 0;
	while (parsing->input[i])
	{
		while (parsing->input[i] == ' ' && parsing->input[i])
			i++;
		j = i;
		if (parsing->input[i] == '\0')
			return(SUCCESS);
		if (files_operator(parsing->input[i]))
		{
			while ((files_operator(parsing->input[i])
					|| parsing->input[i] == ' ') && parsing->input[i])
				i++;
			if (parsing->input[i] == '\0')
				return (SUCCESS);
			while (parsing->input[i] != ' ' && parsing->input[i])
				i++;
			if (create_token(parsing, i, j) == FAIL)
				return (FAIL);
		}
		else if (parsing->input[i] == '|')
		{
			if (parsing->input[i + 1] == '|')
				return (ERROR_UNCLOSE);
			if (create_token(parsing, i + 1, j) == FAIL)
				return (FAIL);
		}
		else
		{
			find_token_cmd(parsing, &i, j);
			i--;
		}
		i++;
	}
	return (SUCCESS);
}
