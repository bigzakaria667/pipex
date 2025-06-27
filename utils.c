/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ghab <zel-ghab@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 20:32:00 by zel-ghab          #+#    #+#             */
/*   Updated: 2025/06/27 17:20:20 by zel-ghab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_all(t_fd fd)
{
	if (fd.infile >= 0)
		close(fd.infile);
	if (fd.outfile >= 0)
		close(fd.outfile);
	if (fd.pipefd)
	{
		close(fd.pipefd[0]);
		close(fd.pipefd[1]);
	}
}

void	free_split(char ***split)
{
	int	i;

	i = 0;
	while ((*split) && (*split)[i])
	{
		free((*split)[i]);
		(*split)[i] = NULL;
		i++;
	}
	free(*split);
	*split = NULL;
}

char	*get_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*find_cmd_path(char **cmd, char **envp)
{
	char	*path;
	char	*slash_cmd;
	char	**dirs;
	char	*full_path;
	int		i;

	i = 0;
	path = get_path(envp);
	dirs = ft_split(path, ':');
	while (dirs[i])
	{
		slash_cmd = ft_strjoin("/", cmd[0]);
		if (!slash_cmd)
			return (free_split(&dirs), NULL);
		full_path = ft_strjoin(dirs[i], slash_cmd);
		if (!full_path)
			return (free_split(&dirs), free(slash_cmd), NULL);
		if (access(full_path, X_OK) == 0)
			return (free_split(&dirs), free(slash_cmd), full_path);
		free(slash_cmd);
		free(full_path);
		i++;
	}
	return (free_split(&dirs), NULL);
}
