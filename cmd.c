/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ghab <zel-ghab@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 20:32:00 by zel-ghab          #+#    #+#             */
/*   Updated: 2025/06/26 18:07:30 by zel-ghab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	cmd2(int fd_outfile, char **argv, int *pipefd, char **envp)
{
	char	**cmd2;
	char	*full_path;

	dup2(pipefd[0], 0);
	dup2(fd_outfile, 1);
	close(fd_outfile);
	close(pipefd[0]);
	close(pipefd[1]);
	cmd2 = ft_split(argv[3], ' ');
	if (!cmd2)
		exit(1);
	full_path = find_cmd_path(cmd2, envp);
	if (!full_path)
		return (free_split(&cmd2), perror("⚠️ Path error !"), exit(1));
	if (execve(full_path, cmd2, envp) == -1)
		return (free_split(&cmd2), free(full_path), \
		perror("⚠️ Path error !"), exit(1));
	exit(0);
}

void	cmd1(int fd_infile, char **argv, int *pipefd, char **envp)
{
	char	**cmd1;
	char	*full_path;

	dup2(fd_infile, 0);
	dup2(pipefd[1], 1);
	close(fd_infile);
	close(pipefd[0]);
	close(pipefd[1]);
	cmd1 = ft_split(argv[2], ' ');
	if (!cmd1)
		exit(1);
	full_path = find_cmd_path(cmd1, envp);
	if (!full_path)
		return (free_split(&cmd1), \
		perror("⚠️ Path error !"), exit(1));
	if (execve(full_path, cmd1, envp) == -1)
		return (free_split(&cmd1), free(full_path), \
		perror("⚠️ Execve error !"), exit(1));
	exit(0);
}
