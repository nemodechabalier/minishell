/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:39:24 by nde-chab          #+#    #+#             */
/*   Updated: 2024/10/07 17:22:19 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_token(t_parsing *parsing)
{
	int	i;

	i = 1;
	while (parsing->tokens)
	{
		printf("token %d : %s\n", i++, parsing->tokens->token);
		if (parsing->tokens->type == PIPES)
			printf("type = PIPE\n");
		if (parsing->tokens->type == CMD)
			printf("type = CMD\n");
		if (parsing->tokens->type == FILES)
			printf("type = FILE\n");
		parsing->tokens = parsing->tokens->next;
	}
}

void	print_strs(char **strs)
{
	int	i;

	if (!strs)
	{
		printf("error strs = NULL");
		return ;
	}
	i = 0;
	while (strs[i])
		ft_putendl_fd(strs[i++], 2);
}
