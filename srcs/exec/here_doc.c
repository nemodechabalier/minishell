/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:27:14 by nde-chab          #+#    #+#             */
/*   Updated: 2024/09/23 16:48:24 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*creat_here_doc()
{
	char	*name;
	char	*temp;
	int		i;

	i = 0;
	name = ft_strdup(".here_doc");
	if (!name)
		return (NULL);
	while (access(name, F_OK) != -1)
	{
		temp = ft_strdup(name);
		free(name);
		if (!temp)
			return (NULL);
		name = ft_strjoin(temp, "1");
		free(temp);
		if (!name)
			return (NULL);
		i++;
	}
	return (name);
}

int	here_doc(t_redirection *red)
{
	char *line;
	int len;

	red->file = creat_here_doc();
	if (!red->file)
		return (FAIL);
	len = ft_strlen(red->stop);
	red->file_fd = open(red->file, O_CREAT, 0644);
	line = get_next_line(0);
	while (line)
	{
		if (ft_strncmp(line, red->stop, len) == 0 && line[len] == '\n')
			break ;
		write(red->file_fd, line, ft_strlen(line));
		free(line);
		line = get_next_line(0);
	}
	free(line);
	dup2(red->file_fd, STDIN_FILENO);
	close(red->file_fd);
	return (SUCCESS);
}