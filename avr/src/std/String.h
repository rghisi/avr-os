//
// Created by ghisi on 08.03.24.
//

#ifndef AVROSTESTS_STRING_H
#define AVROSTESTS_STRING_H


class String {
public:
    static int_fast16_t findFirst(char c, const char* in) {
        if (in == nullptr) {
            return -1;
        }

        int_fast16_t index = 0;
        char nextC = in[index];
        while (nextC != c && nextC != 0) {
            nextC = in[++index];
        }

        if (nextC == c) {
            return index;
        } else {
            return -1;
        }
    }
};


#endif //AVROSTESTS_STRING_H
