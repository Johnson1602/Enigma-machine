//
// Created by 徐伟毅 on 2017/3/15.
//

#ifndef DECODE_H
#define DECODE_H

#include "gear.h"

int Decode (int in, Gear gFast, Gear gMiddle, Gear gSlow) {
    int x, result;
    gFast.Find(in, x);
    result = gFast.Search(x);
    gMiddle.Find(result, x);
    result = gMiddle.Search(x);
    gSlow.Find(result, x);
    result = gSlow.Search(x);
    return result;
}

#endif //DECODE_H
