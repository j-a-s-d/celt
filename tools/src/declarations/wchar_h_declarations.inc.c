const char* wchar_h_name = "wchar.h";

const char* wchar_h_globals[] = {
    // Microsoft-specific global variables declared in <wchar.h>:
    "__argc",
    "__argv",
    "__wargv",
    // Additionally, Microsoft C runtime declares environment variables:
    "_environ",
    "_wenviron",
    NULL
};

// Types declared in wchar.h
const char* wchar_h_types[] = {
    "wchar_t",
    "wint_t",       // wide character integer type
    "wctype_t",
    NULL
};

// Macros declared in wchar.h
const char* wchar_h_macros[] = {
    "WCHAR_MAX",
    "WCHAR_MIN",
    "WEOF",
    "NULL",
    NULL
};

// Functions declared in wchar.h
const char* wchar_h_functions[] = {
    "btowc",
    "fgetwc",
    "fgetws",
    "fputwc",
    "fputws",
    "fwide",
    "fwprintf",
    "fwscanf",
    "getwc",
    "getwchar",
    "mbrlen",
    "mbrtowc",
    "mbsinit",
    "mbsrtowcs",
    "wcrtomb",
    "wcscat",
    "wcschr",
    "wcscmp",
    "wcscoll",
    "wcscpy",
    "wcscspn",
    "wcslen",
    "wcsncat",
    "wcsncmp",
    "wcsncpy",
    "wcspbrk",
    "wcsrchr",
    "wcsrtombs",
    "wcsspn",
    "wcsstr",
    "wcstod",
    "wcstof",
    "wcstold",
    "wcstol",
    "wcstoll",
    "wcstoul",
    "wcstoull",
    "wcswidth",
    "wcsxfrm",
    "wctob",
    "wmemchr",
    "wmemcmp",
    "wmemcpy",
    "wmemmove",
    "wmemset",
    "wprintf",
    "wscanf",
    NULL
};

