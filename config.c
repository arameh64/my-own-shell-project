#include "includes.h"
 
//      config file path    =      ~/.ashrc

void load_rc(t_history **history)
{
    char path[PATH_MAX];
    char *home = getenv("HOME");
    FILE *f;
    char *line = NULL;
    size_t len = 0;

    if (!home)
        return;

    snprintf(path, sizeof(path), "%s/.ashrc", home);

    f = fopen(path, "r");
    if (!f)
        return;

    while (getline(&line, &len, f) != -1)
    {
        // ignore empty/comment lines
        if (line[0] == '\n' || line[0] == '#')
        {
            continue;
        }

        t_token *toks = tokenize(line);
        if (!toks)
            continue;

        t_cmd *cmds = parse_tokens(toks);
        if (!cmds)
        {
            free_tokens(toks);
            continue;
        }

        expand_cmd_vars(cmds);
        execute_commands(cmds, history);

        free_cmds(cmds);
        free_tokens(toks);

        add_history(history, line);
    }

    free(line);
    fclose(f);
}

void process_line(char *raw, t_history **history)
{
    t_token *toks;
    t_cmd   *cmds;

    if (!raw)
        return;

    raw[strcspn(raw, "\n")] = 0;

    if (!*raw)
        return;

    add_history(history, raw);

    toks = tokenize(raw);
    if (!toks)
        return;

    cmds = parse_tokens(toks);
    if (!cmds)
    {
        free_tokens(toks);
        return;
    }

    execute_commands(cmds, history);

    free_cmds(cmds);
    free_tokens(toks);
}






