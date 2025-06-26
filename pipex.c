/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ghab <zel-ghab@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:15:48 by zel-ghab          #+#    #+#             */
/*   Updated: 2025/06/26 20:53:19 by zel-ghab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	read_infile(char *s)
{
	int	fd;

	fd = open(s, O_RDONLY);
	if (fd < 0)
		return (perror("pipex"), exit(1), -1);
	return (fd);
}

int	write_outfile(char *s, int fd_infile)
{
	int	fd;

	fd = open(s, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (close(fd_infile), perror("⚠️ Write error !"), exit(1), -1);
	return (fd);
}

void	instructions(char **argv, char **envp)
{
	int	fd_infile;
	int	fd_outfile;
	int	pipefd[2];
	int	pid;
	int	pid2;

	fd_infile = read_infile(argv[1]);
	fd_outfile = write_outfile(argv[4], fd_infile);
	if (pipe(pipefd) == -1)
		return (close_all(fd_infile, fd_outfile, pipefd), \
		perror("⚠️ Pipe error !"), exit(1));
	pid = fork();
	if (pid == -1)
		return (close_all(fd_infile, fd_outfile, pipefd), \
		perror("⚠️ Fork error !"), exit(1));
	if (pid == 0)
		cmd1(fd_infile, argv, pipefd, envp);
	waitpid(pid, NULL, 0);
	pid2 = fork();
	if (pid2 == -1)
		return (close_all(fd_infile, fd_outfile, pipefd), \
		perror("⚠️ Fork error !"), exit(1));
	if (pid2 == 0)
		cmd2(fd_outfile, argv, pipefd, envp);
	close_all(fd_infile, fd_outfile, pipefd);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
		return (1);
	instructions(argv, envp);
	return (0);
}
