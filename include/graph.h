// graph.h
#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

typedef struct Node {
    char name[32];          // 节点名称（目标或依赖）
    struct Node **children; // 子节点（依赖）
    int child_count;        // 子节点数量
    int in_degree;          // 入度（用于拓扑排序）
} Node;

typedef struct {
    Node **nodes;           // 所有节点
    int count;              // 节点总数
} Graph;

// 初始化图
void init_graph(Graph *graph);

// 添加节点或查找已存在的节点
Node *get_or_create_node(Graph *graph, const char *name);

// 添加边（从target指向dependency）
void add_edge(Graph *graph, const char *target, const char *dependency);

// 拓扑排序（Kahn算法）
bool topological_sort(Graph *graph, char **order);

#endif
