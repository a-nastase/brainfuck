#ifndef parser_h
#define parser_h
#define SIZE 4096

char * read(FILE * input) {
    fseek(input, 0, SEEK_END);
    long size = ftell(input);
    rewind(input);

    char * buf = malloc(size + 1);

    if(buf == NULL) {
        fprintf(stderr, "Failed to allocate memory\n");
        return 0;
    }

    size_t read_size = fread(buf, 1, size, input);

    if(read_size != size) {
        fprintf(stderr, "File read error\n");
        free(buf);
        return NULL;
    }

    buf[read_size] = '\0';

    printf("Read code: %s\n\n\n", buf);

    return buf;
}

int external(FILE * output, int out, char byte) {
    if(output != NULL && out) {
        fputc(byte, output);
    } else {
        putchar(byte);
    }
    return 0;
}

int parse(char * code, FILE * output, int out) {
    int point = 0;
    char * local_memory = calloc(SIZE, 1);

    int len = strlen(code);
    printf("code length: %d\n", len);
    int run = 1;
    for(int rip = 0; rip < len && run; rip++) {
        //printf("instruction: %c\n", code[rip]);
        switch(code[rip]) {
            case '>': (point + 1 < SIZE) ? point++ : throw_error(1); break;
            case '<': (point - 1 >= 0) ? point-- : throw_error(1); break;
            
            case '+': local_memory[point]++; break;
            case '-': local_memory[point]--; break;

            case '.': external(output, out, local_memory[point]); break;
            case ',': local_memory[point] = getchar(); break;

            case '[':
                if(local_memory[point] == 0) {
                    int depth = 1;
                    while(depth > 0) {
                        rip++;
                        if(rip >= len) {
                            throw_error(2); run = 0; break;
                        }
                        if(code[rip] == '[') depth++;
                        if(code[rip] == ']') depth--;
                    }
                }
                break;

            case ']':
                if(local_memory[point] != 0) {
                    int depth = 1;
                    while(depth > 0) {
                        rip--;
                        if(rip < 0) {
                            throw_error(2); run = 0; break;
                        }
                        if(code[rip] == '[') depth--;
                        if(code[rip] == ']') depth++;
                    }
                }
                break;
        }
    }

    free(local_memory);
    return 0;
}

#endif