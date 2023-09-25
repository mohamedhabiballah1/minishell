/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlhafi <youlhafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 12:08:14 by mhabib-a          #+#    #+#             */
/*   Updated: 2023/08/22 20:06:19 by youlhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(char *variable, char **env)
{
	int	variable_length;
	int	i;

	variable_length = ft_strlen(variable);
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(variable, env[i], variable_length) == 0
			&& env[i][variable_length] == '=')
		{
			free(variable);
			return (ft_strdup(&env[i][variable_length + 1]));
		}
		i++;
	}
	free(variable);
	return (NULL);
}

void	expanded(char *str, char **env, t_list **lst)
{
	int		i;
	int		j;
	char	**dst;

	i = 0;
	j = 0;
	dst = malloc(sizeof(char *) * (calc_word(str) + 1));
	if (!dst)
		return ;
	i = 0;
	while (str[i])
	{
		if (is_quote(str[i]))
			dst[j++] = ret_quote(str, &i);
		else
			dst[j++] = ret_arg(str, &i);
	}
	dst[j] = NULL;
	j = 0;
	while (dst[j])
	{
		dst[j] = replace_env_variables(dst[j], env);
		j++;
	}
	str_handle(dst, lst);
}

char	*replace(const char *input, size_t *i, char **env, char *res)
{
	char	*variable;
	char	*value;
	char	*temp;
	int		j;

	j = 0;
	if (!input[*i + 1] || is_quote(input[*i + 1]))
		res = single_dollar(input, res, i);
	else
	{
		j = (*i) + 1;
		while (input[j] != '\0' && (ft_isalnum(input[j]) || input[j] == '_'))
			j++;
		variable = ft_substr(input, (*i) + 1, j - (*i) - 1);
		value = get_env_value(variable, env);
		if (value != NULL)
		{
			temp = ft_strjoin(res, value);
			free(value);
			free(res);
			res = temp;
		}
		(*i) = j;
	}
	return (res);
}

char	*replace_env_variables(const char *input, char **env)
{
	size_t	i;
	char	*result;
	char	*temp;

	if (input == NULL)
		return (NULL);
	result = malloc((1) * sizeof(char));
	if (!result)
		return (NULL);
	result[0] = '\0';
	i = 0;
	while (i < ft_strlen(input))
	{
		if (input[i] == '$' && input[0] != SINGLE_QHOT)
			result = replace(input, &i, env, result);
		else
		{
			temp = ft_strjoinch(result, input[i++]);
			free(result);
			result = temp;
		}
	}
	free((char *)input);
	return (result);
}
