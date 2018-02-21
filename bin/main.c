#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "unistyle.h"

enum MODE {
    CLS,
    CSS,
    ASL
} typedef MODE;

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
        printf("usage: charter [--cls | --css | --asl] file\n");
        return -1;
    }
    MODE mode = CSS;
    FILE *fp;
    fp = fopen(argv[argc-1], "r");
    long size = fsize(argv[1]);
    char * fcontent = malloc(size);
    fread(fcontent, 1, size, fp);
    fclose(fp);

    if (argc > 2)
    {
        if (!strcmp(argv[1], "--cls"))
            mode = CLS;
        else if (!strcmp(argv[1], "--asl"))
            mode = ASL;
    }

    /** TODO do your magic **/
    Style * style = parse(fcontent);
    if (mode == ASL)
    {
        style_print(style);
    }
    else {
        char * rendered;
        if (mode == CLS){
            rendered = render_cls(style);
        } else {
            rendered = render_css(style);
        }
        printf("%s\n", rendered);
        free(rendered);
    }
    style_free(style);
    free(fcontent);
    return 0;
}
