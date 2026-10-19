#include "../reader/reader.h"
#include "../aux/aux.h"

void orb_mreader_read(struct orb_reader *reader, symbol value) {
    if (orb_reader_is_ready(*reader) || orb_reader_is_reading(*reader))
        reader->state = orb_reader_reading;
    else {
        reader->state = orb_reader_error;
        reader->error = orb_reader_read_before_init;

        return;
    }

    if (value == ';') {
        reader->state = orb_reader_done;
        reader->error = orb_reader_ok;

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
