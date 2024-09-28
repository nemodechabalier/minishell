/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_lst_red.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmanouk <clmanouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:04:07 by nde-chab          #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2024/09/28 13:25:44 by clmanouk         ###   ########.fr       */
=======
/*   Updated: 2024/09/25 15:19:48 by clmanouk         ###   ########.fr       */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	create_for_file(t_exec *exec, char *str, int bool)
{
	t_redirection	*pipes;

	pipes = init_redirection();
	if (!pipes)
		return (FAIL);
	if (bool == 1 || bool == 2 || bool == 3)
		pipes->file = str;
	else
		pipes->stop = str;
	if (bool == 1)
		pipes->type = TRUNC;
	else if (bool == 2)
		pipes->type = APEND;
	else if (bool == 3)
		pipes->type = INPUT;
	else if (bool == 4)
		pipes->type = HERE_DOC;
	red_add_back(&exec->red, pipes);
	return (SUCCESS);
}

int	ft_creat_file(t_exec *exec, char *str)
{
	if (str[0] == '>' && !files_operator(str[1]))
	{
		if (str[1] == ' ')
			return (create_for_file(exec, str + 2, 1));
		return (create_for_file(exec, str + 1, 1));
	}
	else if (str[0] == '>' && !files_operator(str[2]))
	{
		if (str[2] == ' ')
			return (create_for_file(exec, str + 3, 2));
		return (create_for_file(exec, str + 2, 2));
	}
	else if (str[0] == '<' && !files_operator(str[1]))
	{
		if (str[1] == ' ')
			return (create_for_file(exec, str + 2, 3));
		return (create_for_file(exec, str + 1, 3));
	}
	else if (str[0] == '<' && str[1] == '<' && !files_operator(str[2]))
	{
		if (str[2] == ' ')
			return (create_for_file(exec, str + 2, 4));
		return (create_for_file(exec, str + 2, 4));
	}
	return (FAIL);
}

int	creat_lst_red(t_data *data, t_list *lst, char **env)
{
	t_exec	*temp;

	temp = data->exec;
	if (!temp)
		temp = new_exec();
	if (!temp)
		return (FAIL);
	exec_add_back(&data->exec, temp);
	while (lst)
	{
		if (lst->type == FILES)
		{
			if (ft_creat_file(temp, lst->token) == FAIL)
				return (FAIL);
		}
		else if (lst->type == CMD)
		{
			if (split_input(lst, temp, env) == FAIL)
				return (FAIL);
		}
		else
		{
			temp = new_exec();
			if (!temp)
				return (FAIL);
			exec_add_back(&data->exec, temp);
		}
		lst = lst->next;
	}
	return (SUCCESS);
}
