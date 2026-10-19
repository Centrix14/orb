#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>

#include "vreader.h"

/* Variant predicates */

bool orb_vreader_is_ready(struct orb_vreader reader) {
    return (reader.token[0] == '\0')
        && (reader.index == 0)
        && (reader.state == orb_vreader_ready)
        && (reader.error == orb_vreader_ok);
}

bool orb_vreader_is_done(struct orb_vreader reader) {
    return (reader.state == orb_vreader_done)
        && (reader.error == orb_vreader_ok);
}

bool orb_vreader_is_failed(struct orb_vreader reader) {
    return (reader.state == orb_vreader_error)
        && (reader.error != orb_vreader_ok);
}

bool orb_vreader_is_reading(struct orb_vreader reader) {
    return (reader.state == orb_vreader_reading)
        && (reader.error == orb_vreader_ok);
}

/* Invariants */

bool orb_vreader_check(struct orb_vreader reader) {
    int8_t variant =
        orb_vreader_is_ready(reader)
        | orb_vreader_is_done(reader) << 1
        | orb_vreader_is_failed(reader) << 2
        | orb_vreader_is_reading(reader) << 3;

    bool is_valid_index = (reader.index <= TOKEN_LENGTH);
    bool is_valid_variant =
        (variant == 0x1)
        || (variant == 0x2)
        || (variant == 0x4)
        || (variant == 0x8);

    return is_valid_index && is_valid_variant;
}

/* Variant changing methods */

void orb_vreader_init(struct orb_vreader *blank) {
    blank->token[0] = '\0';
    blank->index = 0;

    blank->state = orb_vreader_ready;
    blank->error = orb_vreader_ok;
}

void orb_vreader_deinit(struct orb_vreader *reader) {
    reader->state = orb_vreader_done;
    reader->error = orb_vreader_ok;
}

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

bool __append_symbol(symbol *token, token_position index, symbol value) {
    if (index == TOKEN_LENGTH + 1)
        return false;

    token[index] = value;
    token[index + 1] = '\0';

    return true;
}

void orb_vreader_read(struct orb_vreader *reader, symbol value) {
    if (orb_vreader_is_ready(*reader) || orb_vreader_is_reading(*reader))
        reader->state = orb_vreader_reading;
    else {
        reader->state = orb_vreader_error;
        reader->error = orb_vreader_read_before_init;

        return;
    }

    if (__is_done(value)) {
        reader->state = orb_vreader_done;
        reader->error = orb_vreader_ok;
        return;
    }

    if (__is_invalid_symbol_at_index(value, reader->index)) {
        reader->state = orb_vreader_error;
        reader->error = orb_vreader_invalid_symbol;
        return;
    }

    bool appended = __append_symbol(reader->token, reader->index, value);
    if (appended)
        reader->index++;
    else {
        reader->state = orb_vreader_error;
        reader->error = orb_vreader_token_buffer_overflow;
    }
}
