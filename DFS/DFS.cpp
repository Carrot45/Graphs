#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

bool read_from_file(const string& filename,
    int& n,
    vector<vector<int>>& matrix);

void dfs(int u,
    const vector<vector<int>>& matrix,
    vector<bool>& visited);

int main(int argc, char* argv[])
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int n = 0;
    vector<vector<int>> matrix;

    if (!read_from_file("in.txt", n, matrix))
        return 1;

    vector<bool> visited(n, false);

    // обход всех компонент связности
    for (int i = 0; i < n; ++i)
        if (!visited[i])
            dfs(i, matrix, visited);

    cout << '\n';
    return EXIT_SUCCESS;
}

bool read_from_file(const string& filename,
    int& n,
    vector<vector<int>>& matrix)
{
    ifstream fin(filename);
    if (!fin.is_open())
    {
        cerr << "Не удалось открыть файл: " << filename << '\n';
        return false;
    }

    if (!(fin >> n) || n <= 0)
    {
        cerr << "Не удалось прочитать количество вершин\n";
        return false;
    }

    matrix.assign(n, vector<int>(n, 0));

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (!(fin >> matrix[i][j]))
            {
                cerr << "Ошибка чтения элемента [" << i << "][" << j << "]\n";
                return false;
            }

    return true;
}

void dfs(int u,
    const vector<vector<int>>& matrix,
    vector<bool>& visited)
{
    visited[u] = true;
    cout << u << ' ';                  // порядок обхода

    const int n = static_cast<int>(matrix.size());
    for (int v = 0; v < n; ++v) {
        if (matrix[u][v] == 0) continue;
        if (!visited[v])
            dfs(v, matrix, visited);
    }
}