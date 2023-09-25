/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlhafi <youlhafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 08:49:44 by youlhafi          #+#    #+#             */
/*   Updated: 2023/08/23 10:42:15 by youlhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_fd(t_cmd *cmds, t_pip *p, char *save, char *line)
{
	int	fd_tmp;

	(void)p;
	fd_tmp = open("/tmp/tmp_file", O_CREAT | O_RDWR | O_TRUNC, 0644);
	write(fd_tmp, save, ft_strlen(save));
	close(fd_tmp);
	free(save);
	cmds->in = open("/tmp/tmp_file", O_RDONLY);
	if (cmds->in < 0)
		unlink("/tmp/tmp_file");
	if (line)
		free(line);
}

void	handle_her_doc(int sign)
{
	if (sign == SIGINT)
	{
		g_global.herdoc = 1;
		g_global.var = dup(0);
		close(0);
	}
}

void	break_read(t_pip *p, char *save)
{
	p->sign_in = 1;
	dup2(g_global.var, 0);
	close(g_global.var);
	if (save)
		free(save);
}

char	*expand(char *save, t_pip *p)
{
	if (ft_strchr(save, '$')
		&& (!ft_strnstr(save, "$?", ft_strlen(save))))
	{
		save = split_str(save, p->envp);
	}
	else if (ft_strnstr(save, "$?", ft_strlen(save)))
	{
		save = ft_status(save);
	}
	save = ft_strjoin_get(save, "\n");
	return (save);
}

void	ft_read_here_doc(t_cmd *cmds, t_pip *p, char *limter)
{
	char	*line;
	char	*save;

	line = NULL;
	save = NULL;
	signal(SIGINT, handle_her_doc);
	while (1)
	{
		line = readline(">");
		if (line == NULL)
		{
			if (g_global.herdoc == 1)
			{
				break_read(p, save);
				return ;
			}
			break ;
		}
		if (!ft_strcmp(limter, line))
			break ;
		save = ft_strjoin_get(save, line);
		save = expand(save, p);
		free(line);
	}
	write_fd(cmds, p, save, line);
}
