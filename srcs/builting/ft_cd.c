/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:50:10 by clmanouk          #+#    #+#             */
/*   Updated: 2024/10/03 13:18:16 by nde-chab         ###   ########.fr       */
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
		printf("cd: %s: No such file or directory\n", path) ;
}