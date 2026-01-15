#include "includes.h"

#define PROMPT "ashell> "
#define PROMPT_LEN 8

static void redraw_prompt(const char *buf, int len)
{
    write(STDOUT_FILENO, "\r\033[K", 4);          // go start + clear line
    write(STDOUT_FILENO, PROMPT, PROMPT_LEN);    // print prompt
    if (len > 0)
        write(STDOUT_FILENO, buf, len);           // print buffer
}

char *reader(t_history **history)
{
    t_history *cursor = NULL;
    char buffer[4096];
    int len = 0;
    char c;

    buffer[0] = 0;

    redraw_prompt(buffer, len);

    while (1)
    {
        if (read(STDIN_FILENO, &c, 1) != 1)
            return NULL;

        /* ENTER */
        if (c == '\n' || c == '\r')
        {
            write(STDOUT_FILENO, "\n", 1);
            break;
        }

        /* BACKSPACE */
        if (c == 127 || c == 8)
        {
            if (len > 0)
            {
                len--;
                buffer[len] = 0;
                redraw_prompt(buffer, len);
            }
            continue;
        }

        /* ESC (arrow keys) */
        if (c == 27)
        {
            char a, b;

            if (read(STDIN_FILENO, &a, 1) != 1)
                continue;

            if (a != '[' && a != 'O')
                continue;

            if (read(STDIN_FILENO, &b, 1) != 1)
                continue;

            t_history *tail = history_tail(*history);

            /* UP */
            if (b == 'A')
            {
                if (!tail)
                    continue;

                if (cursor == NULL)
                    cursor = tail;
                else if (cursor->prev)
                    cursor = cursor->prev;

                strncpy(buffer, cursor->cmd, sizeof(buffer) - 1);
                buffer[sizeof(buffer) - 1] = 0;
                len = (int)strlen(buffer);
                redraw_prompt(buffer, len);
            }
            /* DOWN */
            else if (b == 'B')
            {
                if (cursor && cursor->next)
                    cursor = cursor->next;
                else
                    cursor = NULL;

                if (cursor)
                {
                    strncpy(buffer, cursor->cmd, sizeof(buffer) - 1);
                    buffer[sizeof(buffer) - 1] = 0;
                    len = (int)strlen(buffer);
                }
                else
                {
                    len = 0;
                    buffer[0] = 0;
                }

                redraw_prompt(buffer, len);
            }

            continue;
        }

        /* ignore other control chars */
        if ((unsigned char)c < 32)
            continue;

        /* normal characters */
        if (len < (int)sizeof(buffer) - 1)
        {
            buffer[len++] = c;
            buffer[len] = 0;
            cursor = NULL;
            write(STDOUT_FILENO, &c, 1);
        }
    }

    return strdup(buffer);
}
