# base64-clang

## 1. 介绍
C语言base64编解码库。

## 2. API
```c
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
```
