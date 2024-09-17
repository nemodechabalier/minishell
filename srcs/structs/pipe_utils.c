/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmanouk <clmanouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:12:19 by clmanouk          #+#    #+#             */
/*   Updated: 2024/09/17 14:57:47 by clmanouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_lst_pipedelone(t_pipe *lst)
{
	if (lst == NULL)
		free(lst);
}

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

void	pipe_add_front(t_pipe *lst, t_pipe *new)
{
	if (lst == NULL)
	{
		lst = new;
		return ;
	}
	new->next = lst;
	lst->prev = new;
	lst = new;
}

void	pipe_add_back(t_pipe *lst, t_pipe *new)
{

	if (lst == NULL)
	{
		lst = new;
		new->prev = NULL;
		return ;
	}
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	lst->next = new;
	new->prev = lst;
	new->next = NULL;
}
