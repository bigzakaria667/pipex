/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ghab <zel-ghab@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:15:48 by zel-ghab          #+#    #+#             */
/*   Updated: 2025/06/17 14:46:46 by zel-ghab         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	int	fd_infile;
	int	fd_outfile;
	int	pipefd[2];
	pid_t	pid;
	char	*path;
	char	**dirs;
	char	*full_path;
	char	*slash_cmd;
	int	i;

	// GET LE PATH
	i = 0;
	if (argc != 5)
		return (1);
	else
	{
		// LECTURE ET ECRITURE
		fd_infile = read_infile(argv[1]);
		fd_outfile = write_outfile(argv[4]);
		if (fd_infile == -1 || fd_outfile == -1)
			return (1);
		// VERIF DU PIPE
		if (pipe(pipefd) == -1)
			return (perror("⚠️ Pipe error !") ,1);
		// CREATION DU FORK
		pid = fork();
		if (pid == -1)
			return (perror("⚠️ Fork error !"), 1);
		// PERMET DE CONNECTER MES FICHIERS A L'ENTREE OU LA SORTIE
		if (pid == 0)
		{
			// CMD1
			dup2(fd_infile, 0);
			dup2(pipefd[1], 1);
			// FERMETURE DES FD INUTILES
			close(fd_infile);
			close(pipefd[0]);
			close(pipefd[1]);
			// PARSER CMD1
			ft_split(argv[2], ' ');
			// TROUVER LE PATH ET L'EMPLACEMENT DU CMD
			path = getenv("PATH");
			dirs = ft_split(path. ':');
			slash_cmd = ft_strjoin("/", cmd);
			full_path = ft_strjoin(dirs[i], slash_cmd);
		}
		else
			// CMD2
	}
	return (0);
}
