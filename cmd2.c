/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ghab <zel-ghab@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 20:32:08 by zel-ghab          #+#    #+#             */
/*   Updated: 2025/06/23 15:07:45 by zel-ghab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	cmd2(int fd_outfile, char **argv, int *pipefd, char **envp)
{
	char	**cmd2;
	char	*full_path;

	// REDIRIGER LES ENTREE ET SORTIE
	dup2(pipefd[0], 0);
	dup2(fd_outfile, 1);
	// FERMER LES FD INUTILES
	close(fd_outfile);
	close(pipefd[0]);
	close(pipefd[1]);
	// PARSER CMD2
	cmd2 = ft_split(argv[3], ' ');
	if (!cmd2)
		return (1);
	// FIND LE PATH DE CMD2
	full_path = find_cmd_path(cmd2, envp);
	if (!full_path)
		return (perror("⚠️ Path error !"), 1);
	// EXECVE
	if (execve(full_path, cmd2, envp) == -1)
		return (perror("⚠️ Path error !"), 1);
	return (0);
}
