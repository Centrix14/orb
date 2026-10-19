#include <stdbool.h>

#include "../reader/reader.h"

bool __append_symbol(symbol *token, token_position index, symbol value) {
    if (index == TOKEN_LENGTH + 1)
        return false;

    token[index] = value;
    token[index + 1] = '\0';

    return true;
}
