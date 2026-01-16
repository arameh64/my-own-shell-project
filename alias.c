#include "includes.h"

t_alias *g_aliases = NULL;

t_alias *alias_find(const char * name)
{
    t_alias *cur = g_aliases;
     while ( cur )
     {
        if ( strcmp(cur->name , name ) == 0 )
        {
            return cur;
        }
     }

     return NULL ; 
     
}

void alias_set(const char * name , const char * value)
{
    t_alias * existing = alias_find(name);
    
    if(existing)
    {
        free(existing->value);
        existing->value = strdup(value);
        return;
    }
    
    t_alias *new = malloc(sizeof(t_alias));
    new->name = strdup(name);
    new->value = strdup(value);
    new->next = g_aliases;
    g_aliases = new;
    
}

void alias_unset(const char *name)
{
    t_alias *cur = g_aliases;
    t_alias *prev = NULL;

    while (cur)
    {
        if (strcmp(cur->name, name) == 0)
        {
            if (prev)
                prev->next = cur->next;
            else
                g_aliases = cur->next;

            free(cur->name);
            free(cur->value);
            free(cur);
            return;
        }
        prev = cur;
        cur = cur->next;
    }
}

void alias_print_all(void)
{
    t_alias *cur = g_aliases;

    while (cur)
    {
        printf("alias %s='%s'\n", cur->name, cur->value);
        cur = cur->next;
    }
}

void expand_aliases(t_token **tokens)
{
    if (!tokens || !*tokens)
        return;

    t_token *first = *tokens;

    if (first->type != TOK_WORD)
        return;

    t_alias *a = alias_find(first->value);
    if (!a)
        return;

    t_token *alias_tokens = tokenize(a->value);

    t_token *last = alias_tokens;
    while (last->next)
        last = last->next;

    last->next = first->next;

    free(first->value);
    free(first);
    *tokens = alias_tokens;
}


