#ifndef _AUDIO_H
#define _AUDIO_H

#include <Arduino.h>
#include "base64.h"
#include "I2S.h"
#include <WiFi.h>
#include <ArduinoJson.h>

// 16bit, monoral, 16000Hz,  linear PCM
// 主要用于录制音频
class Audio1
{
  // I2S *i2s: 指向 I2S 设备的指针，用于音频输入和输出。
  I2S *i2s;
  // WAV 文件头的大小，固定为 44 字节。
  static const int headerSize = 44;
  //  I2S 缓冲区的大小，用于存储音频数据。
  static const int i2sBufferSize = 5120;
  char i2sBuffer[i2sBufferSize];
  // JSON 数据的大小。
  const int DATA_JSON_SIZE = 512;

  char data_json[512];
  String Question = "";
  // 建立基于 TCP 的网络连接。
  WiFiClient client; // @suppress("Abstract class cannot be instantiated")
  // 用于建立基于 TLS/SSL 的安全网络连接。
  // WiFiClientSecure clientsecure; // @suppress("Abstract class cannot be instantiated")
  WiFiClient *_client = nullptr;
  // WAV 文件头部分的格式字符串，包括音频格式、采样率等信息。
  const char *header_format = "{"
                              "\"format\":\"pcm\","
                              "\"rate\":8000,"
                              "\"dev_pid\":1537,"
                              "\"channel\":1,"
                              "\"cuid\":\"\","
                              "\"token\":\"\","
                              "\"speech\":\"";
  // WAV 文件尾部分的格式字符串，包括音频数据的长度。
  const char *footer_format = "\",\"len\":";
  // 用于创建 WAV 文件头部分
  void CreateWavHeader(byte *header, int waveDataSize);
  // 解析 JSON 数据并返回字符串。
  String parseJSON(const char *jsonResponse);
  // 计算音频数据的均方根值，用于检测音量大小。
  float calculateRMS(uint8_t *buffer, int bufferSize);

public:
  // WAV 数据的总大小，用于存储录制的音频数据。
  static const int wavDataSize = 30000; // It must be multiple of dividedWavDataSize. Recording time is about 1.9 second.
  // 分割后的 WAV 数据大小，用于分割大的连续内存区域。
  static const int dividedWavDataSize = i2sBufferSize / 4;
  // 存储分割后的 WAV 数据块的指针数组。
  char **wavData;                          // It's divided. Because large continuous memory area can't be allocated in esp32.
  // 填充后的 WAV 文件头部分，确保长度为偶数且是 3 的倍数，用于 Base64 编码
  byte paddedHeader[headerSize + 4] = {0}; // The size must be multiple of 3 for Base64 encoding. Additional byte size must be even because wave data is 16bit.

  Audio1();
  ~Audio1();
  // 录制音频数据的函数。
  void Record();
  // 清除录制的音频数据。
  void clear();
  // 初始化音频录制功能。
  void init();
};

#endif // _AUDIO_H


