/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmanouk <clmanouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 19:54:00 by nde-chab          #+#    #+#             */
/*   Updated: 2024/09/30 21:23:12 by clmanouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/includes/minishell.h"

int	main(int ac, char **av, char **envp)
{
	if (access("/usr/bin/ls", X_OK) == 0)
	{
		char *args[] = {"/usr/bin/ls", NULL};
		execve("/usr/bin/ls", args, envp);
	}
	else
	{
		perror("Permission denied");
	}
}