/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_lst_red.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:04:07 by nde-chab          #+#    #+#             */
/*   Updated: 2024/09/24 17:26:25 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	create_for_file(t_data *data, char *str, int bool)
{
	t_exec			*new;
	t_redirection	*pipes;

	new = new_exec();
	if (!new)
		return (FAIL);
	pipes = init_redirection();
	if (!pipes)
		return (free(new), FAIL);
	if (bool == 1 || bool == 2 || bool == 3)
		pipes->file = str;
	else
		pipes->stop = str;
	if (bool == 1)
		pipes->type = APEND;
	else if (bool == 2)
		pipes->type = TRUNC;
	else if (bool == 3)
		pipes->type = INPUT;
	else if (bool == 4)
		pipes->type = HERE_DOC;
	new->red = pipes;
	exec_add_back(&data->exec, new);
	return (SUCCESS);
}

int	ft_creat_file(t_data *data, char *str)
{
	if (str[0] == '>' && !files_operator(str[1]))
	{
		if (str[1] == ' ')
			return (create_for_file(data, str + 2, 1));
		return (create_for_file(data, str + 1, 1));
	}
	else if (str[0] == '>' && !files_operator(str[2]))
	{
		if (str[2] == ' ')
			return (create_for_file(data, str + 3, 2));
		return (create_for_file(data, str + 2, 2));
	}
	else if (str[0] == '<' && !files_operator(str[1]))
	{
		if (str[1] == ' ')
			return (create_for_file(data, str + 2, 3));
		return (create_for_file(data, str + 1, 3));
	}
	else if (str[0] == '<' && str[1] == '<' && !files_operator(str[2]))
	{
		if (str[2] == ' ')
			return (create_for_file(data, str + 2, 4));
		return (create_for_file(data, str + 2, 4));
	}
	return (FAIL);
}

int	ft_create_pipe(t_data *data)
{
	t_exec			*new;
	t_redirection	*pipes;

	new = new_exec();
	if (!new)
		return (FAIL);
	pipes = init_redirection();
	if (!pipes)
		return (free(new), FAIL);
	pipes->type = PIPE;
	new->red = pipes;
	if (pipe(pipes->pipes) == -1)
		return (free(new), free(pipe), FAIL);
	exec_add_back(&data->exec, new);
	return (SUCCESS);
}

int	creat_lst_red(t_data *data, t_list *lst, char **env)
{
	while (lst)
	{
		if (lst->type == FILES)
		{
			if (ft_creat_file(data, lst->token) == FAIL)
				return (FAIL);
		}
		else if (lst->type == PIPES)
		{
			if (ft_create_pipe(data) == FAIL)
				return (FAIL);
		}
		else
		{
			if (split_input(lst, data, env) == FAIL)
				return (FAIL);
		}
		lst = lst->next;
	}
	return (SUCCESS);
}
