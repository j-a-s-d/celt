const char* stdio_h_name = "stdio.h";

const char* stdio_h_globals[] = {
    // Note: stdin, stdout, stderr are macros, not plain global variables,
    // so they are *not* included here.
    // The C standard library does not publish other global variables
    // with external linkage in stdio.h.
    NULL
};

// Types declared in stdio.h
const char* stdio_h_types[] = {
    "FILE",
    "fpos_t",
    NULL
};

// Macros declared in stdio.h
const char* stdio_h_macros[] = {
    "NULL",
    "EOF",
    "BUFSIZ",
    "FOPEN_MAX",
    "FILENAME_MAX",
    "TMP_MAX",
    "_IOFBF",
    "_IOLBF",
    "_IONBF",
    "SEEK_SET",
    "SEEK_CUR",
    "SEEK_END",
    "stdin",
    "stdout",
    "stderr",
    NULL
};

// Functions declared in stdio.h
const char* stdio_h_functions[] = {
    "fclose",
    "clearerr",
    "feof",
    "ferror",
    "fflush",
    "fgetpos",
    "fopen",
    "fread",
    "freopen",
    "fseek",
    "fsetpos",
    "ftell",
    "fwrite",
    "remove",
    "rename",
    "rewind",
    "setbuf",
    "setvbuf",
    "tmpfile",
    "tmpnam",
    "fprintf",
    "printf",
    "sprintf",
    "vfprintf",
    "vprintf",
    "vsprintf",
    "fscanf",
    "scanf",
    "sscanf",
    "fgetc",
    "fgets",
    "fputc",
    "fputs",
    "getc",
    "getchar",
    "gets",
    "putc",
    "putchar",
    "puts",
    "ungetc",
    "perror",
    "getline",
    NULL
};

