#include <stdio.h>

int main() {
//    1.类型转换
    unsigned char a = 257;//0001 00000001 a只会保留后8个bit，就是1
    unsigned char b = 1;
    int c = a + b; //a和b都转换为int类型再相加
    printf("%d",c);//1+1=2
//   2.移位运算
//    unsigned char a = 88;
//    unsigned char b = a << 2; //a会自动转换为int类型再进行移位
//    printf("%d",b);
//  3.移位运算 右移
//    int i = 0xcffffff3;
//    printf("%x\n", 0xcffffff3>>2);//无符号的int右移，高位补0
//    printf("%x\n", i>>2);//有符号位的int右移，因为是负数，高位补1
//int i = 0;
//unsigned int sum = 0;
//for (; i < 16; i++)
//	sum = sum + 1U<<i;
//printf("%x",sum);
//    char* a = "gzf";
//    a[0] = 'x';
    return 0;
}
