#include <charset.h>

int knownDigits[] = {
    _0, _1, _2, _3, _4, _5, _6, _7, _8, _9,
};

char formatDigit(const int digit, bool withDot) {
    if (digit > 9 || digit < 0) {
        return _0;
    }

    char val = knownDigits[digit];
    if (withDot) {
        // flip last byte to enable point
        return val ^ (1 << 7);
    }
    return val;
}
