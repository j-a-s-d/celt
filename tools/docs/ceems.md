# ceems

*c code well-known includes good-enough inference tool*

## brief

receives a c file and outputs the header files that it seems to be using amongst the known headers declarations

## usage

```console
    $ ./ceems <c-source-file>
```

## example

in the following example, the code line `printf("%zu %c %ld\n", strlen("hi"), toupper('a'), time(NULL));` will be echoed in a c file and then it will be passed to `ceems`, generating an output that shows the 4 inclusions implicit in the code

```console
    $ echo printf\(\"%zu %c %ld\\n\", strlen\(\"hi\"\), toupper\('a'\), time\(NULL\)\)\; > test-inc.c
    $ ./ceems test-inc.c
    #include <stdio.h>
    #include <string.h>
    #include <ctype.h>
    #include <time.h>
```

