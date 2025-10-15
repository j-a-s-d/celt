# cinco

*c include outfinding tool*

## brief

receives a c definition name and looks for it amongst the known headers declarations

## usage

```console
    $ ./cinco <c-definition-name>
```

## example

in the following example, it will be searched the defition of DBL_EPSILON, generating an output that shows `float.h` as the container file

```console
    $ ./cinco DBL_EPSILON
    Loaded 134 declarations.
    Text to search: DBL_EPSILON
    Found at file: float.h
```

