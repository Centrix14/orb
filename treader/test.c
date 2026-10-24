#include <assert.h>
#include <string.h>

#include "treader.h"

void accept_value_part() {
    struct orb_treader r;
    orb_treader_init(&r);

    symbol *value = "0x3b1";
    for (int i = 0; i < strlen(value); i++) {
        orb_treader_read(&r, value[i]);

        assert(orb_treader_is_reading_length(r));
    }

    orb_treader_deinit(&r);
}

void refuse_measure_only() {
    struct orb_treader r;
    orb_treader_init(&r);

    symbol *value = "b";
    for (int i = 0; i < strlen(value); i++) {
        orb_treader_read(&r, value[i]);

        assert(orb_treader_is_failed(r));
    }

    orb_treader_deinit(&r);
}

void accept_value_definition() {
    struct orb_treader r;
    orb_treader_init(&r);

    symbol *value = "0xf ";
    for (int i = 0; i < strlen(value); i++) {
        orb_treader_read(&r, value[i]);

        if (value[i] == ' ')
            assert(orb_treader_is_reading_measure(r));
        else
            assert(orb_treader_is_reading_length(r));
    }

    orb_treader_deinit(&r);
}

void accept_measure_part() {
    struct orb_treader r;
    orb_treader_init(&r);

    symbol *value = "0xf b";
    for (int i = 0; i < strlen(value); i++) {
        orb_treader_read(&r, value[i]);

        if (value[i] == ' ' || value[i] == 'b')
            assert(orb_treader_is_reading_measure(r));
        else
            assert(orb_treader_is_reading_length(r));
    }

    orb_treader_deinit(&r);
}

void accept_type_definition() {
    struct orb_treader r;
    orb_treader_init(&r);

    symbol *value = "16 b;";
    for (int i = 0; i < strlen(value); i++) {
        orb_treader_read(&r, value[i]);
    }
    assert(orb_treader_is_done(r));

    orb_treader_deinit(&r);
}

int main(void) {
    accept_value_part();
    refuse_measure_only();
    accept_value_definition();
    accept_measure_part();

    return 0;
}
