import networkx as net
import matplotlib.pyplot as pyplot

pyplot.rcParams['font.sans-serif'] = 'SimHei'

file = open("mapInformation.txt")
lines = file.readlines()
file.close()

nodes = set()

graph = net.Graph()

for line in lines:
  list = line.split(" ")
  nodes.add(list[0])
  nodes.add(list[1])

graph.add_nodes_from(nodes)

for line in lines:
  list = line.split(" ")
  graph.add_edge(list[0], list[1], weight = list[2], label = list[2])

pyplot.figure(figsize = (10, 10))
pos = net.circular_layout(graph)
net.draw(graph, pos = pos, with_labels = True)
pyplot.savefig("homo", dpi = 5000 , node_size = 1000, alpha = 0.5)
  




