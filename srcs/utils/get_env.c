/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:07:30 by nde-chab          #+#    #+#             */
/*   Updated: 2024/10/03 15:30:00 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**get_env(t_data *data)
{
	int i;
	char **env;
	t_env *temp;

	i = 0;
	if (!data->env)
		return (NULL);
	env = ft_calloc(sizeof(char *), (env_size(data->env) + 1));
	if (!env)
		return (NULL);
	temp = data->env;
	while (temp)
	{
		env[i++] = ft_strdup(temp->env);
		if (!env[i - 1])
			return (ft_free_strs(env), NULL);
		temp = temp->next;
	}
	env[i] = NULL;
	return (env);
}