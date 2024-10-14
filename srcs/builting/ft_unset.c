/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:28:51 by clmanouk          #+#    #+#             */
/*   Updated: 2024/10/14 14:31:34 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_free_1_env(t_env **env, t_env *next)
{
	t_env	*prev;

	if (!next->next)
	{
		prev = next->prev;
		prev->next = NULL;
	}
	else if (!next->prev)
	{
		*env = next->next;
		(*env)->prev = NULL;
	}
	else
	{
		prev = next->prev;
		prev->next = next->next;
		prev->next->prev = prev;
	}
	return (free(next->name), free(next->value), free(next), SUCCESS);
}

int	remove_env(t_env **env, char *name, char *value)
{
	t_env	*next;

	next = *env;
	while (next)
	{
		if (!ft_strncmp(name, next->name, ft_strlen(name)) && (!value
				|| !ft_strncmp(value, next->value, ft_strlen(value) + 1)))
		{
			if (value)
				free(value);
			return (free(name), ft_free_1_env(env, next));
		}
		next = next->next;
	}
	return (free(name), free(value), SUCCESS);
}

int	take_name(char *str, t_data *data)
{
	char	*value;
	char	*name;
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	name = ft_substr(str, 0, i);
	if (!name)
		return (FAIL);
	if (str[i] == '=')
	{
		value = ft_substr(str, i + 1, ft_strlen(str));
		if (!value)
			return (free(name), FAIL);
	}
	else
		value = NULL;
	return (remove_env(&data->env, name, value));
}

int	ft_unset(t_cmd *cmd, t_data *data)
{
	int	i;

	i = 1;
	data->exit_status = 0;
	while (cmd->cmds[i])
	{
		if (take_name(cmd->cmds[i], data) == FAIL)
		{
			ft_putendl_fd("minishell : unset :ERROR MALLOC", 2);
		}
		i++;
	}
	return (SUCCESS);
}
