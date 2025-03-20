// graph.c
#include "graph.h"
#include <stdlib.h>
#include <string.h>


void init_graph(Graph *graph) {
    graph->nodes = NULL;
    graph->count = 0;
}

Node *get_or_create_node(Graph *graph, const char *name) {
    // 查找是否已存在
    for (int i = 0; i < graph->count; i++) {
        if (strcmp(graph->nodes[i]->name, name) == 0) {
            return graph->nodes[i];
        }
    }

    // 创建新节点
    Node *node = malloc(sizeof(Node));
    strncpy(node->name, name, 32);
    node->children = NULL;
    node->child_count = 0;
    node->in_degree = 0;

    // 添加到图中
    graph->nodes = realloc(graph->nodes, sizeof(Node *) * (graph->count + 1));
    graph->nodes[graph->count++] = node;

    return node;
}

void add_edge(Graph *graph, const char *target, const char *dependency) {
    Node *target_node = get_or_create_node(graph, target);
    Node *dep_node = get_or_create_node(graph, dependency);

    // 添加依赖关系
    target_node->children = realloc(target_node->children, sizeof(Node *) * (target_node->child_count + 1));
    target_node->children[target_node->child_count++] = dep_node;
    dep_node->in_degree++;  // 依赖节点的入度增加
}

bool topological_sort(Graph *graph, char **order) {
    // 实现Kahn算法
    int front = 0, rear = 0;
    Node **queue = malloc(sizeof(Node *) * graph->count);

    // 初始化队列（入度为0的节点）
    for (int i = 0; i < graph->count; i++) {
        if (graph->nodes[i]->in_degree == 0) {
            queue[rear++] = graph->nodes[i];
        }
    }

    int index = 0;
    while (front < rear) {
        Node *node = queue[front++];
        order[index++] = node->name;

        // 减少子节点的入度
        for (int i = 0; i < node->child_count; i++) {
            Node *child = node->children[i];
            child->in_degree--;
            if (child->in_degree == 0) {
                queue[rear++] = child;
            }
        }
    }

    free(queue);
    return index == graph->count;  // 是否所有节点都被处理（无环）
}