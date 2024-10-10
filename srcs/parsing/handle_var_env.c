/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_var_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 14:16:58 by clmanouk          #+#    #+#             */
/*   Updated: 2024/10/10 17:41:57 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	which_quote(char *input, int end)
{
	char	c;

	c = 0;
	int (i) = 0;
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

static int	make_join_2(t_parsing *parsing, char *value, char *rest)
{
	char	*temp;

	temp = ft_strjoin(parsing->input, "\"");
	if (!temp)
		return (free(value), free(rest), FAIL);
	temp = ft_strjoin_free(temp, value);
	if (!temp)
		return (free(value), free(rest), FAIL);
	temp = ft_strjoin_free(temp, "\"");
	if (!temp)
		return (free(value), free(rest), FAIL);
	temp = ft_strjoin_free(temp, rest);
	if (!temp)
		return (free(value), FAIL);
	return (free(rest), free(value), free(parsing->input),
		parsing->input = temp, SUCCESS);
}

static int	make_join(t_parsing *parsing, char *value, char *rest, int position)
{
	char	*temp;

	if (value[0] == '\0')
	{
		temp = ft_strjoin(parsing->input, rest);
		if (!temp)
			return (free(value), FAIL);
		return (free(rest), free(value), free(parsing->input),
			parsing->input = temp, SUCCESS);
	}
	else if (handle_quote(parsing->input, 0, position) == 1)
	{
		temp = ft_strjoin(parsing->input, value);
		if (!temp)
			return (free(rest), free(value), FAIL);
		temp = ft_strjoin_free(temp, rest);
		if (!temp)
			return (free(value), FAIL);
		return (free(rest), free(value), free(parsing->input),
			parsing->input = temp, SUCCESS);
	}
	else
		return (make_join_2(parsing, value, rest));
}

static int	add_var(t_parsing *parsing, t_env *env, int position, t_data *data)
{
	char	*name;
	char	*value;
	char	*rest;

	name = take_name_2(parsing->input, position);
	if (!name)
		return (FAIL);
	value = take_value(env, name, data);
	if (!value)
		return (free(name), FAIL);
	rest = take_rest(parsing->input, position);
	parsing->input[position] = '\0';
	return (free(name), make_join(parsing, value, rest, position));
}

int	var_env(t_parsing *parsing, t_env *env, t_data *data)
{
	int	i;

	i = 0;
	while (interpret_var(parsing->input))
	{
		if (parsing->input[i] == '$' && parsing->input[i + 1] != '$'
			&& !space(parsing->input[i + 1]) && parsing->input[i + 1] != '\0'
			&& which_quote(parsing->input, i) != 39
			&& !is_here_doc(parsing->input, i))
		{
			if (add_var(parsing, env, i, data) == FAIL)
				return (FAIL);
			i = 0;
		}
		i++;
		if (!parsing->input[i])
			break ;
	}
	return (SUCCESS);
}
