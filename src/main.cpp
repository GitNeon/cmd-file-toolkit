#include <windows.h>
#include <iostream>
#include <string>

#include "fs/file_opt.h"
#include "logger/logger.h"
#include "ui/menu.h"

namespace
{
    // 设置控制台输出代码页 UTF-8
    void SetupConsoleEncoding()
    {
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);  // 控制台输入编码
    }
}  // namespace

int main()
{
    SetupConsoleEncoding();

    // 初始化日志：输出 DEBUG 及以上级别，同时写入日志文件
    logger::Init(logger::Level::LG_DEBUG, "toolkit.log");

    ui::ShowMainMenu();

    int select = -1;
    while (true)
    {
        std::cin >> select;

        std::cout << "\n" << "选择的功能序号：" << select << " \n";

        switch (select)
        {
            case 0:
                std::cout << "程序退出！\n";
                return 0;
            case 1:
            {
                std::cin.ignore();  // 丢弃上次输入残留的换行符
                std::cout << "请输入原文件完整路径：";
                std::string oldPath;
                std::getline(std::cin, oldPath);

                std::cout << "请输入新文件名（仅文件名，不含路径）：";
                std::string newName;
                std::getline(std::cin, newName);

                fs::RenameFile(oldPath, newName);
                break;
            }
            case 2:
                /* code */
                break;
            case 3:
                /* code */
                break;
            case 4:
                /* code */
                break;
            case 5:
                /* code */
                break;
            case 6:
                /* code */
                break;
            default:
                std::cout << "选择的功能序号不存在，请重新输入！" << "\n";
                continue;
        }

        ui::ShowMainMenu();
    }
}
