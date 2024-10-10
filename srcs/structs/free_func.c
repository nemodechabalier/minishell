/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:34:36 by nde-chab          #+#    #+#             */
/*   Updated: 2024/10/10 14:01:05 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	if ((*cmd)->path_cmd && (*cmd)->cmds[0] != (*cmd)->path_cmd)
		free((*cmd)->path_cmd);
	if ((*cmd)->cmds)
		ft_free_strs((*cmd)->cmds);
	if ((*cmd)->env)
		ft_free_strs((*cmd)->env);
	free(*cmd);
	*cmd = NULL;
}

void	ft_free_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		strs[i] = NULL;
		i++;
	}
	free(strs);
	strs = NULL;
}

void	free_after_exec(t_data *data)
{
	if (data->exec)
		ft_free_exec(&data->exec);
	data->exec = NULL;
	if (data->parsing->tokens)
		ft_free_list(&data->parsing->tokens);
	data->parsing->tokens = NULL;
	if (data->parsing->input)
		free(data->parsing->input);
	data->parsing->input = NULL;
}
