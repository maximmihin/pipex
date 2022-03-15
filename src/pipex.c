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
		return (error1("Error : less then 4 arg\n"));
	pipex.fd_infile = open(argv[1], O_RDONLY);
	if (pipex.fd_infile < 0)
		return (error1("Error : failed to open infile\n"));
	pipex.fd_outfile = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (pipex.fd_outfile < 0)
		return (error1("Error : failed to open outfile\n"));
	pipex.cmd_paths = find_cmd_paths(env);
	if (!pipex.cmd_paths)
		return (error1("Error : failed malloc (cmd_paths)\n"));
	if (pipe(pipex.end))
		return (error1("Error : failed to create pipe\n"));

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