#include "Menu.h"
#include <iostream>

void Menu::displayMenu() {
  system("cls");
  std::cout << " ---------------------------------" << std::endl;
  std::cout << "|         ��ͼ����ϵͳ�˵�        |" << std::endl;
  std::cout << "|---------------------------------|" << std::endl;
  std::cout << "| 1. �鿴������ͼ������Ϣ         |" << std::endl;
  std::cout << "| 2. ��ӳ���                     |" << std::endl;
  std::cout << "| 3. ɾ������                     |" << std::endl;
  std::cout << "| 4. ��ӵ�·                     |" << std::endl;
  std::cout << "| 5. ɾ����·                     |" << std::endl;
  std::cout << "| 6. ���ҳ��е����ڳ���           |" << std::endl;
  std::cout << "| 7. ���ҳ���֮������·��       |" << std::endl;
  std::cout << "| 8. �˳�ϵͳ                     |" << std::endl;
  std::cout << " ---------------------------------" << std::endl;
  std::cout << "����������ѡ��1-8����";
}


void Menu::displaySubmenuPrint() {
  system("cls");
  std::cout << " ---------------------------------" << std::endl;
  std::cout << "|         �鿴��ͼϵͳ��Ϣ        |" << std::endl;
  std::cout << "|---------------------------------|" << std::endl;
  std::cout << "| 1. �ڽӱ�                       |" << std::endl;
  std::cout << "| 2. �ڽӾ���                     |" << std::endl;
  std::cout << "| 3. ���ز˵�                     |" << std::endl;
  std::cout << " ---------------------------------" << std::endl;
  std::cout << "����������ѡ��1-3����";
}

