/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlhafi <youlhafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 09:30:22 by mhabib-a          #+#    #+#             */
/*   Updated: 2023/08/22 19:57:02 by youlhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_str(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
		free(str[i++]);
	free(str);
}

void	ft_free_token(t_list *token)
{
	t_list	*tmp;

	while (token)
	{
		tmp = token;
		token = token->next;
		free(tmp->content);
		free(tmp);
	}
}

void	ft_free_list(t_cmd *cmd_list)
{
	t_cmd	*tmp;

	while (cmd_list)
	{
		tmp = cmd_list->next;
		if (cmd_list->cmd)
			free(cmd_list->cmd);
		if (cmd_list->args)
			ft_free_str(cmd_list->args);
		if (cmd_list->files)
			ft_free_str(cmd_list->files);
		if (cmd_list->type)
			ft_free_str(cmd_list->type);
		if (cmd_list->type_file)
			ft_free_str(cmd_list->type_file);
		if (cmd_list->herdoc_lim)
			free(cmd_list->herdoc_lim);
		free(cmd_list);
		cmd_list = tmp;
	}
}

void	ft_closefd(t_cmd *cmds, int i)
{
	t_cmd	*tmp;

	tmp = cmds;
	while (tmp)
	{
		if (tmp->i != i)
		{
			if (tmp->pipe_in != 0)
				close(tmp->pipe_in);
			if (tmp->pipe_out != 0)
				close(tmp->pipe_out);
		}
		tmp = tmp->next;
	}
}
