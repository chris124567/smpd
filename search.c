#include <stdio.h>

#include <mpd/client.h>

#include "constants.h"
#include "log.h"
#include "search.h"
#include "util.h"

void tab_complete_list(struct mpd_connection *connection) {
    /* Display all artists, albums, and titles for tab completion when adding */
    long unsigned int i;

    enum mpd_tag_type mpd_tags[3] = {MPD_TAG_ARTIST, MPD_TAG_ALBUM,
                                     MPD_TAG_TITLE};
    for (i = 0; i < sizeof(mpd_tags) / sizeof(mpd_tags[0]); ++i) {
        tag_search(connection, mpd_tags[i]);
    }
}

void tag_search(struct mpd_connection *connection, enum mpd_tag_type tag) {
    struct mpd_pair *pair;

    mpd_search_db_tags(connection, tag);
    mpd_search_commit(connection);

    while ((pair = mpd_recv_pair_tag(connection, tag)) != NULL) {
        mpd_check_error(connection);
        if (pair->value) {
            printf("%s\n", pair->value);
            mpd_return_pair(connection, pair);
        }
    }

#ifdef DEBUG
    log_info("Searched for tag %d", tag);
#endif
}

void search_all_tags(struct mpd_connection *connection, char *query,
                     bool play) {
    int i;
    struct mpd_song *song;

    if (play) {
        mpd_search_add_db_songs(connection, false);
    } else {
        mpd_search_db_songs(connection, false);
    }
    mpd_check_error(connection);

    mpd_search_add_any_tag_constraint(connection, MPD_OPERATOR_DEFAULT, query);
    mpd_check_error(connection);
    mpd_search_commit(connection);
    mpd_check_error(connection);

    if (play) { /* actually play the songs */
        if (!mpd_response_finish(connection)) {
            mpd_check_error(connection);
        }
    } else { /* print the songs */
        i = 0;
        while ((song = mpd_recv_song(connection)) != NULL) {
            mpd_check_error(connection);
            if (song) {
                const char *artist = mpd_song_get_tag(song, MPD_TAG_ARTIST, 0);
                const char *title = mpd_song_get_tag(song, MPD_TAG_TITLE, 0);
                printf("%d - %s - %s\n", i, artist ? artist : NULL_STRING,
                       title ? title : NULL_STRING);
                mpd_song_free(song);
            }
            i++;
        }
    }
#ifdef DEBUG
    log_info("Searched all tags for query %s", query);
#endif
}