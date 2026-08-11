#ifndef LOGGER_LOGGER_H
#define LOGGER_LOGGER_H

#include <cstdint>
#include <string>

namespace logger {
  // 日志级别（数值越大越严重）
  enum class Level : std::uint8_t { LG_DEBUG, LG_INFO, LG_WARNING, LG_ERROR };

  // 初始化日志模块（在 main 开头调用一次；不调用则使用默认配置）
  // minLevel:    最低输出级别，低于该级别的日志将被丢弃
  // logFilePath: 日志文件完整路径；为空字符串则仅输出到控制台
  void Init(Level minLevel, const std::string& logFilePath = "");

  // 各级别日志输出，msg 为 UTF-8 编码的完整日志内容
  void Debug(const std::string& msg);
  void Info(const std::string& msg);
  void Warning(const std::string& msg);
  void Error(const std::string& msg);
}  // namespace logger

#endif  // LOGGER_LOGGER_H
