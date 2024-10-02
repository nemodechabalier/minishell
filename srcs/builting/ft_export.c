/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmanouk <clmanouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:28:57 by clmanouk          #+#    #+#             */
/*   Updated: 2024/10/02 13:55:02 by clmanouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
la cmd export est utilise pour marquer une variable d'env afin qu'elle soit exportee dans tous
les processus fils. En C cela signifie que nous devons dfinir ou modifier une varibale d'env de
maniere a ce qu'elle soit visible par tous les processus crees par l'appel au programme parent.
*/

int	find_var(t_env *env, const char *name)
{
	char	*equal_sign;
	size_t	key_len;

	while (env != NULL)
	{
		equal_sign = ft_strchr(env->env, '=');
		if (equal_sign != NULL)
		{
			key_len = equal_sign - env->env;
			if (ft_strncmp(env->env, name, key_len) == 0
				&& name[key_len] == '\0')
				return (SUCCESS);
		}
		env = env->next;
	}
	return (FAIL);
}

void	export_var(t_env **env, const char *name, const char *value)
{
	t_env	*temp;
	t_env	*new;

	
	if (find_var(*env, name) == FAIL)
	{
		new = creat_env(name, value);
		if (!new)
			return (NULL);
		env_add_back(env, new);
	}
	//else
	//{
	//	temp = *env;
	//	while (temp != NULL)
	//	{
			
	//	}
	//}
}
