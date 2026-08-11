#include "logger.h"

#include <array>
#include <chrono>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <iostream>
#include <mutex>

namespace logger {
  namespace {
    // 模块内部状态
    std::mutex g_mutex;                  // 保护输出，保证多线程下日志不交叉
    Level g_minLevel = Level::LG_DEBUG;  // 最低输出级别
    std::ofstream g_file;                // 日志文件流（未打开时仅输出控制台）

    // 级别转字符串标签
    const char* LevelTag(Level level) {
      switch (level) {
        case Level::LG_DEBUG:
          return "DEBUG";
        case Level::LG_INFO:
          return "INFO";
        case Level::LG_WARNING:
          return "WARNING";
        case Level::LG_ERROR:
          return "ERROR";
        default:
          return "UNKNOWN";
      }
    }

    // 获取当前时间戳字符串，格式：YYYY-MM-DD HH:MM:SS
    std::string Timestamp() {
      const auto NOW = std::chrono::system_clock::now();
      const auto TIME = std::chrono::system_clock::to_time_t(NOW);
      std::tm local{};
      if (localtime_s(&local, &TIME) != 0) {
        return "1970-01-01 00:00:00";
      }

      std::array<char, 32> buf{};
      static_cast<void>(
          std::snprintf(buf.data(), buf.size(), "%04d-%02d-%02d %02d:%02d:%02d",
                        local.tm_year + 1900, local.tm_mon + 1, local.tm_mday,
                        local.tm_hour, local.tm_min, local.tm_sec));
      return buf.data();
    }

    // 日志输出核心：拼格式化行并写入控制台与文件
    void Log(Level level, const std::string& msg) {
      if (level < g_minLevel) {
        return;
      }

      std::lock_guard<std::mutex> lock(g_mutex);

      const std::string LINE =
          "[" + Timestamp() + "] [" + LevelTag(level) + "] " + msg + "\n";

      // 控制台：WARNING/ERROR 走 stderr，其余走 stdout
      if (level >= Level::LG_WARNING) {
        std::cerr << LINE;
      } else {
        std::cout << LINE;
      }

      if (g_file.is_open()) {
        g_file << LINE;
        g_file.flush();
      }
    }
  }  // namespace

  void Init(Level minLevel, const std::string& logFilePath) {
    std::lock_guard<std::mutex> lock(g_mutex);
    g_minLevel = minLevel;

    if (!logFilePath.empty()) {
      // 二进制模式追加写入，直接写 UTF-8 字节，避免 Windows 文本模式转码
      g_file.open(logFilePath, std::ios::binary | std::ios::app);
    }
  }

  void Debug(const std::string& msg) { Log(Level::LG_DEBUG, msg); }

  void Info(const std::string& msg) { Log(Level::LG_INFO, msg); }

  void Warning(const std::string& msg) { Log(Level::LG_WARNING, msg); }

  void Error(const std::string& msg) { Log(Level::LG_ERROR, msg); }
}  // namespace logger
