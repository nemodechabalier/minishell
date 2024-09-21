/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:27:28 by nde-chab          #+#    #+#             */
/*   Updated: 2024/09/21 14:30:04 by nde-chab         ###   ########.fr       */
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

int	create_token_cmd(t_parsing *parsing, int *i, int j)
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

int	create_token_files(t_parsing *parsing, int *i, int j)
{
	while (files_operator(parsing->input[*i]))
		*i += 1;
	while (parsing->input[*i])
	{
		if ((logical_operator(parsing->input[*i]) || parsing->input[*i] == ' ')
			&& handle_quote(parsing, j, *i) == 0)
		{
			*i -= 1;
			return (create_token(parsing, *i + 1, j));
		}
		*i += 1;
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
			return (SUCCESS);
		if (files_operator(parsing->input[i]))
			create_token_files(parsing, &i, j);
		else if (parsing->input[i] == '|')
		{
			if (parsing->input[i + 1] == '|')
				return (ERROR_UNCLOSE);
			if (create_token(parsing, i + 1, j) == FAIL)
				return (FAIL);
		}
		else
		{
			create_token_cmd(parsing, &i, j);
			i--;
		}
		i++;
	}
	return (SUCCESS);
}

// int	find_cmd(t_parsing *parsing)
//{
//	int i = 0;
//	while (parsing->input[i])
//	{
//		if (parsing->input[i] == '|')
//			// mettre les cmds dans le bonne ordre
//		i++;
//	}
//	return (SUCCESS);
//}
