#include <assert.h>

#include "vreader.h"

void init_deinit_integration() {
    struct orb_vreader r;

    orb_vreader_init(&r);
    assert(orb_vreader_is_ready(r));

    orb_vreader_deinit(&r);
    assert(orb_vreader_is_done(r));
}

void init_deinit_correctness() {
    struct orb_vreader r;

    orb_vreader_init(&r);
    assert(orb_vreader_check(r));

    orb_vreader_deinit(&r);
    assert(orb_vreader_check(r));
}

int main(void) {

    init_deinit_integration();
    init_deinit_correctness();

    return 0;
}
