#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libfdr/jval.h"
#include "libfdr/jrb.h"
#include "libfdr/dllist.h"
#include "libfdr/fields.h"

#define MAX_SIZE 1000

char *removeLeadingSpaces(char *str);

void removeChar(char *s, char c);

int compareJval(Jval j1, Jval j2);

int main(int argc, char** argv)
{

    if(argc != 4){  /* Checking if program called properly */
        fprintf(stderr, "Incorrect parameter count\n");
        exit(EXIT_FAILURE);
    } 

    JRB jrb = make_jrb();

    const char *filename = ".kilit";
    FILE *fp = fopen(filename, "rb");
    /*  FILE * input = fopen(argv[2], "r");  */

    IS is;      /* Fields struct for reading input */
    is = new_inputstruct(argv[2]);

    FILE * output = fopen(argv[3], "w+");

    if (!fp)
        perror(filename), exit(1);

    int bufferLength = MAX_SIZE;
    char buffer[bufferLength];
    char *file[MAX_SIZE];
    int i = 0;
    for (i = 0; i < MAX_SIZE; i++)
        file[i] = (char *)malloc(MAX_SIZE * sizeof(char));

    i = 0;
    while (fgets(buffer, bufferLength, fp))
    {
        strcpy(file[i++], buffer);
    }

    int j;
    
    for (j = 1; j < i - 1; j++)
    {
        file[j] = removeLeadingSpaces(file[j]);
        removeChar(file[j], ',');

        char *token = strtok(file[j], ":");

        /* Keep printing tokens while one of the
           delimiters present in str[]. */

        char *key = strdup(token);
        
        
        token = strtok(NULL, ":");

        char *value = strdup(token);
        /* printf("%s\n", token);   */
        token = strtok(NULL, ":");

        value = removeLeadingSpaces(value);

        /*printf("%s\n", key);
        printf("%s\n",value);*/

        Jval myJval = (Jval)malloc(sizeof(Jval));
        myJval = new_jval_v(strdup(value));

        Jval myJval2 = (Jval)malloc(sizeof(Jval));
        myJval2 = new_jval_v(strdup(key));

        if(strcmp(argv[1], "-e")==0){
            (void) jrb_insert_gen(jrb, myJval2, myJval, compareJval);
        }

        else if(strcmp(argv[1], "-d")== 0){

            (void) jrb_insert_gen(jrb, myJval, myJval2, compareJval);
        }

        else{
            fprintf(stderr, "Wrong parameter/n");
            exit(EXIT_FAILURE);
        }
    }
    /*free(key);
        free(value);
        free(token);*/
    
        
        
    JRB bn;
    jrb_traverse(bn, jrb) {
        printf("%s", jval_s(bn->val));
        printf("%s", jval_s(bn->key));
    }


    fclose(fp);

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

void removeChar(char *s, char c)
{

    int j, n = strlen(s);
    for (int i = j = 0; i < n; i++)
        if (s[i] != c)
            s[j++] = s[i];

    s[j] = '\0';
}

int compareJval(Jval j1, Jval j2){

    return strcmp(j1.s, j2.s);
}