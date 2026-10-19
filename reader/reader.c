#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>

#include "reader.h"

/* Variant predicates */

bool orb_reader_is_ready(struct orb_reader reader) {
    return (reader.token[0] == '\0')
        && (reader.index == 0)
        && (reader.state == orb_reader_ready)
        && (reader.error == orb_reader_ok);
}

bool orb_reader_is_done(struct orb_reader reader) {
    return (reader.state == orb_reader_done)
        && (reader.error == orb_reader_ok);
}

bool orb_reader_is_failed(struct orb_reader reader) {
    return (reader.state == orb_reader_error)
        && (reader.error != orb_reader_ok);
}

bool orb_reader_is_reading(struct orb_reader reader) {
    return (reader.state == orb_reader_reading)
        && (reader.error == orb_reader_ok);
}

/* Invariants */

bool orb_reader_check(struct orb_reader reader) {
    int8_t variant =
        orb_reader_is_ready(reader)
        | orb_reader_is_done(reader) << 1
        | orb_reader_is_failed(reader) << 2
        | orb_reader_is_reading(reader) << 3;

    bool is_valid_index = (reader.index <= TOKEN_LENGTH);
    bool is_valid_variant =
        (variant == 0x1)
        || (variant == 0x2)
        || (variant == 0x4)
        || (variant == 0x8);

    return is_valid_index && is_valid_variant;
}

/* Variant changing methods */

void orb_reader_init(struct orb_reader *blank) {
    blank->token[0] = '\0';
    blank->index = 0;

    blank->state = orb_reader_ready;
    blank->error = orb_reader_ok;
}

void orb_reader_deinit(struct orb_reader *reader) {
    reader->state = orb_reader_done;
    reader->error = orb_reader_ok;
}

