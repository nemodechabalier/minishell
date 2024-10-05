/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:15:09 by nde-chab          #+#    #+#             */
/*   Updated: 2024/10/05 16:33:17 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_redirection(t_redirection **red)
{
	t_redirection	*temp;
	t_redirection	*next;

	temp = *red;
	while (temp)
	{
		if (temp->type == HERE_DOC && temp->file)
			unlink(temp->file);
		if (temp->file)
			free(temp->file);
		if (temp->stop)
			free(temp->stop);
		next = temp->next;
		free(temp);
		temp = next;
	}
	*red = NULL;
}

void	ft_free_cmd(t_cmd **cmd)
{
	if ((*cmd)->paths)
		ft_free_strs((*cmd)->paths);
	if ((*cmd)->cmds[0] != (*cmd)->path_cmd && (*cmd)->path_cmd)
		free((*cmd)->path_cmd);
	if ((*cmd)->cmds)
		ft_free_strs((*cmd)->cmds);
	if ((*cmd)->env)
		ft_free_strs((*cmd)->env);
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
		free(temp);
		temp = NULL;
		temp = next;
	}
	*exec = NULL;
}

void	ft_free_list(t_list **list)
{
	t_list	*temp;
	t_list	*next;

	temp = *list;
	if (temp)
	{
		while (temp->prev)
			temp = temp->prev;
	}
	while (temp)
	{
		next = temp->next;
		free(temp->token);
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
	(*parsing)->tokens = NULL;
	free(*parsing);
	*parsing = NULL;
}

void	ft_free_env(t_env **env)
{
	t_env	*temp;
	t_env	*next;

	temp = *env;
	while (temp)
	{
		next = temp->next;
		if (temp->name)
			free(temp->name);
		if (temp->value)
			free(temp->value);
		free(temp);
		temp = next;
	}
	*env = NULL;
}

void	ft_free_data(t_data **data)
{
	if (!*data)
		return ;
	if ((*data)->parsing)
		ft_free_parsing(&(*data)->parsing);
	if ((*data)->exec)
		ft_free_exec(&(*data)->exec);
	if ((*data)->env)
		ft_free_env(&(*data)->env);
	(*data)->exec = NULL;
	(*data)->parsing = NULL;
	if ((*data)->stdin != -1)
		close((*data)->stdin);
	if ((*data)->stdout != -1)
		close((*data)->stdout);
	free(*data);
	*data = NULL;
}
