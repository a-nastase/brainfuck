#ifndef error_h
#define error_h

/*

ERRORS:

0 - not a command
1 - exceeded local_memory size
2 - exceeded text area (code)

*/

int throw_error(int code) {
    printf("%s", "This feature has not been implemented...yet\n");
}

#endif