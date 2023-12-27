#include "Graph.h"
#include <QList>
#include <QString>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <set>

void Graph::init() {
  std::ifstream file("E:/C++/QtMap/map/mapInformation.txt");
  int n, m;
  std::string city, cityA, cityB;
  int distance;
  file >> n;
  while (n--) {
    file >> city;
    if (!cityIndices.count(city))
      addCity(city);
  }
  file >> m;
  while (m--) {
    file >> cityA >> cityB >> distance;
    addRoad(cityA, cityB, distance);
  }
  logInfo->addItem("[成功] ：地图初始化完成");
  logInfo->scrollToBottom();
}

Graph::Graph(QListWidget *logInfo, QListWidget *listWidget) {
  this->logInfo = logInfo;
  this->listWidget = listWidget;
}

void Graph::output() {
  std::ofstream file("E:\\C++\\QtMap\\map\\mapInformation.txt");
  file << cities.size() << "\n";
  int m = 0;
  for (int i = 0; i < cities.size(); i++) {
    file << cities[i] << " \n"[i == cities.size() - 1];
    m += adjacencyList[i].size();
  }
  file << m / 2 << "\n";
  for (int i = 0; i < cities.size(); i++) {
    for (auto const &edge : adjacencyList[i]) {
      if (edge.first > i) {
        file << indexCity[i] << " " << indexCity[edge.first] << " "
             << edge.second << std::endl;
      }
    }
  }
  file.close();
}

Graph::~Graph() { output(); }

void Graph::addCity(const std::string &cityName) {
  if (!cityIndices.count(cityName)) {
    cities.emplace_back(cityName);
    int index = cities.size() - 1; // 新城市的索引
    cityIndices[cityName] = index; // 存储城市名称和其索引的映射关系
    indexCity[index] = cityName;
    adjacencyList.emplace_back();
    logInfo->addItem(
        QString::fromStdString("[成功] ：" + cityName + "已添加到地图"));
  } else {
    logInfo->addItem(QString::fromStdString("[错误] ： 该城市已存在"));
  }
}

void Graph::removeCity(const std::string &cityName) {
  auto it = cityIndices.find(cityName);
  if (it != cityIndices.end()) {
    int index = it->second; // 要删除的城市在 cities 中的索引
    auto indexCityIt = indexCity.find(index);
    cities.erase(cities.begin() + index); // 删除城市
    cityIndices.erase(it); // 删除城市名称和索引的映射关系
    indexCity.erase(indexCityIt);
    adjacencyList.erase(adjacencyList.begin() + index); // 删除邻接表中的相关边
    // 更新其他城市的索引信息
    for (auto &pair : cityIndices) {
      if (pair.second > index) {
        pair.second--; // 减小索引以保持正确性
        indexCity[pair.second] = pair.first;
      }
    }
    // 在邻接表中更新其他城市的边信息
    for (auto &list : adjacencyList) {
      for (auto it = list.begin(); it != list.end(); it++) {
        if (it->first == index) {
          auto ptr = it--;
          list.erase(ptr);
        } else if (it->first > index) {
          it->first--; // 减小索引以保持正确性
        }
      }
    }
    logInfo->addItem(QString::fromStdString("[成功] ： " + cityName +
                                            " 及其相连的道路已被移除"));
  } else {
    logInfo->addItem(
        QString::fromStdString("[错误] ： " + cityName + " 不存在"));
  }
  logInfo->scrollToBottom();
}

void Graph::addRoad(const std::string &cityA, const std::string &cityB,
                    int distance) {
  bool flag = true;
  logInfo->addItem(QString::fromStdString("正在查询城市 ： " + cityA));
  if (!cityIndices.count(cityA)) {
    logInfo->addItem(QString::fromStdString("[错误] ： " + cityA + " 不存在"));
    flag = false;
  } else {
    logInfo->addItem(QString::fromStdString("[成功] ： " + cityA + " 已找到"));
  }

  logInfo->addItem(QString::fromStdString("正在查询城市 ： " + cityB));
  if (!cityIndices.count(cityB)) {
    logInfo->addItem(QString::fromStdString("[错误] ： " + cityB + " 不存在"));
    flag = false;
  } else {
    logInfo->addItem(QString::fromStdString("[成功] ： " + cityB + " 已找到"));
  }
  if (!flag) {
    return;
  }
  auto itA = cityIndices.find(cityA);
  auto itB = cityIndices.find(cityB);
  if (itA == itB) {
    logInfo->addItem("[错误] ： 本系统不允许建立自环");
  } else if (distance <= 0) {
    logInfo->addItem("[错误] ： 城市间道路的长度必须是正数");
  } else if (itA != cityIndices.end() && itB != cityIndices.end()) {
    int indexA = itA->second;
    int indexB = itB->second;
    adjacencyList[indexA].emplace_back(std::make_pair(indexB, distance));
    adjacencyList[indexB].emplace_back(std::make_pair(indexA, distance));
    logInfo->addItem(QString::fromStdString(
        "[成功] ： 在 " + cityA + " 与 " + cityB + " 之间建立了一条长为 " +
        std::to_string(distance) + " 道路"));
  }
}

void Graph::removeRoad(const std::string &cityA, const std::string &cityB) {

  bool flag = true;
  logInfo->addItem(QString::fromStdString("正在查询城市 ： " + cityA));
  if (!cityIndices.count(cityA)) {
    logInfo->addItem(QString::fromStdString("[错误] ： " + cityA + " 不存在"));
    flag = false;
  } else {
    logInfo->addItem(QString::fromStdString("[成功] ： " + cityA + " 已找到"));
  }

  logInfo->addItem(QString::fromStdString("正在查询城市 ： " + cityB));
  if (!cityIndices.count(cityB)) {
    logInfo->addItem(QString::fromStdString("[错误] ： " + cityB + " 不存在"));
    flag = false;
  } else {
    logInfo->addItem(QString::fromStdString("[成功] ： " + cityB + " 已找到"));
  }
  if (!flag) {
    return;
  }

  auto itA = cityIndices.find(cityA);
  auto itB = cityIndices.find(cityB);
  if (itA != cityIndices.end() && itB != cityIndices.end()) {
    int indexA = itA->second;
    int indexB = itB->second;
    adjacencyList[indexA].remove_if([indexB](std::pair<int, int> element) {
      return element.first == indexB;
    });
    adjacencyList[indexB].remove_if([indexA](std::pair<int, int> element) {
      return element.first == indexA;
    });
    logInfo->addItem(QString::fromStdString("[成功] ： " + cityA + " 与 " +
                                            cityB + "之间的道路已被移除"));
  }
}

PathInfo Graph::dijkstraShortestPath(const std::string &startCity,
                                     const std::string &endCity) {
  // 检验数据合法性
  const int INF = 1e9;

  bool flag = true;
  logInfo->addItem(QString::fromStdString("正在查询城市 ： " + startCity));
  if (!cityIndices.count(startCity)) {
    logInfo->addItem(
        QString::fromStdString("[错误] ： " + startCity + " 不存在"));
    flag = false;
  } else {
    logInfo->addItem(
        QString::fromStdString("[成功] ： " + startCity + " 已找到"));
  }

  logInfo->addItem(QString::fromStdString("正在查询城市 ： " + endCity));
  if (!cityIndices.count(endCity)) {
    logInfo->addItem(
        QString::fromStdString("[错误] ： " + endCity + " 不存在"));
    flag = false;
  } else {
    logInfo->addItem(
        QString::fromStdString("[成功] ： " + endCity + " 已找到"));
  }

  std::vector<std::string> shortestPath;
  std::vector<int> distances;
  int totalDistance = INF;

  if (!flag) {
    return {shortestPath, distances, totalDistance};
  }

  int startIndex = cityIndices[startCity];
  int endIndex = cityIndices[endCity];
  totalDistance = 0;
  // 创建优先队列维护集合 T
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                      std::greater<>>
      pq;
  pq.push(std::make_pair(0, startIndex));

  // 标记该节点是否已经在 S 中
  std::vector<bool> visited(cities.size(), false);
  // dist 数组初始化为正无穷
  std::vector<int> dist(cities.size(), INF);
  std::vector<int> prev(cities.size(), -1);

  // 初始化源点的距离为 9
  dist[startIndex] = 0;

  // 重复执行，直到 T 集合为空
  while (!pq.empty()) {
    int u = pq.top().second;
    pq.pop();

    // 如果该点已经在集合 S 中
    if (visited[u])
      continue;
    visited[u] = true;

    for (auto &edge : adjacencyList[u]) {
      int v = edge.first;
      int weight = edge.second;

      if (!visited[v] && dist[v] > dist[u] + weight) {
        dist[v] = dist[u] + weight;
        prev[v] = u;
        pq.push(std::make_pair(dist[v], v));
      }
    }
  }

  // 如果终点能够到达
  if (prev[endIndex] != -1) {
    int current = endIndex;
    while (current != -1) {
      shortestPath.push_back(cities[current]);
      current = prev[current];
    }
    std::reverse(shortestPath.begin(), shortestPath.end());

    for (size_t i = 0; i < shortestPath.size() - 1; ++i) {
      int cityAIndex = cityIndices[shortestPath[i]];
      int cityBIndex = cityIndices[shortestPath[i + 1]];

      int distance = 0;
      for (const auto &edge : adjacencyList[cityAIndex]) {
        if (edge.first == cityBIndex) {
          distance = edge.second;
          totalDistance += distance;
          break;
        }
      }
      distances.push_back(distance);
    }
  }

  return {shortestPath, distances, totalDistance};
}

void Graph::printAdjacencyMatrix() {
  const int INF = 1e9;
  listWidget->clear();

  listWidget->addItem("邻接矩阵：\n");
  QStringList matrix;

  QString row;
  for (auto &cityName : cities) {
    row += cityName + " ";
  }
  QStringList columns = row.split(" ");
  QString formattedRow = "             ";
  for (const QString &column : columns) {
    formattedRow += QString("%1 ").arg(column, 10 - 2 * column.size());
  }
  listWidget->addItem(formattedRow); // 通过序号枚举所有城市，并输出作为表头

  for (int i = 0; i < cities.size(); ++i) { // 通过序号枚举所有城市
    // 将当前城市添加到本行首部
    row = QString::fromStdString(indexCity[i] + " ");
    // 初始化当前城市到所有城市的距离为正无穷
    std::vector<int> distance(cities.size(), INF);
    // 枚举当前城市的所有边并更新城市之间的距离
    for (auto &edge : adjacencyList[i]) {
      distance[edge.first] = std::min(distance[edge.first], edge.second);
    }
    for (int j = 0; j < cities.size(); j++) {
      // 将所有城市之间的距离添加到本行，INF 即为无边
      row += std::to_string(distance[j] == INF ? 0 : distance[j]) + " ";
    }
    matrix << row;
  }

  // 逐行添加矩阵元素到 QListWidget
  foreach (const QString &row, matrix) {
    QStringList columns = row.split(" ");
    QString formattedRow;
    for (const QString &column : columns) {
      formattedRow += QString("%1 ").arg(column, 10 - column.size());
    }
    listWidget->addItem(formattedRow);
  }
}

void Graph::printAdjacencyList() {

  listWidget->clear();
  listWidget->addItem("邻接表：\n");

  QString row;

  // 按照序号枚举所有城市
  for (int i = 0; i < adjacencyList.size(); ++i) {
    row.clear();
    row += indexCity[i] + " -> ";    // 在行首当前城市
    std::set<std::string> neighbors; // 创建 set 容器
    for (const auto &neighbor : adjacencyList[i]) {
      neighbors.insert(indexCity[neighbor.first]);
    }
    for (auto &cityName : neighbors) { // 遍历 set 容器
      row += cityName + " ";
    }
    listWidget->addItem(row);
  }
}

void Graph::printNeighbours(const std::string &cityName) {
  // 对数据在当前地图中的合法性的检验
  logInfo->addItem(QString::fromStdString("正在查询城市 ： " + cityName));
  if (!cityIndices.count(cityName)) {
    logInfo->addItem(
        QString::fromStdString("[错误] ： " + cityName + " 不存在"));
  } else {
    logInfo->addItem(
        QString::fromStdString("[成功] ： " + cityName + " 已找到"));
    listWidget->clear();
    listWidget->addItem(QString::fromStdString(cityName + "的相邻城市："));
    std::set<std::string> st;
    for (const auto &neighbour : adjacencyList[cityIndices[cityName]]) {
      if (!st.count(indexCity[neighbour.first])) {
        st.insert(indexCity[neighbour.first]);
        listWidget->addItem(
            QString::fromStdString(indexCity[neighbour.first] + " "));
      }
    }
    logInfo->addItem(
        QString::fromStdString("[成功] ：" + cityName + "的相邻城市已找到"));
    logInfo->scrollToBottom();
  }
}
