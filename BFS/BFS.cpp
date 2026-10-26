#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <string>
#include <windows.h>

int** create_two_array(int rows, int columns);
void fill_two_array(int** array, int rows, int columns);
void delete_two_array(int** array_address, int rows);

int main(int argc, char* argv[])
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int rows{}, columns{}, V{};
    std::ifstream input_file{ "input.txt" };
    if (!input_file.is_open())
    {
        std::cerr << "Не удалось открыть input.txt\n";
        return 1;
    }
    input_file >> rows;
    if (!input_file)
    {
        std::cerr << "Не удалось прочитать количество вершин из input.txt\n";
        return 1;
    }
    columns = rows;
    input_file.close();
    int** array{ create_two_array(rows, columns) };
    fill_two_array(array, rows, columns);   
    std::cout << "В графе " << rows << " вершин.Введите номер вершины, с которой начнётся обход : " << std::endl;
    std::cin >> V;
    
    while (V < 1 || V > rows)
    {
        std::cerr << "Неверный номер вершины. Введите номер вершины, с которой начнётся обход : ";
        std::cin >> V;
    }
    --V;
        
    std::cout << "Порядок обхода вершин: ";
    std::vector<bool> visited(rows, false);
    std::queue<int> order;    
    if (visited[V] == false)
        {
            order.push(V);
            visited[V] = true;

            while (!order.empty())
            {
                int vertex = order.front();
                order.pop();
                std::cout << vertex + 1 << ' ';
                visited[vertex] = true;
                for (int column{}; column <= columns; ++column)
                {

                    if ((array[vertex][column] == 1) && (!visited[column]))
                    {
                        visited[column] = true;
                        order.push(column);
                    }                
                }              
            }
        }
    
   

    delete_two_array(array, rows);

    return EXIT_SUCCESS;
}

int** create_two_array(int rows, int columns)
{
    int** integers{ new int* [rows] };
    for (int row{}; row < rows; ++row)
    {
        integers[row] = new int[columns] {};
    }
    return integers;
}

void fill_two_array(int** array_address, int rows, int columns)
{
    std::fstream input_file;
    input_file.open("input.txt", std::fstream::in);
    if (input_file.is_open())
    {
        int N{};
        input_file >> N;
        for (int row{}; row < rows; ++row)
        {
            for (int column{ 0 }; column < columns; ++column)
            {
                int temp{};

                input_file >> temp;
                array_address[row][column] = temp;
            }
        }
    }
    input_file.close();
}


void delete_two_array(int** array_address, int rows)
{
    for (int current_row{}; current_row < rows; ++current_row)
    {
        delete[] array_address[current_row];
    }
    delete[] array_address;
}