#include <iostream>
#include <vector>
#include <stack>
#include <omp.h>

using namespace std;

const int MAX_NODES = 100;
vector<int> graph[MAX_NODES];
bool visited[MAX_NODES];

void dfs(int start) {
    stack<int> s;
    s.push(start);

    while (!s.empty()) {
        int node;

        #pragma omp critical
        {
            node = s.top();
            s.pop();
        }

        if (!visited[node]) {
            #pragma omp critical
            visited[node] = true;

            cout << "Visited: " << node << " by thread " << omp_get_thread_num() << endl;

            // Parallel task creation for each neighbor
            #pragma omp parallel
            {
                #pragma omp single
                {
                    for (int neighbor : graph[node]) {
                        if (!visited[neighbor]) {
                            #pragma omp task firstprivate(neighbor)
                            {
                                #pragma omp critical
                                s.push(neighbor);
                            }
                        }
                    }
                }
            }
        }
    }
}

int main() {
    int nodes = 5;

    // Sample undirected graph
    graph[0] = {1, 2};
    graph[1] = {0, 3, 4};
    graph[2] = {0};
    graph[3] = {1};
    graph[4] = {1};

    #pragma omp parallel
    {
        #pragma omp single
        dfs(0);
    }

    return 0;
}
