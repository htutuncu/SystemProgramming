#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "jval.h"
#include "jrb.h"
#include "dllist.h"
#include "fields.h"

#define MAX_SIZE 1000

char *removeLeadingSpaces(char *str);

int compareJval(Jval j1, Jval j2);

int main(int argc, char **argv)
{

    if (argc != 4)
    { /* Checking if program called properly */
        fprintf(stderr, "Incorrect parameter count\n");
        exit(EXIT_FAILURE);
    }

    JRB jrb = make_jrb();

    const char *filename = ".kilit";
    //FILE *fp = fopen(filename, "rb");

    IS is; /* Fields struct for reading input */
    IS kilit;
    kilit = new_inputstruct(filename);
    is = new_inputstruct(argv[2]);
    if (is == NULL)
    {
        perror(argv[2]);
        exit(1);
    }
    if (kilit == NULL)
    {
        perror(filename);
        exit(1);
    }

    FILE *output = fopen(argv[3], "w+");

    int i;
    while (get_line(kilit) >= 0)
    {
        for (i = 0; i < kilit->NF; i++)
        {
            if (strcmp(kilit->fields[i], "{") != 0 && strcmp(kilit->fields[i], "}") != 0)
            {

                char *key = strdup(kilit->fields[i]);
                int k;
                char *newKey = (char *)malloc(strlen(key) * sizeof(char));
                for (k = 0; k < strlen(key) - 3; k++)
                {
                    newKey[k] = key[k + 1];
                }
                char *value = strdup(kilit->fields[i + 1]);
                char *newValue = (char *)malloc(strlen(value) * sizeof(char));
                for (k = 0; k < strlen(value) - 2; k++)
                {
                    newValue[k] = value[k + 1];
                }
                if (newValue[strlen(newValue) - 1] == '\"')
                    newValue[strlen(newValue) - 1] = '\0';
                else
                {
                    newValue[strlen(newValue)] = '\0';
                }

                Jval myJval = (Jval)malloc(sizeof(Jval));
                myJval = new_jval_v(strdup(newValue));

                Jval myJval2 = (Jval)malloc(sizeof(Jval));
                myJval2 = new_jval_s(strdup(newKey));

                if (strcmp(argv[1], "-e") == 0)
                {
                    (void)jrb_insert_gen(jrb, myJval2, myJval, compareJval);
                }

                else if (strcmp(argv[1], "-d") == 0)
                {

                    (void)jrb_insert_gen(jrb, myJval, myJval2, compareJval);
                }

                else
                {
                    fprintf(stderr, "Wrong parameter/n");
                    exit(EXIT_FAILURE);
                }

                free(newKey);
                free(newValue);

                i++;
            }
        }
    }

    if (strcmp(argv[1], "-e") == 0)
    {
        while (get_line(is) >= 0)
        {
            for (i = 0; i < is->NF; i++)
            {
                if (jrb_find_str(jrb, is->fields[i]) != NULL)
                    fprintf(output, "%s ", jrb_find_str(jrb, is->fields[i])->val);
                else
                    fprintf(output, "%s ", is->fields[i]);
            }
        }
    }
    else
    {
        while (get_line(is) >= 0)
        {
            for (i = 0; i < is->NF; i++)
            {
                if (jrb_find_str(jrb, is->fields[i]) != NULL)
                    fprintf(output, "%s ", jrb_find_str(jrb, is->fields[i])->val);
                else
                    fprintf(output, "%s ", is->fields[i]);
            }
        }
    }

    jettison_inputstruct(kilit);
    jettison_inputstruct(is);
    fclose(output);

    return 0;
}

char *removeLeadingSpaces(char *str)
{
    static char str1[1000];
    int count = 0, j, k;

    /* Iterate String until last
       leading space character  */
    while (str[count] == ' ')
    {
        count++;
    }

    /* Putting string into another
       string variable after
       removing leading white spaces */
    for (j = count, k = 0;
         str[j] != '\0'; j++, k++)
    {
        str1[k] = str[j];
    }
    str1[k] = '\0';

    return str1;
}

int compareJval(Jval j1, Jval j2)
{

    return strcmp(j1.s, j2.s);
}
