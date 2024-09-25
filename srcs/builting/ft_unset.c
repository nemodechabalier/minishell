/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmanouk <clmanouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:28:51 by clmanouk          #+#    #+#             */
/*   Updated: 2024/09/25 12:07:05 by clmanouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Unset va supprimer une variable d'env ou une variable d'env exportee

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
// pour supprimer var globale

int	ft_unset_globalvar(const char *name)
{
	
}

// appel aux deux
int	ft_unset(const char *cmd, char **env)
{
	
}