//
// Created by 徐伟毅 on 2017/3/11.
//

#ifndef THREEPIGS_ENCODE_H
#define THREEPIGS_ENCODE_H

#include "gear.h"

int Encode (int in, Gear gFast, Gear gMiddle, Gear gSlow) {
    int x, result;
    gSlow.Find(in, x);
    result = gSlow.Search(x);
    gMiddle.Find(result, x);
    result = gMiddle.Search(x);
    gFast.Find(result, x);
    result = gFast.Search(x);
    return result;
}

#endif //THREEPIGS_ENCODE_H
