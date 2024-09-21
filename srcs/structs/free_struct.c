/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:15:09 by nde-chab          #+#    #+#             */
/*   Updated: 2024/09/21 14:04:56 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_redirection(t_redirection **red)
{
	if ((*red)->file)
		free((*red)->file);
	free(*red);
	*red = NULL;
}

void	ft_free_cmd(t_cmd **cmd)
{
	if ((*cmd)->paths)
		ft_free_strs((*cmd)->paths);
	if ((*cmd)->cmds)
		ft_free_strs((*cmd)->cmds);
	if ((*cmd)->cmd)
		free((*cmd)->cmd);
	if ((*cmd)->path_cmd)
		free((*cmd)->path_cmd);
	free(*cmd);
	*cmd = NULL;
}

void	ft_free_exec(t_exec **exec)
{
	t_exec	*temp;
	t_exec	*next;

	temp = *exec;
	while (temp)
	{
		next = temp->next;
		if (temp->cmd)
		{
			ft_free_cmd(&temp->cmd);
			temp->cmd = NULL;
		}
		if (temp->red)
		{
			ft_free_redirection(&temp->red);
			temp->red = NULL;
		}
	}
	*exec = NULL;
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
	if (*data)
		return ;
	if ((*data)->parsing)
		ft_free_parsing(&(*data)->parsing);
	(*data)->exec = NULL;
	(*data)->parsing = NULL;
	free(*data);
	*data = NULL;
}
