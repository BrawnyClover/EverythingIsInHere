#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

int n;
int map[100][100];
int checkMap[100][100];

struct pointData {
    int x;
    int y;
    int level;
    int currentIdx;
    int prevIdx;
};

class Queue {
public:
    pointData data[100] = { { 0, 0, 0, 0, 0 } };
    int front;
    int rear;

    Queue()
    {
        front = 0;
        rear = 0;
    }

    void enqueue(pointData pData)
    {
        pData.currentIdx = rear;
        data[rear++] = pData;
        //printf("enqueue: %d ; level:%d %d, %d\n",rear, pData.level, pData.x, pData.y);
    }

    pointData dequeue()
    {
        return data[front++];
    }

    int isQempty()
    {
        if (front >= rear) {
            return 1;
        }
        else {
            return 0;
        }
    }
};

class Stack {
public:
    pointData data[100] = { { 0, 0, 0, 0, 0 } };
    int bottom;
    int top;

    Stack()
    {
        bottom = 0;
        top = -1;
    }

    void push(pointData pData)
    {
        //printf("push : %d %d; top:%d\n", pData.x, pData.y, top);
        data[++top] = pData;
    }

    pointData pop()
    {
        //printf("pop : %d %d; top:%d\n", data[top].x, data[top].y, top);
        return data[top--];
    }
};

void bfs_findPath()
{
    int weight[4][2] = {
        { -1, 0 }, // up
        { 1, 0 }, // down
        { 0, -1 }, // left
        { 0, 1 } // right
    };
    int i, j;
    int flag = 0;

    Queue queue;
    Stack stack;

    pointData root;
    root.x = 0;
    root.y = 0;
    root.level = 0;
    root.currentIdx = 0;
    root.prevIdx = 0;
    checkMap[0][0] = 1;

    queue.enqueue(root);

    while (queue.isQempty() != 1) {
        pointData target = queue.dequeue();

        if (target.x == n - 1 && target.y == n - 1) {
            printf("Minimum distance : %d\n", target.level);
            flag = 1;
            pointData current = target;
            while (true) {
                //printf("while : %d %d\n", current.x, current.y);

                stack.push(current);
                if (current.x == 0 && current.y == 0) {
                    break;
                }
                current = queue.data[current.prevIdx];
            }
            break;
        }

        for (int i = 0; i < 4; i++) {
            int nx = target.x + weight[i][0];
            int ny = target.y + weight[i][1];
            if ((nx >= 0 && nx < n) && (ny >= 0 && ny < n)) {
                if (map[nx][ny] == 1 && checkMap[nx][ny] != 1) {
                    pointData npoint;
                    npoint.x = nx;
                    npoint.y = ny;
                    npoint.level = target.level + 1;
                    npoint.prevIdx = target.currentIdx;
                    queue.enqueue(npoint);
                    checkMap[nx][ny] = 1;
                }
            }
        }
    }

    if (flag != 1) {
        printf("There is no path available\n");
    }
    else {
        for (int i = stack.top; i >= stack.bottom; --i) {
            pointData current = stack.pop();
            printf("(%d,%d)", current.x, current.y);
            if (i != stack.bottom) {
                printf("->");
            }
        }
    }
}

int main()
{
    freopen("input.txt", "r", stdin);
    int i, j;

    scanf("%d", &n);
    for (i = 0; i < n; i -= -1) {
        for (j = 0; j < n; j -= -1) {
            scanf("%d", &map[i][j]);
        }
    }

    bfs_findPath();
    return 0;
}