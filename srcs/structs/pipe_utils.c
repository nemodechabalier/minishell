/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:12:19 by clmanouk          #+#    #+#             */
/*   Updated: 2024/09/21 12:17:11 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_exec	*new_exec(void)
{
	t_exec	*exec;

	exec = (t_exec *)malloc(sizeof(t_exec));
	if (!exec)
		return (NULL);
	exec->cmd = NULL;
	exec->next = NULL;
	exec->prev = NULL;
	exec->red = NULL;
}

void	exec_add_back(t_exec **exec, t_exec *new)
{
	t_exec *temp;
	temp = *exec;
	if (!*exec)
	{
		*exec = new;
		return ;
	}
	while (temp->next)
		temp = temp->next;
	new->prev = temp;
	temp->next = new;
}