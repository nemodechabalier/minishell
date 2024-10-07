/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_remove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmanouk <clmanouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 14:44:21 by nde-chab          #+#    #+#             */
/*   Updated: 2024/10/07 18:09:40 by clmanouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_in_quote(char *str, int end)
{
	char	c;

	int (i) = 0;
	int (count) = -1;
	while (str[i] && i <= end)
	{
		if (str[i] == 39 || str[i] == '"')
		{
			c = str[i];
			count = -count;
			i++;
			while (str[i] && i < end)
			{
				if (str[i] == c)
				{
					count = -count;
					break ;
				}
				i++;
			}
		}
		if (str[i])
			i++;
	}
	return (count);
}

int	is_quote(char *str, int i)
{
	if (str[i] == 39 || str[i] == '"')
	{
		if (i == 0 || (is_in_quote(str, i + 1) == -1 || is_in_quote(str, i
					- 1) == -1))
			return (0);
	}
	return (1);
}

char	*remove_quote(char *str)
{
	char	*dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	dest = ft_calloc(ft_strlen(str) + 1, 1);
	if (!dest)
		return (NULL);
	while (str[i])
	{
		if (is_quote(str, i))
			dest[j++] = str[i];
		i++;
	}
	dest[j] = '\0';
	return (dest);
}

t_remove	init_remove(void)
{
	t_remove	rm;

	rm.j = 0;
	rm.i = 1;
	rm.count = 0;
	rm.size = 8;
	rm.temp = NULL;
	rm.dest = ft_calloc(8, rm.size);
	return (rm);
}

char	**remove_quote_cmd(char *str)
{
	t_remove (r) = init_remove();
	if (!r.dest)
		return (NULL);
	while (str[r.i - 1])
	{
		if ((str[r.i] == ' ' || !str[r.i]) && handle_quote(str, r.j, r.i) == -1)
		{
			r.temp = ft_substr(str, r.j, r.i - r.j);
			if (!r.temp)
				return (ft_free_strs(r.dest), NULL);
			r.dest[r.count++] = remove_quote(r.temp);
			if (!r.dest[r.count - 1])
				return (ft_free_strs(r.dest), NULL);
			if (r.count - 1 >= r.size - 1)
				r.dest = ft_realloc(r.dest, &r.size);
			if (!r.dest)
				return (NULL);
			while (str[r.i] == ' ')
				r.i++;
			r.j = r.i;
			free(r.temp);
		}
		r.i++;
	}
	return (r.dest);
}
