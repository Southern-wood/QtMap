#include "Menu.h"
#include <iostream>

void Menu::displayMenu() {
  system("cls");
  std::cout << " ---------------------------------" << std::endl;
  std::cout << "|         地图导航系统菜单        |" << std::endl;
  std::cout << "|---------------------------------|" << std::endl;
  std::cout << "| 1. 查看整个地图网络信息         |" << std::endl;
  std::cout << "| 2. 添加城市                     |" << std::endl;
  std::cout << "| 3. 删除城市                     |" << std::endl;
  std::cout << "| 4. 添加道路                     |" << std::endl;
  std::cout << "| 5. 删除道路                     |" << std::endl;
  std::cout << "| 6. 查找城市的相邻城市           |" << std::endl;
  std::cout << "| 7. 查找城市之间的最短路径       |" << std::endl;
  std::cout << "| 8. 退出系统                     |" << std::endl;
  std::cout << " ---------------------------------" << std::endl;
  std::cout << "请输入您的选择（1-8）：";
}


void Menu::displaySubmenuPrint() {
  system("cls");
  std::cout << " ---------------------------------" << std::endl;
  std::cout << "|         查看地图系统信息        |" << std::endl;
  std::cout << "|---------------------------------|" << std::endl;
  std::cout << "| 1. 邻接表                       |" << std::endl;
  std::cout << "| 2. 邻接矩阵                     |" << std::endl;
  std::cout << "| 3. 返回菜单                     |" << std::endl;
  std::cout << " ---------------------------------" << std::endl;
  std::cout << "请输入您的选择（1-3）：";
}

