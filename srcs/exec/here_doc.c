/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:27:14 by nde-chab          #+#    #+#             */
/*   Updated: 2024/10/10 15:15:09 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*creat_here_doc(void)
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
	i = open(name, O_CREAT, 0655);
	close(i);
	return (name);
}

int	here_doc_2(t_redirection *red, char *line, int len)
{
	write(1, "> ", 2);
	line = get_next_line(0);
	while (line)
	{
		if (ft_strncmp(line, red->stop, len) == 0 && line[len] == '\n')
			break ;
		write(1, "> ", 2);
		write(red->file_fd, line, ft_strlen(line));
		free(line);
		line = get_next_line(0);
	}
	if (!line && g_verif != 5)
	{
		ft_putstr_fd("minishell: warning: here-document at line ", 2);
		ft_putnbr_fd(count_line(0), 2);
		ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
		ft_putstr_fd(red->stop, 2);
		ft_putendl_fd("')", 2);
	}
	else if (!line)
		write(2, "\n", 1);
	free(line);
	close(red->file_fd);
	return (SUCCESS);
}

int	here_doc(t_redirection *red)
{
	char	*line;
	int		len;

	g_verif = 1;
	red->file = creat_here_doc();
	if (!red->file)
		return (FAIL);
	len = ft_strlen(red->stop);
	red->file_fd = open(red->file, W_OK, R_OK);
	line = NULL;
	return (here_doc_2(red, line, len));
}
