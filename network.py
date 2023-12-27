import networkx as net
import matplotlib.pyplot as pyplot
import codecs

pyplot.rcParams['font.sans-serif'] = 'SimHei'

graph = net.Graph()

file = open("E:\\C++\\QtMap\\map\\mapInformation.txt", 'r', encoding = 'UTF-8') 

n = file.readline()
line = file.readline().split()
graph.add_nodes_from(line)

m = file.readline()
lines = file.readlines()
edge_labels = dict()

for line in lines:
  list = line.split()
  if (graph.has_edge(list[0], list[1])):
    graph[list[0]][list[1]]['weight'] = min(list[2], graph[list[0]][list[1]]['weight'])
    graph[list[0]][list[1]]['minlen'] = graph[list[0]][list[1]]['weight']
  else:
    graph.add_edge(list[0], list[1], weight = list[2], minlen = list[2])

for edge in graph.edges:
  edge_labels[edge] = graph[edge[0]][edge[1]]['weight']

pyplot.figure(figsize = (10, 5))
pos = net.planar_layout(graph)
net.draw(graph, pos = pos, with_labels = True, node_size = 600, width = 1)
net.draw_networkx_edge_labels(graph, pos, edge_labels = edge_labels)
pyplot.savefig("E:\\C++\\QtMap\\map\\homo", dpi = 100,)

file.close()



