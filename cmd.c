/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ghab <zel-ghab@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 20:32:00 by zel-ghab          #+#    #+#             */
/*   Updated: 2025/06/26 20:25:21 by zel-ghab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	cmd2(int fd_outfile, char **argv, int *pipefd, char **envp)
{
	char	**cmd2;
	char	*full_path;

	cmd2 = ft_split(argv[3], ' ');
	if (!cmd2)
		exit(1);
	full_path = find_cmd_path(cmd2, envp);
	if (!full_path)
		return (free_split(&cmd2), close_all(fd_outfile, -1, pipefd), \
		ft_printf("%s: command not found\n", argv[3]), exit(1));
	if (dup2(pipefd[0], 0) == -1 || dup2(fd_outfile, 1) == -1)
		return (close_all(fd_outfile, -1, pipefd), free_split(&cmd2), \
		free(full_path), exit(1));
	close_all(fd_outfile, -1, pipefd);
	if (execve(full_path, cmd2, envp) == -1)
		return (free_split(&cmd2), free(full_path), exit(1));
	exit(0);
}

void	cmd1(int fd_infile, char **argv, int *pipefd, char **envp)
{
	char	**cmd1;
	char	*full_path;

	cmd1 = ft_split(argv[2], ' ');
	if (!cmd1)
		exit(1);
	full_path = find_cmd_path(cmd1, envp);
	if (!full_path)
		return (free_split(&cmd1), close_all(fd_infile, -1, pipefd), \
		ft_printf("%s: command not found\n", argv[2]), exit(1));
	if (dup2(fd_infile, 0) == -1 || dup2(pipefd[1], 1) == -1)
		return (close_all(fd_infile, -1, pipefd), free_split(&cmd1), \
		free(full_path), exit(1));
	close_all(fd_infile, -1, pipefd);
	if (execve(full_path, cmd1, envp) == -1)
		return (free_split(&cmd1), free(full_path), exit(1));
	exit(0);
}
