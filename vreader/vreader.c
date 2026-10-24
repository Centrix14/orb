#include <stdbool.h>
#include <ctype.h>

#include "vreader.h"

/* orb_vreader_read supplement */

bool __is_done(symbol value) {
    return value == ':'
        || value == ';'
        || value == ' ';
}

bool __is_first_digit(symbol value) {
    return isdigit(value);
}

bool __is_second_digit(symbol value) {
    return isdigit(value)
        || value == 'x'
        || value == 'X'
        || value == 'b'
        || value == 'B';
}

bool __is_remaining_digit(symbol value) {
    return isxdigit(value);
}

bool __is_invalid_symbol_at_index(symbol value, token_position index) {
    switch (index) {
    case 0:
        return !__is_first_digit(value);
    case 1:
        return !__is_second_digit(value);
    default:
        return !__is_remaining_digit(value);
    }
}

void orb_vreader_read(struct orb_reader *reader, symbol value) {
    if (orb_reader_is_ready(*reader) || orb_reader_is_reading(*reader))
        reader->state = orb_reader_reading;
    else {
        reader->state = orb_reader_error;
        reader->error = orb_reader_read_before_init;

        return;
    }

    if (__is_done(value)) {
        reader->state = orb_reader_done;
        reader->error = orb_reader_ok;
        return;
    }

    if (__is_invalid_symbol_at_index(value, reader->index)) {
        reader->state = orb_reader_error;
        reader->error = orb_reader_invalid_symbol;
        return;
    }

    bool appended = __append_symbol(reader->token, reader->index, value);
    if (appended)
        reader->index++;
    else {
        reader->state = orb_reader_error;
        reader->error = orb_reader_token_buffer_overflow;
    }
}
