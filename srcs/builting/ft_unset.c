/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmanouk <clmanouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:28:51 by clmanouk          #+#    #+#             */
/*   Updated: 2024/09/25 17:01:45 by clmanouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// pour supp var d'env

int	ft_unsetenv(const char *name, t_env **env)
{
	t_env	*current;
	int		len_name;

	if (name == NULL || ft_strchr(name, '=') != NULL)
		return (FAIL);
	current = *env;
	len_name = ft_strlen(name);
	while (current != NULL)
	{
		if (ft_strncmp(current->env, name, len_name) == 0
			&& current->env[len_name] == '=')
		{
			if (current->prev = NULL)
				current->prev->next = current->next;
			else
				*env = current->next;
			if (current->next != NULL)
				current->next->prev = current->prev;
			free(current->env);
			free(current);
		}
		current = current->next;
	}
	return (SUCCESS);
}