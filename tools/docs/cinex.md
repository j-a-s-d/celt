# cinex

*c include expanding tool*

## brief

receives a c header file and flattens it out by including recursively all the referred headers with quotes

## usage

```console
    $ ./cinex <c-header-file>
```

## example

in the following example, two headers are created with one definition each, later a new header is created including the first two, finally this final header is passed to `cinex`, generating an output that shows the flatten of the two included headers

```console
    $ echo -e "#define HELLO \"hello\"" > a1.h
    $ echo -e "#define WORLD \"world\"" > a2.h
    $ echo -e "#include \"a1.h\"\n#include \"a2.h\"\n" > a_headers.h
    $ ./cinex a_headers.h
    // [cinex] while processing "a_headers.h" begins expansion of "a1.h"
    #define HELLO "hello"
    // [cinex] while processing "a_headers.h" begins expansion of "a2.h"
    #define WORLD "world"
    
```

