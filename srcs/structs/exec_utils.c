/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:12:19 by clmanouk          #+#    #+#             */
/*   Updated: 2024/09/23 12:56:39 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_exec	*new_exec(void)
{
	t_exec	*new;

	new = (t_exec *)malloc(sizeof(t_exec));
	if (!new)
		return (NULL);
	new->cmd = NULL;
	new->next = NULL;
	new->prev = NULL;
	new->red = NULL;
	return (new);
}

void	exec_add_back(t_exec **exec, t_exec *new)
{
	t_exec	*temp;

	temp = *exec;
	if (!*exec)
	{
		*exec = new;
		return ;
	}
	while (temp->next)
		temp = temp->next;
	(*exec)->next = new;
	new->prev = *exec;
}
