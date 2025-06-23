/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ghab <zel-ghab@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 20:32:00 by zel-ghab          #+#    #+#             */
/*   Updated: 2025/06/23 22:08:17 by zel-ghab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	cmd2(int fd_outfile, char **argv, int *pipefd, char **envp)
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
		exit(1);
	// FIND LE PATH DE CMD2
	full_path = find_cmd_path(cmd2, envp);
	if (!full_path)
		return (free_split(&cmd2), perror("⚠️ Path error !"), exit(1));
	// EXECVE
	if (execve(full_path, cmd2, envp) == -1)
		return (free_split(&cmd2), free(full_path), perror("⚠️ Path error !"), exit(1));
	// POUR SORTIR DU PROCESS
	exit(0);
}

void	cmd1(int fd_infile, char **argv, int *pipefd, char **envp)
{
	char	**cmd1;
	char	*full_path;

	// PERMET DE CONNECTER MES FICHIERS A L'ENTREE OU A LA SORTIE
	dup2(fd_infile, 0);
	dup2(pipefd[1], 1);
	// FERMETURE DES FD INUTILES
	close(fd_infile);
	close(pipefd[0]);
	close(pipefd[1]);
	// PARSER CMD1
	cmd1 = ft_split(argv[2], ' ');
	if (!cmd1)
		exit(1);
	// FIND LE PATH DU CMD
	full_path = find_cmd_path(cmd1, envp);
	if (!full_path)
		return (free_split(&cmd1), perror("⚠️ Path error !"), exit(1));
	// EXECVE
	if (execve(full_path, cmd1, envp) == -1)
		return (free_split(&cmd1), free(full_path), perror("⚠️ Execve error !"), exit(1));
	// POUR SORTIR DU PROCESS
	exit(0);
}
