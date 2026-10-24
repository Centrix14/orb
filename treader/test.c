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

int main(void) {
    accept_value_part();

    return 0;
}
