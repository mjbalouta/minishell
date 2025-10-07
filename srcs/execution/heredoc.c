#include "minishell.h"

/**
 * @brief find last heredoc (used to store in the pipe only the output of this last one)
 * 
 * @param redir_list 
 * @return t_redir* last_heredoc 
 */
t_redir	*find_last_heredoc(t_redir *redir_list)
{
    t_redir	*last_heredoc;

    last_heredoc = NULL;
    while (redir_list)
    {
        if (redir_list->type == T_HEREDOC)
            last_heredoc = redir_list;
        redir_list = redir_list->next;
    }
    return (last_heredoc);
}
/**
 * @brief reads from the stdin and compares the line with the limiter(filename),
 * also calls the function to write the output of the last_heredoc to the pipe
 * 
 * @param redir_list 
 * @param last_heredoc 
 * @param heredoc_fd 
 */
void	read_heredoc(t_redir *redir_list, t_redir *last_heredoc, int *heredoc_fd)
{
    char	*line;

    line = NULL;

    if (redir_list->type == T_HEREDOC)
    {
        while (1)
        {
            write(STDOUT_FILENO, "> ", 2);
            line = get_next_line(0);
            if (ft_strlen(line) > 0)
                line[ft_strlen(line) - 1] = '\0';
            if (ft_strcmp(line, redir_list->filename) == 0)
            {
                free(line);
                return ;
            }
            if (redir_list == last_heredoc)
                write_inside_pipe(heredoc_fd, line);
            free(line);
        }
    }
}
/**
 * @brief handles heredoc input calling other useful functions - stores the read end of
 * the pipe in a variable for it to be the input of the command of that redirection
 * 
 * @param ms 
 */
void	handle_heredoc_input(t_shell *ms)
{
    char	*line;
    int		heredoc_fd[2];
    t_redir	*redir_list;
    t_redir	*last_heredoc;

    redir_list = ms->command->redirection;
    last_heredoc = find_last_heredoc(redir_list);
    line = NULL;
    redir_list = ms->command->redirection;
    if (last_heredoc && pipe(heredoc_fd) != 0)
        exit_shell(ms, 1);
    while (redir_list)
    {
        if (redir_list->type == T_HEREDOC)
            read_heredoc(redir_list, last_heredoc, heredoc_fd);
        redir_list = redir_list->next;
    }
    if (last_heredoc)
    {
        close(heredoc_fd[1]);
        ms->command->heredoc_fd = heredoc_fd[0];
    }
    get_next_line(-1);
}
