/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ghab <zel-ghab@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:15:48 by zel-ghab          #+#    #+#             */
/*   Updated: 2025/06/21 19:13:16 by zel-ghab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	read_infile(char *s)
{
	int	fd;

	fd = open(s, O_RDONLY);
	if (fd < 0)
		return (perror("⚠️ Open error !"), -1);
	return (fd);
}

int	write_outfile(char *s)
{
	int	fd;

	// 0644 = PERM ONLY PROPRIO
	fd = open(s, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (perror("⚠️ Write error !"), -1);
	return (fd);
}

int	instructions(char **argv, char **envp)
{
	int	fd_infile;
	int	fd_outfile;
	int	pipefd[2];
	pid_t	pid;
	pid_t	pid2;

	// LECTURE ET ECRITURE
	fd_infile = read_infile(argv[1]);
	fd_outfile = write_outfile(argv[4]);
	if (fd_infile == -1 || fd_outfile == -1)
		return (1);
	// VERIF DU PIPE
	if (pipe(pipefd) == -1)
		return (perror("⚠️ Pipe error !"), 1);
	// CREATION DU FORK
	pid = fork();
	if (pid == -1)
		return (perror("⚠️ Fork error !"), 1);
	// CHILD = CMD1
	if (pid == 0)
	{
		if (cmd1(fd_infile, argv, pipefd, envp) == 1)
			return (1);
	}
	// PARENT = CMD2
	else
	{
		pid2 = fork();
		if (pid == -1)
			return (perror("⚠️ Fork error !"), 1);
		if (pid == 0)
			cmd2(fd_outfile, argv, pipefd, envp);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
		return (1);
	if (instructions(argv, envp) == 1)
		return (1);
	return (0);
}
