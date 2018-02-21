#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "unistyle.h"

off_t fsize(const char *filename) {
    struct stat st;

    if (stat(filename, &st) == 0)
        return st.st_size;

    return -1;
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("usage: charter file\n");
        return -1;
    }
    FILE *fp;
    fp = fopen(argv[1], "r");
    long size = fsize(argv[1]);
    char * fcontent = malloc(size);
    fread(fcontent, 1, size, fp);
    fclose(fp);

    /** TODO do your magic **/
    Style * style = parse(fcontent);
    style_print(style);

    free(fcontent);
    return 0;
}
