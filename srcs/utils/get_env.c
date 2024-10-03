/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:07:30 by nde-chab          #+#    #+#             */
/*   Updated: 2024/10/03 15:00:43 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_env(t_data *data, char **env)
{
	int i;

	i = 0;
	if (!data->env)
		return (SUCCESS);
	env = ft_calloc(sizeof(char *), (env_size(data) + 1));
	if (!env)
		return (FAIL);
	while (data->env)
	{
		env[i++] = data->env->env;
		data->env = data->env->next;
	}
	env[i] = NULL;
	return (SUCCESS);
}