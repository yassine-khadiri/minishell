int main(int argc , char **argv, char **env)
{
    char *str = "";
    char **sp = ft_split(str, ' ');
    char *str1 = "grep";
    char **sp1 = ft_split(str1, ' ');
    int fd[2];
    if(pipe(fd) == -1)
        return (1);
    int pid1 = fork();
    if(pid1 < 0)
        return (2);
    if (pid1 == 0)
    {

        dup2(fd[1], STDOUT_FILENO);
       
        close(fd[1]);
        execve("/bin/ls", sp, env);
    }
    int pid2 = fork();
    if(pid2 < 0)
        return (0);
    if (pid2 == 0)
        {
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);
            execve("/usr/bin/wc", sp1, env);
        }
        close(fd[0]);
        close(fd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    return (0);

}
