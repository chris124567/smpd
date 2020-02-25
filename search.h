#ifndef SEARCH_H
#define SEARCH_H
void tab_complete_list(struct mpd_connection *connection);
void tag_search(struct mpd_connection *connection, enum mpd_tag_type tag);
void search_all_tags(struct mpd_connection *connection, char *query, bool play);
#endif