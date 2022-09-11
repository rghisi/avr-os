//
// Created by ghisi on 10.09.22.
//

#include "Random.h"

const uint8_t Random::sequence[] = {
        193, 132, 136, 115, 13, 35, 204, 189, 194, 65, 78, 140, 50, 85, 153, 120,
        117, 216, 248, 28, 73, 79, 170, 164, 62, 210, 245, 77, 10, 68, 123, 109,
        225, 81, 135, 222, 167, 27, 231, 178, 143, 173, 211, 96, 89, 175, 41, 30,
        169, 150, 72, 106, 235, 145, 0, 144, 90, 226, 100, 158, 229, 38, 83, 165,
        201, 33, 152, 202, 232, 166, 91, 58, 203, 8, 92, 3, 2, 148, 26, 168,
        213, 4, 56, 116, 40, 233, 71, 187, 215, 63, 102, 228, 122, 110, 238, 94,
        227, 22, 139, 24, 207, 42, 253, 84, 121, 199, 161, 54, 244, 236, 18, 133, 111, 142, 48, 129, 59, 195, 179, 34,
        67, 219, 239, 97, 17, 118, 6, 128,
        185, 141, 9, 241, 43, 126, 157, 46, 181, 12, 182, 125, 223, 212, 87, 20, 95, 52, 80, 119, 197, 155, 190, 64,
        200, 183, 242, 44, 247, 251, 57, 112, 160, 14, 171, 220, 11, 205, 75, 49, 208, 98, 23, 16, 131, 176, 180, 31,
        19, 162, 127, 192, 103, 101, 146, 230, 177, 198, 113, 61, 37, 55, 209, 252, 188, 70, 206, 250, 163, 138, 45, 5,
        53, 114, 104, 151, 82, 147, 196, 249, 36, 69, 246, 156, 29, 93, 191, 221, 25, 66, 105, 137, 39, 124, 32, 240,
        184, 76, 254, 86, 224, 217, 237, 214, 243, 174, 149, 154, 60, 1, 218, 47, 107, 108, 21, 172, 186, 234, 134, 255,
        99, 74, 7, 88, 130, 159, 51, 15
};

uint8_t Random::last = 0;
uint8_t Random::offset = 0;

uint8_t Random::next() {
    last = sequence[last + offset];

    return last;
}

void Random::seed(uint8_t seed) {
    offset = seed;
}

