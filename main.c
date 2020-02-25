#include <stdio.h>
#include <stdlib.h>

#include <getopt.h>
#include <mpd/client.h>
#include "constants.h"
#include "log.h"
#include "misc.h"
#include "player.h"
#include "queue.h"
#include "search.h"
#include "song.h"
#include "util.h"

#define HOST "127.0.0.1"
#define PORT 6600

int main(int argc, char *argv[]) {
    int opt;
    struct mpd_connection *connection;

    connection = NULL;
    connection = mpd_connection_new(HOST, PORT, 0);

    if (connection != NULL) {
#ifdef DEBUG
        log_info(MSG_CONNECTION_SUCC);
#endif
        if (mpd_connection_get_error(connection) != MPD_ERROR_SUCCESS) {
            die(connection, MSG_CONNECTION_FAIL);
        }
        while ((opt = getopt(argc, argv, "0a:cCd:hlLmn:p:P:rRs:tx:")) != -1) {
            switch (opt) {
                case '0':
                    tab_complete_list(connection);
                    break;

                case 'a':
                    if (optarg) {
                        optind--;
                        for (; optind < argc && *argv[optind] != '-';
                             optind++) {
                            search_all_tags(connection, argv[optind], true);
                        }
                    } else {
                        die(connection, ADDITIONAL_ARGUMENT_FAIL);
                    }
                    break;

                case 'c':
                    clear_queue(connection);
                    break;

                case 'C':
                    print_current_song(connection);
                    break;

                case 'd':
                    if (optarg) {
                        delete_from_queue(connection, atoi(optarg));
                    } else {
                        die(connection, ADDITIONAL_ARGUMENT_FAIL);
                    }
                    break;

                case 'h':
                    print_help();
                    break;

                case 'l':
                    print_queue(connection);
                    break;

                case 'L':
                    print_queue(connection);
                    break;

                case 'm':
                    print_current_song_metadata(connection);
                    break;

                case 'n':
                    if (optarg) {
                        queue_relative_change(connection, atoi(optarg));
                    } else {
                        die(connection, ADDITIONAL_ARGUMENT_FAIL);
                    }
                    break;

                case 'p':
                    if (optarg) {
                        song_set_position(connection, atoi(optarg));
                    } else {
                        die(connection, ADDITIONAL_ARGUMENT_FAIL);
                    }
                    break;

                case 'P':
                    if (optarg) {
                        song_set_relative_position(connection, atoi(optarg));
                    } else {
                        die(connection, ADDITIONAL_ARGUMENT_FAIL);
                    }
                    break;

                case 'r':
                    toggle_repeat_mode(connection);
                    break;

                case 'R':
                    shuffle_queue(connection);
                    break;

                case 's':
                    if (optarg) {
                        search_all_tags(connection, optarg, false);
                    } else {
                        die(connection, ADDITIONAL_ARGUMENT_FAIL);
                    }
                    break;

                case 't':
                    toggle_playing(connection);
                    break;

                case 'x':
                    if (optarg) {
                        clear_queue(connection);
                        optind--;
                        for (; optind < argc && *argv[optind] != '-';
                             optind++) {
                            search_all_tags(connection, argv[optind], true);
                        }
                        toggle_playing(
                            connection); /* for some reason after clearing queue
                                            it turns off playing mode, so we
                                            re-enable it with this */
                    } else {
                        die(connection, ADDITIONAL_ARGUMENT_FAIL);
                    }
                    break;

                default:
                    die(connection, UNKNOWN_ARGUMENT_FAIL);
                    break;
            }
        }
        mpd_connection_free(connection);
    } else {
        die(NULL, MSG_CONNECTION_FAIL);
    }

    exit(EXIT_SUCCESS);
}
