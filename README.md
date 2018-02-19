# C++语言实现转轮密码机

> ​	20世纪20年代，随着机械和机电技术的成熟，以及电报和无线电需求的出现，引起了密码设备方面的一场革命——发明了转轮密码机（简称转轮机，Rotor）。转轮机由一个键盘和一系列转轮组成，每个转轮是26个字母的任意组合。转轮被齿轮连接起来，当一个转轮转动时，可以将一个字母转换成另一个字母。照此传递下去，当最后一个转轮处理完毕时，就可以得到加密后的字母。

### 一、转轮密码机原理

![密码机原理](https://ww4.sinaimg.cn/large/006tNbRwly1fdm4f6uia2j30go0bm0ty.jpg)

​	每一个旋转轮代表一个单表替代系统，旋转一个引脚，再转变为另一个单表替代系统。为使机器更安全，可把几种转轮和移动的齿轮结合起来。因为所有转轮以不同的速度移动，n个转轮的机器的周期是26的n次方，即n个单表替代系统。最后一个转轮转完一圈之后，它前面的转轮就旋转一个引脚，有点像时钟的齿轮。

### 二、工作目标

​	使用C++语言、链表以及文件处理，实现转轮密码机的加密过程。具体功能包括：

1. 输入100字符之内的任意文字，经程序加密后输出在屏幕上
2. 选择需要加密的文件，经程序加密后输出在指定文件路径

### 三、运行截图

加密文字：

![加密文字](https://ww1.sinaimg.cn/large/006tNbRwly1fdm4f3yzctj309l03uq3l.jpg)

加密文件：

![加密文件](https://ww2.sinaimg.cn/large/006tNbRwly1fdm4f4r20kj306v02ldg3.jpg)

加密前后文件对比：

![加密前后对比](https://ww3.sinaimg.cn/large/006tNbRwly1fdm4f2lx1qj31400p0agt.jpg)

### 四、实现思路

​	本程序的核心部分为 `Gear` 类的定义以及 `Encode` 加密算法的定义。`Gear` 类中包括三个转轮的初始化方法 `void initGear(int data[2][26]);`，齿轮的旋转方法 `bool move();` 以及加密算法 `int Encode (int in, Gear gFast, Gear gMiddle, Gear gSlow);` 中所要用到的查找 `bool Find(int in, int &x) const;` 和搜索 `int Search(int x) const;` 方法。下面分别介绍以上方法

1. 转轮初始化算法

```C++
void Gear::initGear(int data[2][26]) {
    Node *p = first, *q;
    for (int i = 0; i < 26; ++i) {
        q = new Node;
        q->leftElement = data[0][i];
        q->rightElement = data[1][i];
        if (i == 0) {
            first = q;
            p = q;
        } else if (i == 25) {
            p->link = q;
            p = q;
            q->link = first;
        } else {
            p->link = q;
            p = q;
        }
    }
}
```

​	调用初始化函数，传入一个二维数组，其中第一行对应转轮的左列元素值，第二列对应转轮的右列元素，使用 for 循环分别对转轮的每一行进行赋值。实际使用中只需传入不同的数组即可为不同的转轮进行初始化。

2. 齿轮旋转算法

```C++
bool Gear::move() {
    Node *p = first;
    for (int i = 0; i <25; ++i) {       // first 指向最后一个节点，将链表最后一个元素置为第一个元素
        p = p->link;
    }
    first = p;
    return true;
}
```

​	本程序使用单向循环链表来方便齿轮的旋转（每旋转一次，所有元素向下移动一个位置，处在最下面的元素翻到最上面）。所以只要找到当前处在最下面的元素，并将 `first` 指针指向它即可完成旋转的动作。

3. 加密算法和用到的查找及搜索方法

```C++
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

bool Gear::Find(int in, int &x) const {
    Node *p = first;
    for (int i = 0; i < in; ++i) {
        p = p->link;
    }
    x = p->leftElement;
    return true;
}

int Gear::Search(int x) const {
    Node *p = first;
    int i;
    for (i = 0; p && p->rightElement != x; ++i) {    //从第一个元素开始查找，一直到 p 指向 NULL 或 p 指向的节点的 element 值与 x 相等
        p = p->link;
    }
    if (p) {        //若 p 不指向 NULL，return 当前下标
        return i;
    }
    return -1;
}
```

​	`Encode` 算法的输入之一和输出都是对应字母所在元素的下标，例如上面转轮密码机原理图中，若按下的按键是“A”，它对应的下标为0，经过加密输出的下标为1。其他三个输入是三个转轮所对应的链表。

​	首先定义int x，作为 `Find(int in, int &x)` 和 ` Search(int x)` 的接收值和传入值。 `Find(int in, int &x)` 函数接收传入的下标，并找到该下标所对应的元素的值，例如传入“A”的下标为0，则其对应的元素为24； ` Search(int x)` 函数接收传入元素的值，并返回在右列中与传入元素值相同的元素所对应的下标，例如接收24，返回7。经过这两个函数就完成了慢轮子的加密，同理，再分别调用两次，即可完成中轮子和快轮子的加密过程，并返回最终的下标，此时只需将其加65（“A”对应的ASCII码值），即可得到加密后的字母。