/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_var_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmanouk <clmanouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 14:16:58 by clmanouk          #+#    #+#             */
/*   Updated: 2024/10/07 18:17:18 by clmanouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_in_quote(char *input, int end)
{
	char	c;
	int(i) = 0;
	while (input[i] && i < end)
	{
		if (input[i] == 39 || input[i] == '"')
		{
			c = input[i];
			i++;
			while (input[i] && i < end)
			{
				if (input[i] == c)
				{
					c = 0;
					break ;
				}
				i++;
			}
		}
		if (input[i])
			i++;
	}
	return (c);
}

int	count_var(char *input)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '$')
			count++;
		i++;
	}
	return (count);
}
char	*find_name_var(char *input)
{
	char	*name;

	int(i) = 0;
	int(j) = 0;
	while (1)
	{
		if (input[j] == '$')
		{
			j++;
			break ;
		}
		j++;
		if (input[j] == '$' || input[j] == '\0')
		{
			if (input[j] == '$')
				j++;
			break ;
		}
	}
	i = j;
	while (1)
	{
		j++;
		if (input[j] == '$' || input[j] == '"' || input[j] == '\0'
			|| input[j] == 39 || input[j] == ' ')
			break ;
	}
	name = ft_substr(input, i, j - i);
	if (!name)
		return (NULL);
	return (name);
}

char	*find_rest(char *input, char **end_input)
{
	int	rest;

	*end_input = input;
	rest = ft_strlen(input);
	int(j) = 0;
	while (input[j] && input[j] != '$')
		j++;
	if (input[j] == '$')
	{
		j++;
		while (input[j] && (ft_isalnum(input[j]) || input[j] == '_'))
			j++;
		if (j < rest)
		{
			*end_input = ft_substr(input, j, rest);
			if (!*end_input)
				return (NULL);
		}
	}
	else
	{
		while (input[j])
			j++;
		*end_input = ft_substr(input, j, rest);
	}
	printf("Rest = %s\n", *end_input);
	return (*end_input);
}

t_env	*compare_var_input(char *input, t_env *env)
{
	t_env	*temp;
	char	*name;

	name = find_name_var(input);
	temp = env;
	if (env == NULL)
		return (NULL);
	while (temp != NULL)
	{
		if (ft_strncmp(name, temp->name, ft_strlen(temp->name)) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}
char	*return_simple_var(char *input, t_env *env, int count)
{
	char	*valid_pars;
	t_env	*name;
	char	*rest_input;

	rest_input = NULL;
	valid_pars = NULL;
	int(i) = 0;
	if (input[i] != '\0')
	{
		while (input[i] != '\0' && input[i] != '$')
			i++;
		if (i != 0)
		{
			valid_pars = ft_substr(input, 0, i);
			if (input[i] == '$')
			{
				i++;
				name = compare_var_input(input, env);
				valid_pars = ft_strjoin(valid_pars, "\"");
				valid_pars = ft_strjoin(valid_pars, name->value);
				valid_pars = ft_strjoin(valid_pars, "\"");
				if (count > 1)
				{
					count--;
					return (return_parsing_heredoc(rest_input, env, count));
				}
				else if (ft_strncmp(find_rest(input, &rest_input), input,
						ft_strlen(input)) != 0)
					valid_pars = ft_strjoin(valid_pars, rest_input);
				else
					return (valid_pars);
			}
			printf("%s\n", valid_pars);
		}
		else
		{
			if (input[i] == '$')
			{
				i++;
				name = compare_var_input(input, env);
				valid_pars = ft_strjoin(name->value, "\"");
				valid_pars = ft_strjoin("\"", valid_pars);
				if (count > 1)
				{
					count--;
					return (return_parsing_heredoc(rest_input, env, count));
				}
				else if (ft_strncmp(find_rest(input, &rest_input), input,
						ft_strlen(input)) != 0)
					valid_pars = ft_strjoin(valid_pars, rest_input);
				else
					return (valid_pars);
			}
			printf("%s\n", valid_pars);
		}
	}
	return (valid_pars);
}

char	*return_parsing(char *input, t_env *env, int count)
{
	char	*valid_pars;
	t_env	*name;
	char	*rest_input;

	rest_input = NULL;
	valid_pars = NULL;
	int(i) = 0;
	if ((simple_quote(input) == -1))
	{
		valid_pars = input;
		printf("%s\n", valid_pars);
		return (valid_pars);
	}
	else if ((double_quote(input) == -1))
	{
		while (input[i] != '\0' && input[i] != '$')
			i++;
		if (i != 0)
		{
			valid_pars = ft_substr(input, 0, i);
			if (input[i] == '$')
			{
				i++;
				name = compare_var_input(input, env);
				valid_pars = ft_strjoin(valid_pars, name->value);
				if (count > 1)
				{
					count--;
					return (return_parsing_heredoc(rest_input, env, count));
				}
				else if (ft_strncmp(find_rest(input, &rest_input), input,
						ft_strlen(input)) != 0)
					valid_pars = ft_strjoin(valid_pars, rest_input);
				else
					return (valid_pars);
			}
		}
	}
	printf("%s\n", valid_pars);
	return (return_simple_var(input, env, count));
}

char	*return_parsing_heredoc(char *input, t_env *env, int count)
{
	char	*valid_pars;

	valid_pars = NULL;
	int(i) = 0;
	int(j) = 0;
	if (input[j] == '<' && input[j + 1] == '<')
	{
		valid_pars = input;
		return (valid_pars);
	}
	while (1)
	{
		i++;
		if ((input[i] == '<' && input[i + 1] == '<') || (input[i] == '\0'))
			break ;
	}
	if (input[i] == '<' && input[i + 1] == '<')
	{
		valid_pars = input;
	}
	else if ((input[j] != '<' && input[j + 1] != '<') || input[j] != '\0')
	{
		return (return_parsing(input, env, count));
	}
	return (valid_pars);
}
