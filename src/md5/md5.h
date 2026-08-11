#ifndef MY_MD5_H
#define MY_MD5_H

#include <cstdint>
#include <string>
#include <vector>

namespace my_md5 {

  /**
   * @brief 计算文件的 MD5 哈希值（十六进制字符串格式）
   *
   * 使用 QuickDigest5 第三方库对指定文件计算 MD5 哈希，
   * 返回 32 位小写十六进制字符串。
   *
   * @param filePath 要进行 MD5 校验的文件完整路径（UTF-8 编码）
   * @return 32 位小写十六进制 MD5 字符串；校验失败时返回空字符串
   */
  std::string ComputeFileHash(const std::string& filePath);

  /**
   * @brief 计算文件的 MD5 哈希值（二进制格式）
   *
   * 使用 QuickDigest5 第三方库对指定文件计算 MD5 哈希，
   * 返回 16 字节的原始二进制数据。
   *
   * @param filePath 要进行 MD5 校验的文件完整路径（UTF-8 编码）
   * @return 16 字节的 uint8_t 向量；校验失败时返回空向量
   */
  std::vector<uint8_t> ComputeFileBinaryHash(const std::string& filePath);

}  // namespace my_md5

#endif  // MY_MD5_H
