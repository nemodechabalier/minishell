/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:15:09 by nde-chab          #+#    #+#             */
/*   Updated: 2024/09/17 15:43:09 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_pipe(t_pipe **pipe)
{
	t_pipe	*temp;
	t_pipe	*next;

	temp = *pipe;
	while (temp)
	{
		next = temp->next;
		free(temp);
		temp = NULL;
		temp = next;
	}
	*pipe = NULL;
}

void	ft_free_list(t_list **list)
{
	t_list	*temp;
	t_list	*next;

	temp = *list;
	while (temp)
	{
		next = temp->next;
		free(temp);
		temp = NULL;
		temp = next;
	}
	*list = NULL;
}

void	ft_free_cmd(t_cmd **cmd)
{
	if ((*cmd)->pipe)
		ft_free_pipe(&(*cmd)->pipe);
	(*cmd)->pipe = NULL;
	if ((*cmd)->cmds)
		ft_free_str((*cmd)->cmds);
	(*cmd)->cmds = NULL;
	if ((*cmd)->paths)
		ft_free_str((*cmd)->paths);
	(*cmd)->paths = NULL;
	if ((*cmd)->cmd)
		free((*cmd)->cmd);
	(*cmd)->cmd = NULL;
	if ((*cmd)->path_cmd)
		free((*cmd)->path_cmd);
	(*cmd)->path_cmd = NULL;
}

void	ft_free_parsing(t_parsing **parsing)
{
	if ((*parsing)->input)
		free((*parsing)->input);
	(*parsing)->input = NULL;
	if ((*parsing)->tokens)
		ft_free_list(&(*parsing)->tokens);
}

void	ft_free_data(t_data **data)
{
	if ((*data)->cmd)
		ft_free_cmd(&(*data)->cmd);
	if ((*data)->parsing)
		ft_free_parsing(&(*data)->parsing);
	(*data)->cmd = NULL;
	(*data)->parsing = NULL;
	free(*data);
	*data = NULL;
}
