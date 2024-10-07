/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:28:57 by clmanouk          #+#    #+#             */
/*   Updated: 2024/10/07 20:36:52 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_creat_new_element(t_data *data, char *name, char *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (FAIL);
	new->next = NULL;
	new->prev = NULL;
	new->name = name;
	new->value = value;
	env_add_back(&data->env, new);
	return (SUCCESS);
}

int	add_env(char *str, t_data *data)
{
	t_env	*temp;
	char	*name;
	char	*value;

	int (i) = 0;
	while (str[i] && str[i] != '=')
		i++;
	name = ft_substr(str, 0, i);
	value = ft_substr(str, i + 1, ft_strlen(str));
	if (!value || !name)
		return (free(name), free(value), FAIL);
	temp = data->env;
	while (temp)
	{
		if (!ft_strncmp(name, temp->name, ft_strlen(name)))
		{
			if (value[0] != '\0')
				return (free(name), free(temp->value), temp->value = value,
					SUCCESS);
			return (free(name), free(value), SUCCESS);
		}
		temp = temp->next;
	}
	return (ft_creat_new_element(data, name, value));
}

void	ft_print_export(t_data *data)
{
	t_env	*temp;

	temp = data->env;
	while (temp)
	{
		ft_printf("export %s=\"%s\"\n", temp->name, temp->value);
		temp = temp->next;
	}
}

int	valid_export(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[0]))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	ft_export(t_data *data, t_cmd *cmd)
{
	int	i;

	i = 1;
	if (!cmd->cmds[1])
		ft_print_export(data);
	while (cmd->cmds[i])
	{
		if (valid_export(cmd->cmds[i]))
		{
			if (add_env(cmd->cmds[i], data) == FAIL)
				ft_putendl_fd("minishell : export :ERROR MALLOC", 2);
		}
		else
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(cmd->cmds[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
		}
		i++;
	}
}
