/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmanouk <clmanouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:23:44 by nde-chab          #+#    #+#             */
/*   Updated: 2024/10/02 15:58:35 by clmanouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//void	ft_env(char **env)
//{
//	int i;

//	i = 0;
//	if (!env)
//		return ;
//	printf("Coucou\n\n\n\n");
//	while (env[i])
//	{
//		ft_putstr_fd(env[i], 1);
//		i++;
//	}
//	printf("Coucou\n\n\n\n");
//}

void	ft_env(t_data *data)
{
	data = init_data();
	while (data->env)
	{
		ft_putstr_fd(data->env->env, 1);
		data->env = data->env->next;
	}
	ft_putstr_fd("Coucou\n\n\n\n", 1);
}