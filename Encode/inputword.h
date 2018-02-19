//
// Created by 徐伟毅 on 2017/3/11.
//

#ifndef THREEPIGS_INPUTWORD_H
#define THREEPIGS_INPUTWORD_H

#include "inputfile.h"

void Encodeword() {

    char plain[100], cipher[100];
    int in[100], out[100];
    int i = 0;
    int gf = 0, gm = 0;

    cout << "请输入您要加密的内容（空格以'／'代替）: " << endl;
    cin >> plain;
    int n = (int) (strlen(plain));
    cout << "正在加密......\n";
    for (i = 0; i < n; ++i) {
        if (plain[i] < 65 || plain[i] > 122 || plain[i] == 91 || plain[i] == 92 || plain[i] == 93 || plain[i] == 94 || plain[i] == 95 || plain[i] == 96) {
            cipher[i] = plain[i];
        } else {
            if (plain[i] >= 97 && plain[i] <= 122) {
                in[i] = plain[i] - 32 - 'A';
            } else {
                in[i] = plain[i] - 'A';
            }
            out[i] = Encode(in[i], gFast, gMiddle, gSlow);
            cipher[i] = char(out[i] + 'A');
            gf++;
            gFast.move();
            if (gf == 26) {
                gm++;
                gMiddle.move();
                gf = 0;
                if (gm == 26) {
                    gSlow.move();
                    gm = 0;
                }
            }
        }
        cipher[i+1] = '\0';
    }
    cout << "加密成功！密文是：" << endl;
    cout << cipher;
}

#endif //THREEPIGS_INPUTWORD_H
