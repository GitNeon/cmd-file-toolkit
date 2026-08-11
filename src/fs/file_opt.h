#ifndef FS_FILE_OPT_H
#define FS_FILE_OPT_H

#include <string>

namespace fs {
  // 单文件重命名
  // oldPath:  原文件完整路径（含文件名）
  // newName:  新文件名（仅文件名，不含路径）
  // 返回 true 表示成功，false 表示失败
  bool RenameFile(const std::string& oldPath, const std::string& newName);
}  // namespace fs

#endif  // FS_FILE_OPT_H
