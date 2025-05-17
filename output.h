#ifndef usage_h
#define usage_h

int help_short() {
    char * helptext = "brainfuck [-io] file [-u] [--ign] [-h/--help]\n";
    printf("%s", helptext);
    return 0;
}

int help() {
    char * helptext = "brainfuck - program\n"
    "-i file (for the input method)\n"
    "-o file (for the output method)\n"
    "-u (for inputting one command at a time by the user)\n"
    "--ign (to ignore the warning messages / errors)\n"
    "-h / --help (this menu)\n";
    printf("%s", helptext);
    return 0;
}

#endif