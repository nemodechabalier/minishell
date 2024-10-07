/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmanouk <clmanouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:23:44 by nde-chab          #+#    #+#             */
/*   Updated: 2024/10/07 18:08:55 by clmanouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	find_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	ft_env(t_data *data)
{
	t_env	*temp;

	temp = data->env;
	while (temp)
	{
		if (temp->value[0])
		{
			ft_printf("%s=%s\n", temp->name, temp->value);
		}
		temp = temp->next;
	}
}
