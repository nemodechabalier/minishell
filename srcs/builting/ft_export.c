/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmanouk <clmanouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:28:57 by clmanouk          #+#    #+#             */
/*   Updated: 2024/09/26 17:24:34 by clmanouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
la cmd export est utilise pour marquer une variable d'env afin qu'elle soit exportee dans tous 
les processus fils. En C cela signifie que nous devons dfinir ou modifier une varibale d'env de 
maniere a ce qu'elle soit visible par tous les processus crees par l'appel au programme parent.
*/

/*
rechercher si var existe dans env;
si elle existe modifier sa valeur
si elle n'existe pas ajouter une nouvelle entree dans env
*/

int	find_var(const char *name)
{
	
}

void	export_var(const char *name, const char *value)
{
	
}

void	parse_and_export(const char *input)
{
	
}