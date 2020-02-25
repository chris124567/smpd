# smpd
The first actually usable command line MPD client.  Featuring tab completion and convenient searching.

# Requirements:
* mpd (tested with 0.21.5)
* libmpdclient (tested with 2.16)
* c compiler
* c standard library

# Install:
`$ ./build.sh`

`# ./install.sh`

# Sample Usage of Most Used Features:
Case 1:

`smpd -x Ettor[TAB]`

`smpd -x Ettore\ Stratta`

Would erase the current queue and then play all songs by artist Ettore Strata.

Case 2:

`smpd -a Lovin[TAB]`

`smpd -a Loving\ You Erik[TAB]`

`smpd -a Loving\ You Erik\ Satie`

Would play all songs titled "Loving You", along with all songs by "Erik Satie".

Note: The tab completion works based on files in your library.  The above examples are hypothetical and assume that you have those artists and songs in your library.

# Options (any of the following can be combined and chained)
```-0      Tab completion generator, internal

-a      Add search results(s) to queue (tab completed), takes query(s)

-c      Clear the queue

-C      Display the currently playing song

-d      Delete a given position from the queue, takes a position integer

-h      Print this help message

-l, -L  Print all of the currently queued songs

-m      Print the current songs metadata

-n      Skip relatively around in the song queue, takes an integer

-p      Seek to an exact position in the current song (in seconds), takes an integer argument

-P      Seek relatively in the current song (in seconds), takes an integer argument

-r      Toggle repeat mode

-s      Search library, takes a query

-x      Clear the queue, then search the library for a given query (tab completed).  Takes query(s)

Note: -x and -a have identical behavior, except -x deletes the current queue before adding the results```
```

# Miscellaneous:
* Written in C99
* Compiles with maximum security features (see variable SEC in build.sh) and optimizations (CFLAGS and GCC_OPT)
* Compiles with no warnings or errors using `-Wall -Wextra -Wshadow -Wcast-qual -Wstrict-prototypes -Wmissing-prototypes` on gcc-8.3.0
* Tested all options with valgrind-3.14.0 to make sure there's no memory leaks, including testing w/ errors (hope I got everything, but C inevitably introduces bugs)
* Formatted with clang-format (see .clang-format for configuration)
* Implemented error handling for every libmpdclient call
* I use all of the functionality except the search/adding songs via my keyboard shortcut manager, xbindkeys.  An excerpt of my configuration can be seen in the `xbindkeys_excerpt` file.

# Known Issues:
- Tab completion when files have quotes in the name