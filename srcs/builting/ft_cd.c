/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmanouk <clmanouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:50:10 by clmanouk          #+#    #+#             */
/*   Updated: 2024/10/01 19:20:40 by clmanouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
chdir return 0 en cas de success
*/
void	ft_cd(char *path)
{
	if (path == NULL)
	{
		path = getenv("HOME");
		if (path == NULL)
		{
			return ;
		}
	}
	if (chdir(path) != 0)
		return ;
}