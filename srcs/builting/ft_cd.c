/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:50:10 by clmanouk          #+#    #+#             */
/*   Updated: 2024/10/14 11:38:06 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	add_path(t_env *env)
{
	t_env	*temp;
	char	cwd[PATH_MAX];
	char	*new;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (SUCCESS);
	temp = env;
	while (temp)
	{
		if (!ft_strncmp("PWD", temp->name, ft_strlen(temp->name)))
		{
			new = ft_strdup(cwd);
			if (!temp->value)
				return (FAIL);
			free(temp->value);
			temp->value = new;
			return (SUCCESS);
		}
		temp = temp->next;
	}
	return (SUCCESS);
}

char	*ft_getenv(char *str, t_env *env)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		if (!ft_strncmp(str, temp->name, ft_strlen(str)))
			return (ft_strdup(temp->value));
		temp = temp->next;
	}
	return (NULL);
}

void	ft_cd(t_cmd *cmd, t_data *data)
{
	char	*path;

	path = cmd->cmds[1];
	if (cmd->cmds[1] && cmd->cmds[2])
		return (ft_putendl_fd("minishell : cd: too many arguments", 2));
	if (path == NULL)
	{
		path = ft_getenv("HOME", data->env);
		if (path == NULL)
			return ;
	}
	if (chdir(path) != 0)
	{
		printf("cd: %s: No such file or directory\n", path);
		data->exit_status = 1;
	}
	else
	{
		if (add_path(data->env) == FAIL)
			ft_putstr_fd("ERROR MALLOC CD", 2);
	}
}
