/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_open.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:21:01 by nde-chab          #+#    #+#             */
/*   Updated: 2024/10/15 14:48:43 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_here(int bool)
{
	static int	here = 0;

	if (bool == 1)
		here = 1;
	if (bool == 0)
		here = 0;
	return (here);
}
