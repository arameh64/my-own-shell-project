#include "includes.h"

t_history *history_tail(t_history *h)
{
    if (!h)
        return NULL;
    while (h->next)
        h = h->next;
    return h;
}

void add_history(t_history **head, char *line)
{
    t_history *new;
    t_history *tail;

    if (!head || !line || !*line)
        return;

    new = malloc(sizeof(t_history));
    if (!new)
        return;

    new->cmd = strdup(line);
    if (!new->cmd)
    {
        free(new);
        return;
    }

    new->prev = NULL;
    new->next = NULL;

    if (!*head)
    {
        *head = new;
        return;
    }

    tail = history_tail(*head);
    tail->next = new;
    new->prev = tail;
}
