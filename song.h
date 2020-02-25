#ifndef SONG_H
#define SONG_H
#include <mpd/client.h>
void print_current_song(struct mpd_connection *connection);
void print_current_song_metadata(struct mpd_connection *connection);
#endif