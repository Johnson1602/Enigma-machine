//
// Created by 徐伟毅 on 2017/3/11.
//

#ifndef THREEPIGS_INPUTFILE_H
#define THREEPIGS_INPUTFILE_H

#include <fstream>
#include <string.h>
#include "encode.h"

void Outportfile(char *outport, char appchar) {
    ofstream outpurtfile(outport, ios::app);
    if (!outpurtfile) {
        cout << "创建文件失败！请确认文件路径配置正确！" << endl;
        return;
    }
    outpurtfile << appchar;
    outpurtfile.close();
}

void Encodefile() {
    char character, cipher;
    int gf = 0, gm = 0, in = 0, out = 0;
    ifstream importfile("/Users/Johnson/Downloads/3littlepigs.txt");  //配置正确文件加载路径
    if (!importfile) {
        cout << "文件打开失败！请确认文件路径配置正确！" << endl;
        return;
    }
    cout << "正在加密......\n";
    while (importfile.get(character)) {
        if (character < 65 || character > 122 || character == 91 || character == 92 || character == 93 || character == 94 || character == 95 || character == 96) {
            Outportfile((char *) "/Users/Johnson/Downloads/encoded.txt", character);
        } else {
            if (character >= 97 && character <= 122) {
                in = character - 32 - 'A';
            } else {
                in = character - 'A';
            }
            out = Encode(in, gFast, gMiddle, gSlow);
            cipher = char(out + 'A');
            Outportfile((char *) "/Users/Johnson/Downloads/encoded.txt", cipher);
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
    }
    importfile.close();
    cout << "文件加密成功！请查看。";
}

#endif //THREEPIGS_INPUTFILE_H
