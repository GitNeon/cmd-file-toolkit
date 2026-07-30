#include <windows.h>
#include <iostream>
#include "ui/menu.h"


// 设置控制台输出代码页 UTF-8
void SetupConsoleEncoding()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);  // 控制台输入编码
}

int main()
{
    SetupConsoleEncoding();

    ui::ShowMainMenu();

    int select;
    while (true)
    {
        std::cin >> select;

        std::cout << "\n" << "选择的功能序号：" << select << " \n";

        switch (select)
        {
            case 0:
                /* code */
                break;
            case 1:
                /* code */
                break;
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
    }
}
