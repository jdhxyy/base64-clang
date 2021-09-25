// Copyright 2020-2021 The jdh99 Authors. All rights reserved.
// base64������
// Authors: jdh99 <jdh821@163.com>

#ifndef BASE64_H
#define BASE64_H

#include <stdint.h>
#include <stdbool.h>

// Base64GetEncodeLen ��ȡ�����ĳ���
int Base64GetEncodeLen(int dataLen);

// Base64GetDecodeLen ��ȡ�����ĳ���
int Base64GetDecodeLen(char* data);

// Base64Encode ���ֽ����ݱ����base64�ַ���
// dstCapacity���ַ���������
bool Base64Encode(uint8_t* src, int srcLen, char* dst, int dstCapacity);

// Base64Decode ��base64��ʽ�ַ���������ֽ���
// dstCapacity�ǽ������ֽ���������.dstLen�ǽ����ĳ���
bool Base64Decode(char* src, uint8_t* dst, int dstCapacity, int* dstLen);

#endif
