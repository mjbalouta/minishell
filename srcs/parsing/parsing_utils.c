#include "minishell.h"

void ft_cmd_lstclear(t_command **lst)
{
    t_command *current;
    t_command *next;

    if (!lst || !*lst)
        return;

    current = *lst;
    while (current)
    {
        next = current->next;
        if (current->args)
            free_char_array(current->args);
        if (current->comm_path)
            free(current->comm_path);
        if (current->redirection)
            free_redirection_list(current->redirection);
        free(current);
        current = next;
    }
    *lst = NULL;
}

void free_redirection_list(t_redir *redir)
{
    t_redir *current;
    t_redir *next;

    current = redir;
    while (current)
    {
        next = current->next;
        if (current->filename)
            free(current->filename);
        free(current);
        current = next;
    }
}
