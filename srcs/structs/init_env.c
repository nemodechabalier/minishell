/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmanouk <clmanouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:03:24 by clmanouk          #+#    #+#             */
/*   Updated: 2024/10/02 17:39:29 by clmanouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*init_env(char *env)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->env = ft_strdup(env);
	if (!env)
		return (free(new), NULL);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	env_add_back(t_env **env, t_env *new)
{
	t_env	*temp;

	temp = *env;
	if (*env == NULL)
	{
		*env = new;
		return ;
	}
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = new;
	new->prev = temp;
}

int	creat_env(t_env *env, t_data *data)
{
	int i;
	i = 0;
	while (env->env[i])
	{
		env = init_env(&env->env[i++]);
		if (!env)
			return (FAIL);
		env_add_back(&data->env, env);
	}
	return (SUCCESS);
}
