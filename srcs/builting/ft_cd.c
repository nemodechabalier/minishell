/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmanouk <clmanouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:50:10 by clmanouk          #+#    #+#             */
/*   Updated: 2024/09/24 15:26:53 by clmanouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
The cd utility shall change the working directory of the current  shell
execution  environment  (see Section 2.12, Shell Execution Environment)
by executing the following steps in sequence. (In the following  steps,
the  symbol  curpath  represents an intermediate value used to simplify
the description of the algorithm used by cd.  There is  no  requirement
that curpath be made visible to the application.
*/