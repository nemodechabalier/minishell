/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmanouk <clmanouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:05:03 by nde-chab          #+#    #+#             */
/*   Updated: 2024/09/19 14:20:56 by clmanouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
