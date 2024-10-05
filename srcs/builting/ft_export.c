/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:28:57 by clmanouk          #+#    #+#             */
/*   Updated: 2024/10/05 17:37:37 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

// int	find_var(t_env *env, const char *name)
//{
//	char	*equal_sign;
//	size_t	key_len;

//	while (env != NULL)
//	{
//		equal_sign = ft_strchr(env->env, '=');
//		if (equal_sign != NULL)
//		{
//			key_len = equal_sign - env->env;
//			if (ft_strncmp(env->env, name, key_len) == 0
//				&& name[key_len] == '\0')
//				return (SUCCESS);
//		}
//		env = env->next;
//	}
//	return (FAIL);
//}

void	ft_export(t_data *data, t_cmd *cmd)
{
	if (!cmd->cmds[1])
		ft_print_export(data);
}
