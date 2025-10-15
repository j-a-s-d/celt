const char* wctype_h_name = "wctype.h";

const char* wctype_h_globals[] = {
    // Microsoft-specific global variables declared in <wctype.h> used internally by character classification functions:
    "_pctype",
    "_pwctype",
    "_wctype",
    "_mbctype",
    "_mbcasemap",
    NULL
};

// Types declared in wctype.h
const char* wctype_h_types[] = {
    "wctrans_t",    // type representing a wide character transformation
    "wctype_t",     // type representing a wide character classification
    NULL
};

// Macros declared in wctype.h
const char* wctype_h_macros[] = {
    // Character class test functions (returning non-zero for true, 0 for false)
    "iswalnum",     // test for alphanumeric wide character
    "iswalpha",     // test for alphabetic wide character
    "iswblank",     // test for blank wide character
    "iswcntrl",     // test for control wide character
    "iswdigit",     // test for decimal digit wide character
    "iswgraph",     // test for graphic wide character
    "iswlower",     // test for lowercase wide character
    "iswprint",     // test for printing wide character
    "iswpunct",     // test for punctuation wide character
    "iswspace",     // test for whitespace wide character
    "iswupper",     // test for uppercase wide character
    "iswxdigit",    // test for hexadecimal digit wide character

    // Character transformation functions
    "towlower",     // convert wide character to lowercase
    "towupper",     // convert wide character to uppercase

    NULL
};

// Functions declared in wctype.h
const char* wctype_h_functions[] = {
    // Extensible wide character classification and mapping functions
    "iswctype",     // int iswctype(wint_t wc, wctype_t desc);
    "wctype",       // wctype_t wctype(const char *property);
    "towctrans",    // wint_t towctrans(wint_t wc, wctrans_t desc);
    "wctrans",      // wctrans_t wctrans(const char *property);
    NULL
};

