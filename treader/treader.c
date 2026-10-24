#include "treader.h"

bool orb_treader_is_reading_length(struct orb_treader reader) {
    return reader.state == orb_treader_reading_length
        && orb_reader_is_reading(reader.vreader);
}

bool orb_treader_is_reading_measure(struct orb_treader reader) {
    return reader.state == orb_treader_reading_measure
        && (orb_reader_is_ready(reader.mreader)
            || orb_reader_is_reading(reader.mreader));
}

bool orb_treader_is_reading(struct orb_treader reader) {
    return orb_treader_is_reading_length(reader)
        || orb_treader_is_reading_measure(reader);
}

bool orb_treader_is_failed(struct orb_treader reader) {
    return orb_reader_is_failed(reader.vreader)
        || orb_reader_is_failed(reader.mreader);
}

bool orb_treader_is_done(struct orb_treader reader) {
    return orb_reader_is_done(reader.vreader)
        && orb_reader_is_done(reader.mreader);
}

void orb_treader_init(struct orb_treader *blank) {
    blank->state = orb_treader_reading_length;

    orb_reader_init(&blank->vreader);
    orb_reader_init(&blank->mreader);
}

void orb_treader_deinit(struct orb_treader *reader) {
    orb_reader_deinit(&reader->vreader);
    orb_reader_deinit(&reader->mreader);
}

void orb_treader_read(struct orb_treader *reader, symbol value) {
    if (reader->state == orb_treader_reading_length)
        orb_vreader_read(&reader->vreader, value);
    else if (reader->state == orb_treader_reading_measure)
        orb_mreader_read(&reader->mreader, value);

    if (orb_reader_is_done(reader->vreader))
        reader->state = orb_treader_reading_measure;
}
