/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_case.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:37:17 by nde-chab          #+#    #+#             */
/*   Updated: 2024/10/07 20:29:01 by nde-chab         ###   ########.fr       */
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
		{
			bool = 1;
			while (files_operator(input[i]))
				i++;
			while (input[i] == ' ' && input[i] && i <= position)
				i++;
			while (i < position)
			{
				if (input[i] == ' ' && handle_quote(input, 0, i) == -1)
				{
					bool = 0;
					break ;
				}
				i++;
			}
		}
		if (input[i] && i < position)
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
		if (input[i] == '$' && which_quote(input, i) != 39
			&& !is_here_doc(input, i))
			return (1);
		i++;
	}
	return (0);
}

char	*take_name_2(char *input, int position)
{
	int	i;

	i = position + 1;
	while (input[i - 1])
	{
		if (ft_isalnum(input[i]) == 0 && input[i] != '_')
			return (ft_substr(input, position + 1,i - position - 1));
		i++;
	}
	return (NULL);
}

char	*take_value(t_env *env, char *name)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		if (!ft_strncmp(temp->name, name, ft_strlen(name)))
			return (temp->value);
		temp = temp->next;
	}
	return ("");
}

char	*take_rest(char *input, int position)
{
	int	i;

	i = position + 1;
	while (input[i - 1])
	{
		if (!isalnum(input[i]) && input[i] != '_')
			return (ft_strdup(input + i));
		i++;
	}
	return (NULL);
}

int	add_var(t_parsing *parsing, t_env *env, int position)
{
	char	*name;
	char	*value;
	char	*rest;
	char	*temp;

	name = take_name_2(parsing->input, position);
	if (!name)
		return (FAIL);
	value = take_value(env, name);
	temp = parsing->input;
	rest = take_rest(parsing->input, position);
	parsing->input[position] = '\0';
	if (handle_quote(parsing->input, 0, position) == -1)
	{
		parsing->input = ft_strjoin(parsing->input, "\"");
		parsing->input = ft_strjoin(parsing->input, value);
		parsing->input = ft_strjoin(parsing->input, "\"");
		parsing->input = ft_strjoin(parsing->input, rest);
	}
	else
	{
		parsing->input = ft_strjoin(parsing->input, value);
		parsing->input = ft_strjoin(parsing->input, rest);
	}
	return (SUCCESS);
}

int	var_env(t_parsing *parsing, t_env *env)
{
	int i;

	i = 0;
	while (interpret_var(parsing->input))
	{
		if (parsing->input[i] == '$' && which_quote(parsing->input, i) != 39
			&& !is_here_doc(parsing->input, i))
		{
			add_var(parsing, env, i);
			i = 0;
		}
		i++;
		if (!parsing->input[i])
			break ;
	}
	return (SUCCESS);
}
