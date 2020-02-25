#ifndef PLAYER_H
#define PLAYER_H
void toggle_repeat_mode(struct mpd_connection *connection);
void toggle_playing(struct mpd_connection *connection);
void song_set_position(struct mpd_connection *connection, int position);
void song_set_relative_position(struct mpd_connection *connection,
                                int relative_offset);
#endif
