#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include "fileregex.h"
#include <sys/time.h>
#include <inttypes.h>
#include <ctype.h>
#include "colors.h"

int sequenceFileType(char *filename)
{
    regex_t r;
    const char * regex_text;
    regex_text = "[^\\s]+(.*?)\\.(txt|sec)$";
    compile_regex (& r, regex_text);
    int file_valid = match_regex (& r, filename);
    return file_valid;
}

int checkIfFileExists(char * filePath)
{
    int is_valid;
    if( access( filePath, F_OK ) == 0 ) {
        printf("%sOk file %s exists %s\n", MAG, filePath, RESET);
        is_valid = 1;

        int is_valid_file_type = sequenceFileType(filePath);
        if(is_valid_file_type == 0) {
            printf("File type is invalid please enter txt or sec file. \n");
            is_valid = 0;
        }
    } else {
        printf("File %s not found . \n", filePath);
        is_valid =  0;
    }
    return is_valid;
}

int get_path_from_user(char ** filePath, char * message)
{
    char *v = (char*) malloc(128 * sizeof(char));
    printf("%s",message);
    scanf("%s", v);

    while (checkIfFileExists(v) == 0)
    {
        printf("%s",message);
        scanf("%s",v);
    }
    *filePath = v;

    return 1;

}

void extract_sequence(char * filename, char ** sequence) {
    char *buffer = NULL;
    int string_size, read_size;
    FILE *handler = fopen(filename, "r");

    if (handler)
    {
        // Seek the last byte of the file
        fseek(handler, 0, SEEK_END);
        // Offset from the first to the last byte, or in other words, filesize
        string_size = ftell(handler);
        // go back to the start of the file
        rewind(handler);

        // Allocate a string that can hold it all
        buffer = (char*) malloc(sizeof(char) * (string_size + 1) );

        // Read it all in one operation
        read_size = fread(buffer, sizeof(char), string_size, handler);

        // fread doesn't set it so put a \0 in the last position
        // and buffer is now officially a string
        buffer[string_size] = '\0';

        if (string_size != read_size)
        {
            // Something went wrong, throw away the memory and set
            // the buffer to NULL
            free(buffer);
            buffer = NULL;
        }

        // Always remember to close the file.
        fclose(handler);
    }
    *sequence = buffer;

}

int save_sequence(char * data, char * filePath, int max_line_length) {
    char *filename = filePath;
    // open the file for writing

    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error opening the file %s", filename);
        return -1;
    }

    if(max_line_length > 0)
    {
        int i,j =0;
        for(i = 0; i < strlen(data) && data[i] != '\0'; ++i)
        {

            if(j < max_line_length || i == 0) {
                j++;
                printf("%c", data[i]);
                fprintf(fp, "%c", data[i]);
            } else {

                if( i > 0 && j == max_line_length) {
                    fputs("\n", fp);
                }
                j = 0;
            }
        }
    } else{
        fputs(data, fp);
    }

    // close the file
    fclose(fp);
    /* Success message */
    printf("File created and saved successfully. :) \n");
    return 1;
}

char * replaceWord(const char* s, const char* oldW, const char* newW)
{
    char* result;
    int i, cnt = 0;
    int newWlen = strlen(newW);
    int oldWlen = strlen(oldW);

    // Counting the number of times old word
    // occur in the string
    for (i = 0; s[i] != '\0'; i++) {
        if (strstr(&s[i], oldW) == &s[i]) {
            cnt++;

            // Jumping to index after the old word.
            i += oldWlen - 1;
        }
    }

    // Making new string of enough length
    result = (char*)malloc(i + cnt * (newWlen - oldWlen) + 1);

    i = 0;
    while (*s) {
        // compare the substring with the result
        if (strstr(s, oldW) == s) {
            strcpy(&result[i], newW);
            i += newWlen;
            s += oldWlen;
        }
        else
            result[i++] = *s++;
    }

    result[i] = '\0';
    return result;
}

long int timeInMilliseconds() {
    struct timeval te;
    gettimeofday(&te, NULL); // get current time
    long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000; // calculate milliseconds
    return milliseconds;
}

int in_array(char *array[], int size, char * lookfor)
{
    int i;
    for (i = 0; i < size; i++)
    {
        if (strcmp(lookfor, array[i]) == 0)
        {
            return 1;
        }

    }

    return 0;
}

void removeAllSpaceAndReturnAline(char **sequence) {
    int count = 0;
    char * c = *sequence;

    for (int i = 0; c[i]; i++)
    {
        if (c[i] != ' ' && c[i] != '\n')
            c[count++] = c[i]; // here count is
    }
    // incremented
    c[count] = '\0';
    *sequence =c;
}