# chime

*c header included members explorer tool*

## brief

receives the c header file name and prints all its members separated into 4 categories: Globals, Types, Macros and Functions

## usage

```console
    $ ./chime <header-file-name>
```

## example

in the following example, chime is invoked with `time.h` as parameter, generating an output that shows all the members of that header

```console
    $ ./chime time.h
    Loaded 134 declarations.
    File: time.h
    -- Globals
        -
    -- Types
        clock_t
        time_t
        struct tm
        clockid_t
        timer_t
    -- Macros
        CLOCKS_PER_SEC
        TIME_UTC
    -- Functions
        clock
        difftime
        mktime
        time
        asctime
        ctime
        gmtime
        localtime
        strftime
        nanosleep
        clock_getres
        clock_gettime
        clock_settime
        timer_create
        timer_delete
        timer_getoverrun
        timer_gettime
        timer_settime
        gmtime_r
        localtime_r
        timegm
        timespec_getres
```

