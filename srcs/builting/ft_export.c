/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmanouk <clmanouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:28:57 by clmanouk          #+#    #+#             */
/*   Updated: 2024/10/02 17:51:13 by clmanouk         ###   ########.fr       */
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
/*
int ft_export(t_env **env, const char *new_env)
{
	verification de la variable sous format name=value
	find_var() pour verifier si elle existe deja
	si oui mettre valeur a jour
	si non ajouter a la liste
	char *equal_sign = ft_strlen(new_env, '=');
	char *name;
	t_env *current;
	
	current = *env;
	
}
*/