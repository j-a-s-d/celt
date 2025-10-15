const char* inttypes_h_name = "inttypes.h";

const char* inttypes_h_globals[] = {
    // <inttypes.h> defines integer types and macros for format specifiers,
    // but it does NOT define any global variables with external linkage.
    NULL
};

// Types declared in inttypes.h
const char* inttypes_h_types[] = {
    "imaxdiv_t",   // structure type returned by imaxdiv()
    NULL
};

// Macros declared in inttypes.h
const char* inttypes_h_macros[] = {
    // Format specifier macros for printf/fprintf family (PRI...)
    "PRId8", "PRId16", "PRId32", "PRId64",
    "PRIi8", "PRIi16", "PRIi32", "PRIi64",
    "PRIo8", "PRIo16", "PRIo32", "PRIo64",
    "PRIu8", "PRIu16", "PRIu32", "PRIu64",
    "PRIx8", "PRIx16", "PRIx32", "PRIx64",
    "PRIX8", "PRIX16", "PRIX32", "PRIX64",

    "PRIdLEAST8", "PRIdLEAST16", "PRIdLEAST32", "PRIdLEAST64",
    "PRIiLEAST8", "PRIiLEAST16", "PRIiLEAST32", "PRIiLEAST64",
    "PRIoLEAST8", "PRIoLEAST16", "PRIoLEAST32", "PRIoLEAST64",
    "PRIuLEAST8", "PRIuLEAST16", "PRIuLEAST32", "PRIuLEAST64",
    "PRIxLEAST8", "PRIxLEAST16", "PRIxLEAST32", "PRIxLEAST64",
    "PRIXLEAST8", "PRIXLEAST16", "PRIXLEAST32", "PRIXLEAST64",

    "PRIdFAST8", "PRIdFAST16", "PRIdFAST32", "PRIdFAST64",
    "PRIiFAST8", "PRIiFAST16", "PRIiFAST32", "PRIiFAST64",
    "PRIoFAST8", "PRIoFAST16", "PRIoFAST32", "PRIoFAST64",
    "PRIuFAST8", "PRIuFAST16", "PRIuFAST32", "PRIuFAST64",
    "PRIxFAST8", "PRIxFAST16", "PRIxFAST32", "PRIxFAST64",
    "PRIXFAST8", "PRIXFAST16", "PRIXFAST32", "PRIXFAST64",

    "PRIdMAX", "PRIiMAX", "PRIoMAX", "PRIuMAX", "PRIxMAX", "PRIXMAX",
    "PRIdPTR", "PRIiPTR", "PRIoPTR", "PRIuPTR", "PRIxPTR", "PRIXPTR",

    // Format specifier macros for scanf/fscanf family (SCN...)
    "SCNd8", "SCNd16", "SCNd32", "SCNd64",
    "SCNi8", "SCNi16", "SCNi32", "SCNi64",
    "SCNo8", "SCNo16", "SCNo32", "SCNo64",
    "SCNu8", "SCNu16", "SCNu32", "SCNu64",
    "SCNx8", "SCNx16", "SCNx32", "SCNx64",

    "SCNdLEAST8", "SCNdLEAST16", "SCNdLEAST32", "SCNdLEAST64",
    "SCNiLEAST8", "SCNiLEAST16", "SCNiLEAST32", "SCNiLEAST64",
    "SCNoLEAST8", "SCNoLEAST16", "SCNoLEAST32", "SCNoLEAST64",
    "SCNuLEAST8", "SCNuLEAST16", "SCNuLEAST32", "SCNuLEAST64",
    "SCNxLEAST8", "SCNxLEAST16", "SCNxLEAST32", "SCNxLEAST64",

    "SCNdFAST8", "SCNdFAST16", "SCNdFAST32", "SCNdFAST64",
    "SCNiFAST8", "SCNiFAST16", "SCNiFAST32", "SCNiFAST64",
    "SCNoFAST8", "SCNoFAST16", "SCNoFAST32", "SCNoFAST64",
    "SCNuFAST8", "SCNuFAST16", "SCNuFAST32", "SCNuFAST64",
    "SCNxFAST8", "SCNxFAST16", "SCNxFAST32", "SCNxFAST64",

    "SCNdMAX", "SCNiMAX", "SCNoMAX", "SCNuMAX", "SCNxMAX",
    "SCNdPTR", "SCNiPTR", "SCNoPTR", "SCNuPTR", "SCNxPTR",

    NULL
};

// Functions declared in inttypes.h
const char* inttypes_h_functions[] = {
    "imaxabs",     // absolute value of intmax_t
    "imaxdiv",     // division of intmax_t returning imaxdiv_t
    "strtoimax",   // string to intmax_t conversion
    "strtoumax",   // string to uintmax_t conversion
    "wcstoimax",   // wide string to intmax_t conversion
    "wcstoumax",   // wide string to uintmax_t conversion
    NULL
};

