#include "md5.h"

#include <filesystem>
#include <iostream>
#include <quickdigest5.hpp>

namespace my_md5 {

  std::string ComputeFileHash(const std::string& filePath) {
    // 计算前先检查文件是否存在
    std::error_code ec;
    if (!std::filesystem::exists(filePath, ec)) {
      std::cerr << "错误：文件不存在 - " << filePath << "\n";
      return "";
    }

    try {
      // 调用 QuickDigest5 的静态方法直接获取十六进制哈希字符串
      return QuickDigest5::fileToHash(filePath);
    } catch (const std::exception& e) {
      std::cerr << "MD5 计算异常：" << e.what() << "\n";
      return "";
    } catch (...) {
      std::cerr << "MD5 计算发生未知异常。" << "\n";
      return "";
    }
  }

  std::vector<uint8_t> ComputeFileBinaryHash(const std::string& filePath) {
    // 计算前先检查文件是否存在
    std::error_code ec;
    if (!std::filesystem::exists(filePath, ec)) {
      std::cerr << "错误：文件不存在 - " << filePath << "\n";
      return {};
    }

    try {
      // 调用 QuickDigest5 的静态方法获取二进制哈希值（16 字节）
      return QuickDigest5::digestFile(filePath);
    } catch (const std::exception& e) {
      std::cerr << "MD5 计算异常：" << e.what() << "\n";
      return {};
    } catch (...) {
      std::cerr << "MD5 计算发生未知异常。" << "\n";
      return {};
    }
  }

}  // namespace my_md5
