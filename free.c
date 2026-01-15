#include "includes.h"

void free_tokens(t_token *t)
{
    t_token *tmp;

    while (t)
    {
        tmp = t->next;
        free(t->value);
        free(t);
        t = tmp;
    }
}


void free_cmds(t_cmd *cmds)
{
    t_cmd *tmp;
    int i;

    while (cmds)
    {
        tmp = cmds->next;

        if (cmds->argv)
        {
            for (i = 0; cmds->argv[i]; i++)
                free(cmds->argv[i]);
            free(cmds->argv);
        }

        if (cmds->infile)
            free(cmds->infile);

        if (cmds->outfile)
            free(cmds->outfile);

        free(cmds);
        cmds = tmp;
    }
}
