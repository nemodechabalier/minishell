/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_var_env_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:34:44 by nde-chab          #+#    #+#             */
/*   Updated: 2024/10/14 13:12:22 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	interpret_var(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '$' && input[i + 1] != '$' && !space(input[i + 1])
			&& input[i + 1] != '\0' && which_quote(input, i) != 39
			&& !is_here_doc(input, i))
			return (1);
		i++;
	}
	return (0);
}

static int	h_quot(char *input, int start, int end)
{
	char	c;

	int (i) = start;
	int (count) = -1;
	while (input[i] && i < end)
	{
		if (input[i] == 39 || input[i] == '"')
		{
			c = input[i];
			count = -count;
			i++;
			while (input[i] && i < end)
			{
				if (input[i] == c)
				{
					count = -count;
					break ;
				}
				i++;
			}
		}
		if (input[i])
			i++;
	}
	return (count);
}

int	is_here_doc(char *input, int position)
{
	int (i) = 0;
	int (bool) = 0;
	while (input[i] && i < position)
	{
		if (input[i] == '<' && input[i + 1] == '<' && h_quot(input, 0, i) == -1)
		{
			bool = 1;
			while (files_operator(input[i]))
				i++;
			while (space(input[i]) && input[i] && i <= position)
				i++;
			while (i < position)
			{
				if (space(input[i]) && handle_quote(input, 0, i) == -1)
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

char	*take_name_2(char *input, int position)
{
	int	i;

	i = position + 1;
	if (input[i] == '?')
		return (ft_strdup("?"));
	if (ft_isdigit(input[i]))
		return (ft_substr(input, i, 1));
	while (input[i - 1])
	{
		if (ft_isalnum(input[i]) == 0 && input[i] != '_')
			return (ft_substr(input, position + 1, i - position - 1));
		i++;
	}
	return (NULL);
}

char	*take_value(t_env *env, char *name, t_data *data)
{
	t_env	*temp;

	temp = env;
	if (name[0] == '?')
		return (ft_itoa(data->exit_status));
	while (temp)
	{
		if (!ft_strncmp(temp->name, name, ft_strlen(name) + 1))
			return (ft_strdup(temp->value));
		temp = temp->next;
	}
	return (ft_strdup(""));
}
