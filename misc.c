#include "misc.h"
#include <stdio.h>
#include "constants.h"

void print_help(void) {
    printf(
        "smpd version %d\n-0\t\tTab completion generator, internal\n-a\t\tAdd "
        "search results(s) to queue (tab completed), takes a "
        "query\n-c\t\tClear the queue\n-C\t\tDisplay the currently playing "
        "song\n-d\t\tDelete a given position from the queue, takes a position "
        "integer\n-h\t\tPrint this help message\n-l, -L\t\tPrint all of the "
        "currently queued songs\n-m\t\tPrint the current songs "
        "metadata\n-n\t\tSkip relatively around in the song queue, takes an "
        "integer\n-p\t\tSeek to an exact position in the current song (in "
        "seconds), takes an integer argument\n-P\t\tSeek relatively in the "
        "current song (in seconds), takes an integer argument\n-r\t\tToggle "
        "repeat mode\n-s\t\tSearch library, takes query(s)\n-x\t\tClear the "
        "queue, then search the library for a given query.  Takes"
        "query(s)\nNote: -x and -a have identical behavior, except -x deletes "
        "the "
        "current queue before adding the results\n",
        VERSION);
}

