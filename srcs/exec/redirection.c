/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:05:03 by nde-chab          #+#    #+#             */
/*   Updated: 2024/09/18 17:39:36 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	file_to_pipe(char *file, t_pip *pip)
{
	int	file_fd;

	file_fd = open(file, O_RDONLY);
	if (file_fd == -1)
		return (perror(file), close_pipe(pip), close(file_fd), 0);
	dup2(file_fd, STDIN_FILENO);
	dup2(pip->pipe_fd[1], STDOUT_FILENO);
	close_pipe(pip);
	close(file_fd);
	return (1);
}

void	pipe_to_pipe(int pipe_fd_1[2], int pipe_fd_2[2], t_pip *pip)
{
	dup2(pipe_fd_1[0], STDIN_FILENO);
	dup2(pipe_fd_2[1], STDOUT_FILENO);
	close_pipe(pip);
}

int	pipe_to_file(char *file, t_pip *pip)
{
	int	file_fd;

	file_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file_fd == -1)
		return (perror(file), close(file_fd), close_pipe(pip), 0);
	dup2(pip->pipe_fd[0], STDIN_FILENO);
	dup2(file_fd, STDOUT_FILENO);
	close_pipe(pip);
	close(file_fd);
	return (1);
}

//int	pipe_to_file_for_here_doc(char *file, t_pip *pip)
//{
//	int	file_fd;

//	file_fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
//	if (file_fd == -1)
//		return (perror(file), close(file_fd), close_pipe(pip), 0);
//	dup2(pip->pipe_fd[0], STDIN_FILENO);
//	dup2(file_fd, STDOUT_FILENO);
//	close_pipe(pip);
//	close(file_fd);
//	return (1);
//}
