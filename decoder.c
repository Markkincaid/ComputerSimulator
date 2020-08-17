#include "decoder.h"

unsigned int decoder(unsigned char b) {
    return 1 << (b & DECODER_BITMASK);
}
