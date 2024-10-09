/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:12:19 by clmanouk          #+#    #+#             */
/*   Updated: 2024/10/09 15:32:12 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_redirection	*init_redirection(void)
{
	t_redirection	*red;

	red = (t_redirection *)malloc(sizeof(t_redirection));
	if (!red)
		return (NULL);
	red->file_fd = -1;
	red->file = NULL;
	red->stop = NULL;
	red->next = NULL;
	red->next = NULL;
	return (red);
}

void	red_add_back(t_redirection **red, t_redirection *new)
{
	t_redirection	*temp;

	temp = *red;
	if (!*red)
	{
		*red = new;
		return ;
	}
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	new->prev = temp;
}

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
	new->skip = 0;
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
	temp->next = new;
	new->prev = temp;
}
