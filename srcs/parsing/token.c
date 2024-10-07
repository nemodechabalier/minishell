/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmanouk <clmanouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:27:28 by nde-chab          #+#    #+#             */
/*   Updated: 2024/10/07 18:10:02 by clmanouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	create_token(t_parsing *parsing, int i, int j, int bool)
{
	char	*str;
	t_list	*list;

	str = ft_substr(parsing->input, j, i - j);
	if (!str)
		return (FAIL);
	list = create_new_token(str, bool);
	if (!list)
		return (free(str), FAIL);
	token_add_back(&parsing->tokens, list);
	return (SUCCESS);
}

int	create_token_cmd(t_parsing *parsing, int *i, int j)
{
	while (parsing->input[*i])
	{
		if (logical_operator(parsing->input[*i]) && handle_quote(parsing->input,
				j, *i) == -1)
		{
			if (create_token(parsing, *i, j, 0) == FAIL)
				return (FAIL);
			else
				return (*i -= 1, SUCCESS);
		}
		*i += 1;
	}
	if (handle_quote(parsing->input, j, *i) == -1)
	{
		if (create_token(parsing, *i, j, 0) == FAIL)
			return (FAIL);
		else
			return (*i -= 1, SUCCESS);
	}
	return (ft_putendl_fd("error: unclose", 2), -1);
}

int	create_token_files(t_parsing *parsing, int *i, int j)
{
	while (files_operator(parsing->input[*i]))
		*i += 1;
	while ((parsing->input[*i]) == ' ')
		*i += 1;
	while (parsing->input[*i])
	{
		if ((logical_operator(parsing->input[*i]) || parsing->input[*i] == ' ')
			&& handle_quote(parsing->input, j, *i) == -1)
		{
			*i -= 1;
			return (create_token(parsing, *i + 1, j, 2));
		}
		*i += 1;
	}
	if (handle_quote(parsing->input, j, *i) == -1)
		return (create_token(parsing, *i, j, 2));
	return (ft_putendl_fd("error: unclose", 2), -1);
}

int	pars_token(t_parsing *parsing)
{
	int	j;

	int (i) = 0;
	while (parsing->input[i])
	{
		while (parsing->input[i] == ' ')
			i++;
		j = i;
		if (parsing->input[i] == '\0')
			return (SUCCESS);
		if (files_operator(parsing->input[i]))
			create_token_files(parsing, &i, j);
		else if (parsing->input[i] == '|')
		{
			if (parsing->input[i + 1] == '|')
				return (ft_putendl_fd("error || \n", 2), ERROR_UNCLOSE);
			if (create_token(parsing, i + 1, j, 1) == FAIL)
				return (FAIL);
		}
		else if (create_token_cmd(parsing, &i, j) == FAIL)
			return (FAIL);
		if (parsing->input[i])
			i++;
	}
	return (SUCCESS);
}
