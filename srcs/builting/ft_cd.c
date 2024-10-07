/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:50:10 by clmanouk          #+#    #+#             */
/*   Updated: 2024/10/07 17:22:13 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_cd(t_cmd *cmd)
{
	char	*path;

	path = cmd->cmds[1];
	if (cmd->cmds[1] && cmd->cmds[2])
		return (ft_putendl_fd("minishell : cd: too many arguments", 2));
	if (path == NULL)
	{
		path = getenv("HOME");
		if (path == NULL)
		{
			return ;
		}
	}
	if (chdir(path) != 0)
		printf("cd: %s: No such file or directory\n", path);
}
