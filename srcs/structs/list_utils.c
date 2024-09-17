/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmanouk <clmanouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:10:34 by clmanouk          #+#    #+#             */
/*   Updated: 2024/09/17 12:56:26 by clmanouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_lstdelone (t_list *lst)
{
	if (lst == NULL)
		free(lst);
}

int	ft_lstsize(t_list *lst)
{
	t_list	*temp;
	int			i;

	i = 0;
	temp = lst;
	while (temp != NULL)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

t_list	*create_new_token(char *token)
{
		t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->token = token;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	token_add_front(t_list **lst, t_list *new)
{
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	new->next = *lst;
	(*lst)->prev = new;
	*lst = new;
}

void	token_add_back(t_list *lst, t_list *new)
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