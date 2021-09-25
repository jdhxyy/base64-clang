// Copyright 2020-2021 The jdh99 Authors. All rights reserved.
// base64编解码库
// Authors: jdh99 <jdh821@163.com>

#ifndef BASE64_H
#define BASE64_H

#include <stdint.h>
#include <stdbool.h>

// Base64GetEncodeLen 读取编码后的长度
int Base64GetEncodeLen(int dataLen);

// Base64GetDecodeLen 读取解码后的长度
int Base64GetDecodeLen(char* data);

// Base64Encode 将字节数据编码成base64字符串
// dstCapacity是字符串的容量
bool Base64Encode(uint8_t* src, int srcLen, char* dst, int dstCapacity);

// Base64Decode 将base64格式字符串解码成字节流
// dstCapacity是解码后的字节数组容量.dstLen是解码后的长度
bool Base64Decode(char* src, uint8_t* dst, int dstCapacity, int* dstLen);

#endif
