#include "file_opt.h"

#include <filesystem>
#include <system_error>

#include "logger/logger.h"

namespace fs {
  bool RenameFile(const std::string& oldPath, const std::string& newName) {
    namespace stdfs = std::filesystem;

    const stdfs::path OLD_P(oldPath);

    // 检查原文件是否存在
    std::error_code ec;
    if (!stdfs::exists(OLD_P, ec)) {
      logger::Error("文件不存在 - " + oldPath);
      return false;
    }

    // 构造新文件路径（保持原目录不变）
    const stdfs::path NEW_P = OLD_P.parent_path() / newName;

    // 检查目标文件名是否已存在
    if (stdfs::exists(NEW_P, ec)) {
      logger::Error("目标文件名已存在 - " + NEW_P.string());
      return false;
    }

    // 执行重命名
    stdfs::rename(OLD_P, NEW_P, ec);
    if (ec) {
      logger::Error("重命名失败 - " + ec.message());
      return false;
    }

    logger::Info("文件已重命名为 " + newName);
    return true;
  }
}  // namespace fs
