#include <string.h>
#include <stdio.h> 
#include <stdlib.h>

#include "./error.h"
#include "./parser.h"
#include "./output.h"
#include "./interactive.h"


FILE * input = NULL;
int in = 0;

FILE * output = NULL;
int out = 0;

int usr = 0;
int ign = 0;

int quit(int code) {
    if(input != NULL) {
        fclose(input);
    }
    
    if(output != NULL) {
        fclose(output);
    }

    exit(code);
}

int main(int argc, char *argv[]) {
    setbuf(stdout, NULL);
    if(argc == 1) {
        help_short();
        return 0;
    }

    for(int i = 1; i < argc; i++) {
        if(!strcmp("-i", argv[i])) {
            if(argc < i + 1) {
                help_short();
                quit(0);
            } 

            in = 1;
            input = fopen(argv[i+1], "r");
            if(input == NULL) {
                fprintf(stderr, "Could not open the file\n");
                quit(1);
            }
            i++;
        } else if(!strcmp("-o", argv[i])) {
            if(argc < i + 1) {
                help_short();
                quit(0);
            }

            out = 1;
            output = fopen(argv[i+1], "w");
            if(output == NULL) {
                fprintf(stderr, "Could not open file\n");
                quit(1);
            }
            i++;
        } else if(!strcmp("-u", argv[i])) {
            usr = 1;
        } else if(!strcmp("--ign", argv[i])) {
            ign = 1;
        } else if(!strcmp("--help", argv[i]) || !strcmp("-h", argv[i])) {
            help();
        } else {
            help_short();
            return 0;
        }
    }

    if(usr) {
        interactive();
    } else {
        if(!in) {
            help_short();
            return 0;
        }

        char * code = read(input);
        parse(code, output, out);
        free(code);
    }

    return 0;
}
