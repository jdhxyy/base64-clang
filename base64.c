// Copyright 2020-2021 The jdh99 Authors. All rights reserved.
// base64编解码库
// Authors: jdh99 <jdh821@163.com>

#include "base64.h"

#include <string.h>

// Base64GetEncodeLen 读取编码后的长度
int Base64GetEncodeLen(int dataLen) {
    int len = 0;
    if (dataLen % 3 == 0) {
        len = dataLen/3*4;
    } else {
        len = (dataLen / 3 + 1) * 4;
    }
    return len;
}

// Base64GetDecodeLen 读取解码后的长度
int Base64GetDecodeLen(char* data) {
    int len = 0;
    int dataLen = (int)strlen(data);
    if (strstr(data, "==")) {
        len = dataLen / 4 * 3 - 2;
    } else if (strstr(data,"=")) {
        len = dataLen / 4 * 3 - 1;
    } else {
        len = dataLen / 4 * 3;
    }
    return len;
}

// Base64Encode 将字节数据编码成base64字符串
// dstCapacity是字符串的容量
bool Base64Encode(uint8_t* src, int srcLen, char* dst, int dstCapacity) {
    if (src == NULL || srcLen == 0 || dst == NULL || dstCapacity <= 0) {
        return false;
    }

    //计算经过base64编码后的字符串长度
    int calcLen = Base64GetEncodeLen(srcLen);
    if (dstCapacity < calcLen + 1) {
        return false;
    }
    dst[calcLen] = '\0';

    //定义base64编码表
    uint8_t* base64Table = (uint8_t*)"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    // 以3个8位字符为一组进行编码
    int i = 0;
    int j = 0;
    for (i = 0, j = 0; i < calcLen - 2; j += 3, i += 4) {
        //取出第一个字符的前6位并找出对应的结果字符
        dst[i] = (char)base64Table[src[j] >> 2];
        //将第一个字符的后位与第二个字符的前4位进行组合并找到对应的结果字符
        dst[i+1] = (char)base64Table[(src[j] & 0x3) << 4 | (src[j+1] >> 4)];
        //将第二个字符的后4位与第三个字符的前2位组合并找出对应的结果字符
        dst[i+2] = (char)base64Table[(src[j+1] & 0xf) << 2 | (src[j+2] >> 6)];
        //取出第三个字符的后6位并找出结果字符
        dst[i+3] = (char)base64Table[src[j+2] & 0x3f];
    }

    switch(srcLen % 3) {
    case 1:
        dst[i-2]='=';
        dst[i-1]='=';
        break;
    case 2:
        dst[i-1]='=';
        break;
    }
    return true;
}

// Base64Decode 将base64格式字符串解码成字节流
// dstCapacity是解码后的字节数组容量.dstLen是解码后的长度
bool Base64Decode(char* src, uint8_t* dst, int dstCapacity, int* dstLen) {
    // 根据base64表，以字符找到对应的十进制数据
    static uint8_t table[] = {
        0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,62,0,0,0,
        63,52,53,54,55,56,57,58,
        59,60,61,0,0,0,0,0,0,0,0,
        1,2,3,4,5,6,7,8,9,10,11,12,
        13,14,15,16,17,18,19,20,21,
        22,23,24,25,0,0,0,0,0,0,26,
        27,28,29,30,31,32,33,34,35,
        36,37,38,39,40,41,42,43,44,
        45,46,47,48,49,50,51
    };

    if (src == NULL || dst == NULL || dstCapacity <= 0 || dstLen == 0) {
        return false;
    }

    int calcLen = Base64GetDecodeLen(src);
    if (dstCapacity < calcLen) {
        return false;
    }
    *dstLen = calcLen;
    if (dstCapacity >= calcLen + 1) {
        dst[calcLen] = '\0';
    }

    int srcLen = (int)strlen(src);
    // 以4个字符为一位进行解码
    int i = 0;
    int j = 0;
    for (i = 0, j = 0; i < srcLen - 2; j += 3, i += 4) {
        // 取出第一个字符对应base64表的十进制数的前6位与第二个字符对应base64表的十进制数的后2位进行组合
        dst[j] = (uint8_t)((table[(int)src[i]] << 2) | (table[(int)src[i+1]] >> 4));
        // 取出第二个字符对应base64表的十进制数的后4位与第三个字符对应bas464表的十进制数的后4位进行组合
        dst[j+1] = (uint8_t)((table[(int)src[i+1]] << 4) | (table[(int)src[i+2]] >> 2));
        // 取出第三个字符对应base64表的十进制数的后2位与第4个字符进行组合
        dst[j+2] = (uint8_t)((table[(int)src[i+2]] << 6) | (table[(int)src[i+3]]));
    }
    return true;
}

