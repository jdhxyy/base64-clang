// Copyright 2020-2021 The jdh99 Authors. All rights reserved.
// base64������
// Authors: jdh99 <jdh821@163.com>

#include "base64.h"

#include <string.h>

// Base64GetEncodeLen ��ȡ�����ĳ���
int Base64GetEncodeLen(int dataLen) {
    int len = 0;
    if (dataLen % 3 == 0) {
        len = dataLen/3*4;
    } else {
        len = (dataLen / 3 + 1) * 4;
    }
    return len;
}

// Base64GetDecodeLen ��ȡ�����ĳ���
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

// Base64Encode ���ֽ����ݱ����base64�ַ���
// dstCapacity���ַ���������
bool Base64Encode(uint8_t* src, int srcLen, char* dst, int dstCapacity) {
    if (src == NULL || srcLen == 0 || dst == NULL || dstCapacity <= 0) {
        return false;
    }

    //���㾭��base64�������ַ�������
    int calcLen = Base64GetEncodeLen(srcLen);
    if (dstCapacity < calcLen + 1) {
        return false;
    }
    dst[calcLen] = '\0';

    //����base64�����
    uint8_t* base64Table = (uint8_t*)"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    // ��3��8λ�ַ�Ϊһ����б���
    int i = 0;
    int j = 0;
    for (i = 0, j = 0; i < calcLen - 2; j += 3, i += 4) {
        //ȡ����һ���ַ���ǰ6λ���ҳ���Ӧ�Ľ���ַ�
        dst[i] = (char)base64Table[src[j] >> 2];
        //����һ���ַ��ĺ�λ��ڶ����ַ���ǰ4λ������ϲ��ҵ���Ӧ�Ľ���ַ�
        dst[i+1] = (char)base64Table[(src[j] & 0x3) << 4 | (src[j+1] >> 4)];
        //���ڶ����ַ��ĺ�4λ��������ַ���ǰ2λ��ϲ��ҳ���Ӧ�Ľ���ַ�
        dst[i+2] = (char)base64Table[(src[j+1] & 0xf) << 2 | (src[j+2] >> 6)];
        //ȡ���������ַ��ĺ�6λ���ҳ�����ַ�
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

// Base64Decode ��base64��ʽ�ַ���������ֽ���
// dstCapacity�ǽ������ֽ���������.dstLen�ǽ����ĳ���
bool Base64Decode(char* src, uint8_t* dst, int dstCapacity, int* dstLen) {
    // ����base64�����ַ��ҵ���Ӧ��ʮ��������
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
    // ��4���ַ�Ϊһλ���н���
    int i = 0;
    int j = 0;
    for (i = 0, j = 0; i < srcLen - 2; j += 3, i += 4) {
        // ȡ����һ���ַ���Ӧbase64���ʮ��������ǰ6λ��ڶ����ַ���Ӧbase64���ʮ�������ĺ�2λ�������
        dst[j] = (uint8_t)((table[(int)src[i]] << 2) | (table[(int)src[i+1]] >> 4));
        // ȡ���ڶ����ַ���Ӧbase64���ʮ�������ĺ�4λ��������ַ���Ӧbas464���ʮ�������ĺ�4λ�������
        dst[j+1] = (uint8_t)((table[(int)src[i+1]] << 4) | (table[(int)src[i+2]] >> 2));
        // ȡ���������ַ���Ӧbase64���ʮ�������ĺ�2λ���4���ַ��������
        dst[j+2] = (uint8_t)((table[(int)src[i+2]] << 6) | (table[(int)src[i+3]]));
    }
    return true;
}

