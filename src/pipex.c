#include "../includes/pipex.h"

char	**find_cmd_paths(char **env)
{
	char *all_paths;
	char **cmd_paths;

	while (ft_strncmp("PATH", *env, 4))
		env++;
	all_paths = *env + 5;
	cmd_paths = ft_split(all_paths, ':');
	if (!cmd_paths)
		return (NULL);
	return (cmd_paths);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex pipex;

	if (argc != 5)
	{
		write(2, "Error 1\n", 8);
		return (1);
	}
	pipex.fd_infile = open(argv[1], O_RDONLY);
	if (pipex.fd_infile < 0)
	{
		write(2, "Error 2\n", 8);
		return (1);
	}
	pipex.fd_outfile = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (pipex.fd_outfile < 0)
	{
		write(2, "Error 3\n", 8);
		return (1);
	}
	pipex.cmd_paths = find_cmd_paths(env);
	if (!pipex.cmd_paths)
	{
		write(2, "Error 4\n", 8);
		return (1);
	}
	if (pipe(pipex.end))
	{
		write(2, "Error 5\n", 8);
		return (1);
	}

	pipex.pid_id_first = fork();
	if (pipex.pid_id_first == 0)
		first_child(pipex, argv, env);

	if (pipex.pid_id_first != 0)
	{
		pipex.pid_id_second = fork();
		if (pipex.pid_id_second == 0)
			second_child(pipex, argv[3], env);
	}

	close(pipex.end[0]);
	close(pipex.end[1]);
	waitpid(pipex.pid_id_first, NULL, 0);
	waitpid(pipex.pid_id_second, NULL, 0);
}