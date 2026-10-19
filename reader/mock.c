#include <ctype.h>

#include "reader.h"
#include "../aux/aux.h"

/*
  [0-9] - ready->reading | reading->reading
  ; | space - reading->done
 */

void orb_mock_read(struct orb_reader *reader, symbol value) {
    if (orb_reader_is_ready(*reader) || orb_reader_is_reading(*reader))
        reader->state = orb_reader_reading;
    else {
        reader->state = orb_reader_error;
        reader->error = orb_reader_read_before_init;

        return;
    }

    if (value == ';' || value == ' ') {
        reader->state = orb_reader_done;
        reader->error = orb_reader_ok;

        return;
    }

    if (!isdigit(value)) {
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
