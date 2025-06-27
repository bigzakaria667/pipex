/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ghab <zel-ghab@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:15:48 by zel-ghab          #+#    #+#             */
/*   Updated: 2025/06/27 17:29:24 by zel-ghab         ###   ########.fr       */
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
	t_fd	fd;
	int		pid;
	int		pid2;

	fd.infile = read_infile(argv[1]);
	fd.outfile = write_outfile(argv[4], fd.infile);
	if (pipe(fd.pipefd) == -1)
		return (close_all(fd), perror("⚠️ Pipe error !"), exit(1));
	pid = fork();
	if (pid == -1)
		return (close_all(fd), perror("⚠️ Fork error !"), exit(1));
	if (pid == 0)
		cmd1(fd, argv, envp);
	waitpid(pid, NULL, 0);
	pid2 = fork();
	if (pid2 == -1)
		return (close_all(fd), perror("⚠️ Fork error !"), exit(1));
	if (pid2 == 0)
		cmd2(fd, argv, envp);
	close_all(fd);
	waitpid(pid2, NULL, 0);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
		return (1);
	instructions(argv, envp);
	return (0);
}
