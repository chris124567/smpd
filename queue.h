#ifndef QUEUE_H
#define QUEUE_H
void clear_queue(struct mpd_connection *connection);
void delete_from_queue(struct mpd_connection *connection, int slot);
void print_queue(struct mpd_connection *connection);
void queue_relative_change(struct mpd_connection *connection, int step);
void shuffle_queue(struct mpd_connection *connection);
#endif
