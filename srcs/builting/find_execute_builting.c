/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_execute_builting.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmanouk <clmanouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:53:56 by clmanouk          #+#    #+#             */
/*   Updated: 2024/10/02 15:02:56 by clmanouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((t_byte)s1[i] - (t_byte)s2[i]);
		i++;
	}
	return (0);
}

//int	find_built_var(t_parsing *parsing)
//{
	
//}

int	find_built(t_parsing *parsing)
{
	char	cwd[PATH_MAX];
	int		token_built;
	char	*path;
	char	**split;

	path = NULL;
	printf("Token : %s\n", parsing->tokens->token);
	token_built = ft_strncmp(parsing->tokens->token, "cd", 2);
	split = ft_split(parsing->tokens->token, ' ');
	if (!split)
		return (FAIL);
	if (token_built == 0)
	{
		if (ft_strcmp(parsing->tokens->token, "cd") != 0)
		{
			split = remove_quote_cmd(split[1]);
			printf("before ft_cd path : %s\n", split[1]);
			ft_cd(split[1]);
		}
		else
			ft_cd(getenv("HOME"));
		if (getcwd(cwd, sizeof(cwd)) != NULL)
			printf("New path after cd: %s\n", cwd);
		return (1);
	}
	if (ft_strncmp(parsing->tokens->token, "echo", 4) == 0)
	{
		// a rajouter condiation pour le -n
		split = remove_quote_cmd(split[1]);
		return (ft_echo(*split), 1);
	}
	if (ft_strcmp(parsing->tokens->token, "pwd") == 0)
		return (ft_pwd(), 1);
	return (FAIL);
}
