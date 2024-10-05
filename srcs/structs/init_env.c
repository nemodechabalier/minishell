/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:03:24 by clmanouk          #+#    #+#             */
/*   Updated: 2024/10/05 16:56:58 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	env_size(t_env *env)
{
	t_env	*temp;
	int		i;

	temp = env;
	i = 0;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

t_env	*init_env(char *env)
{
	t_env	*new;
	int		i;

	i = 0;
	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	new->name = ft_substr(env, 0, i);
	if (!new->name)
		return (free(new), NULL);
	if (env[i])
		new->value = ft_strdup(env + i +1);
	else
		new->value = ft_strdup("");
	if (!new->name)
		return (free(new->name), free(new), NULL);
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

int	creat_env(char **env, t_data *data)
{
	t_env	*envs;
	int		i;

	if (!env)
		return (SUCCESS);
	i = 0;
	while (env[i])
	{
		envs = init_env(env[i++]);
		if (!env)
			return (FAIL);
		env_add_back(&data->env, envs);
	}
	return (SUCCESS);
}
