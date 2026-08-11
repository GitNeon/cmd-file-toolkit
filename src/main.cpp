#include <windows.h>
#include <cctype>
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

    // 简短操作提示：不刷完整菜单，减少屏幕滚动
    void ShowShortPrompt()
    {
        std::cout << "\n请输入功能编号（M=查看菜单, 0=退出）：";
    }
}  // namespace

int main()
{
    SetupConsoleEncoding();

    // 初始化日志：输出 DEBUG 及以上级别，同时写入日志文件
    logger::Init(logger::Level::LG_DEBUG, "toolkit.log");

    // 首次启动显示完整菜单
    ui::ShowMainMenu();
    ShowShortPrompt();

    std::string input;
    while (true)
    {
        std::getline(std::cin, input);

        // 空输入跳过
        if (input.empty())
        {
            ShowShortPrompt();
            continue;
        }

        // 按 M 键显示完整菜单
        if (input.size() == 1 && std::toupper(input[0]) == 'M')
        {
            ui::ShowMainMenu();
            ShowShortPrompt();
            continue;
        }

        // 尝试解析为整数
        int select = -1;
        try
        {
            std::size_t pos = 0;
            select          = std::stoi(input, &pos);
            // 输入必须是纯数字，不允许 "1abc" 这种部分解析
            if (pos != input.size())
            {
                throw std::invalid_argument("非纯数字输入");
            }
        }
        catch (...)
        {
            std::cout << "输入无效，请重新输入！\n";
            ShowShortPrompt();
            continue;
        }

        std::cout << "\n"
                  << "选择的功能序号：" << select << " \n";

        switch (select)
        {
            case 0:
                std::cout << "程序退出！\n";
                return 0;
            case 1:
            {
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
            case 3:
            case 4:
            case 5:
            case 6:
                std::cout << "该功能尚未实现，敬请期待。\n";
                break;
            default:
                std::cout << "选择的功能序号不存在，请重新输入！\n";
                break;
        }

        // 功能执行完毕，显示简短提示，等待下一次输入
        ShowShortPrompt();
    }
}
