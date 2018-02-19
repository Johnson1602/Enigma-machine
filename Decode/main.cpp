#include "decode.h"

int main() {

    gFast.initGear(fgear);
    gMiddle.initGear(mgear);
    gSlow.initGear(sgear);

    char plain[80], cipher[80];
    int in[80], out[80];
    int i = 0;
    int gf = 0, gm = 0;

    cout << "请输入您要解密的内容（空格以'／'代替）: " << endl;
    fgets(cipher, 80, stdin);
//    cin >> plain;
    int n = (int) (strlen(cipher));
    cout << "正在解密......\n";
    for (i = 0; i < n; ++i) {
        if (cipher[i] < 65 || cipher[i] > 122 || cipher[i] == 91 || cipher[i] == 92 || cipher[i] == 93 || cipher[i] == 94 || cipher[i] == 95 || cipher[i] == 96) {
            plain[i] = cipher[i];
        } else {
            if (cipher[i] >= 97 && cipher[i] <= 122) {
                in[i] = cipher[i] - 32 - 'A';
            } else {
                in[i] = cipher[i] - 'A';
            }
            out[i] = Decode(in[i], gFast, gMiddle, gSlow);
            plain[i] = char(out[i] + 'A');
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
        plain[i+1] = '\0';
    }
    cout << "解密成功！明文是：" << endl;
//    cout << cipher;

    fputs(plain, stdout);

    return 0;
}