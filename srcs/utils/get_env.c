/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:07:30 by nde-chab          #+#    #+#             */
/*   Updated: 2024/10/05 16:59:11 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**get_env(t_data *data)
{
	int i;
	char *temp;
	char **env;
	t_env *current;

	i = 0;
	if (!data->env)
		return (NULL);
	env = ft_calloc(sizeof(char *), (env_size(data->env) + 1));
	if (!env)
		return (NULL);
	current = data->env;
	while (current)
	{
		if (current->value[0])
		{
			temp = ft_strjoin_free(ft_strdup(current->name), "=");
			if (!temp || temp[0] == '=')
				return (ft_free_strs(env), NULL);
			env[i++] = ft_strjoin(temp, current->value);
			if (!env[i - 1])
				return (ft_free_strs(env),free(temp), NULL);
			free(temp);
		}
		current = current->next;
	}
	env[i] = NULL;
	return (env);
}