//
// Created by 徐伟毅 on 2017/3/11.
//

#include "inputword.h"

int main() {

    int a;      //选择加密方式

    //初始化转轮密码机
    gFast.initGear(fgear);
    gMiddle.initGear(mgear);
    gSlow.initGear(sgear);

    cout << "请选择加密方式：\n" << "1.加密输入的内容\t" << "2.加密指定文件" << endl << "请输入序号并回车确认：\t";
    cin >> a;
    if (a == 1) {
        Encodeword();
    } else if (a == 2) {
        Encodefile();
    }

    return 0;
}