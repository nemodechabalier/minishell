/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:12:19 by clmanouk          #+#    #+#             */
/*   Updated: 2024/09/17 15:19:56 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_lstsize_pipe(t_pipe *lst)
{
	t_pipe	*temp;
	int		i;

	i = 0;
	temp = lst;
	while (temp != NULL)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

t_pipe	*create_new_pipe(void)
{
	t_pipe *new;

	new = (t_pipe *)malloc(sizeof(t_pipe));
	if (!new)
		return (NULL);
	new->tab[0] = -1;
	new->tab[1] = -1;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	pipe_add_front(t_pipe **lst, t_pipe *new)
{
	if (lst == NULL)
	{
		(*lst) = new;
		return ;
	}
	new->next = lst;
	(*lst)->prev = new;
	lst = new;
}

void	pipe_add_back(t_pipe **lst, t_pipe *new)
{
	t_pipe *temp;

	temp = *lst;
	if (lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (temp->next != NULL)
		lst = temp->next;
	temp->next = new;
	new->prev = lst;
}
