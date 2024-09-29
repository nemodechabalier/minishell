/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_remove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 14:44:21 by nde-chab          #+#    #+#             */
/*   Updated: 2024/09/29 18:14:51 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_quote(char c)
{
	if (c == 39 || c == '"')
		return (1);
	return (0);
}

int	is_in_quote(char *str, int end)
{
	int		count;
	char	c;
	int		i;

	i = 0;
	count = -1;
	while (str[i] && i <= end)
	{
		if (str[i] == 39 || str[i] == '"')
		{
			c = str[i];
			count = -count;
			i++;
			while (str[i] && i <= end)
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

char	**ft_realloc(char **strs, int *size)
{
	char	**new;
	int		i;

	i = 0;
	*size = *size * 2;
	new = malloc((*size) * sizeof(char *));
	if (!new)
		return (NULL);
	while (new[i])
	{
		new[i] = strs[i];
		i++;
	}
	new[i] = NULL;
	free(strs);
	return (new);
}

char	*remove_quote(char *str)
{
	char	*dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	dest = ft_calloc(ft_strlen(str), 1);
	if (!dest)
		return (NULL);
	while (str[i])
	{
		if (is_quote(str[i]))
		{
			if (i != 0 && is_in_quote(str, i) == 1 && is_in_quote(str, i
					- 1) == 1 && str[i] != str[i - 1])
				dest[j++] = str[i];
		}
		else
			dest[j++] = str[i];
		i++;
	}
	dest[j] = '\0';
	return (dest);
}

char	**remove_quote_cmd(char *str)
{
	int		i;
	int		j;
	int		size;
	int		count;
	char	**dest;
	char	*temp;

	i = 0;
	j = 0;
	size = 8;
	count = 0;
	dest = calloc(8, size);
	if (!dest)
		return (NULL);
	while (str[i - 1])
	{
		if ((str[i] = ' ' || !str[i]) && handle_quote(str, j, i) == -1)
		{
			temp = ft_substr(str, j, i);
			if (!temp)
				return (ft_free_strs(dest), NULL);
			dest[count++] = remove_quote(temp);
			if (!dest[count - 1])
				return (ft_free_strs(dest), NULL);
			if (count - 1 >= size - 1)
				dest = ft_realloc(dest, &size);
			if (!dest)
				return (NULL);
			j = i;
			free(temp);
		}
		i++;
	}
	return (dest);
}
