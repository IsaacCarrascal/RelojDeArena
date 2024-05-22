// RelojesDeArena.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
const int MAX_ROWS = 100;
const int MAX_COLS = 100;
using namespace std;

class Numbers {
public:
    Numbers() {
        readFile();
    }
    int readFile(){
        ifstream infile("data.txt");
        // Check if file opened successfully
        if (!infile) {
            cerr << "Error opening file!" << endl;
            return 1;
        }
        while (infile >> temp) {
            // Check if number of elements exceeds array dimensions
            if (rows >= MAX_ROWS || cols >= MAX_COLS) {
                cerr << "Error: Too many elements in the file!" << endl;
                return 1;
            }

            array[rows][cols] = temp;
            cols++;
            if (infile.peek() == '\n') {
                rows++;
                cols = 0;
                infile.ignore();
            }
        }
        rows++;
        infile.close();
    }

    int getRows() {
        return rows;
    }
    int getColumns() {
        return cols;
    }

    int getNumber(int col, int row) {
        return array[row][col];
    }
private:
    int array[MAX_ROWS][MAX_COLS];
    int rows = 0, cols = 0;
    int temp;
};

class HourGlass {
public:
    void setSum(Numbers number, int row, int column) {
        for (int i = column - 1; i <= column + 1; i++) {
            sum += number.getNumber(i, row - 1);
        }
        for (int i = column - 1; i <= column + 1; i++) {
            sum += number.getNumber(i, row + 1);
        }
        sum += number.getNumber(column, row);
   }

    int getSum() {
        return sum;
    }
private: 
    int sum;
};

class Calculator {
public:
    Calculator() {
        Numbers numbers;
        if (numbers.getColumns() < 3 || numbers.getRows() < 3) {
            cout << "Matriz demasiado pequeña. Min # de filas y columnas: 3" << endl;
        }
        else {
            TotalHourglasses = (numbers.getColumns() - 2) * (numbers.getRows() - 2);
            vector<HourGlass> hourglasses(TotalHourglasses);
            for (int i = 1; i < numbers.getRows() - 1; i++) {
                for (int j = 1; j < numbers.getColumns()-1; j++) {
                    hourglasses[counter].setSum(numbers, i, j);
                    counter++;

                }
            }
            setSmaller(hourglasses);
        }

    }

    void setSmaller(vector<HourGlass> hourglasses) {
        int smaller = hourglasses[0].getSum();
        for (int i = 1; i < TotalHourglasses; i++) {
            if (hourglasses[i].getSum() < smaller)
                smaller = hourglasses[i].getSum();
        }
        cout << "Valor menor: " << smaller << endl;
    }

private:
    int counter = 0;
    int TotalHourglasses=0;
};

class Program{
public:
    static void run() {
        int choice = 0;
        while (choice != 2) {
            system("cls");
            cout << "Calculador de relojes de arena" << endl;
            cout << "1. Calcular" << endl;
            cout << "2. salir" << endl;
            choice = getValidInt();
            switch (choice) {
            case 1: {
                Calculator calculator;
                break;
            }
            case 2: {
                cout << "Hasta luego :)" << endl;
                break;
            }
            default: {
                cout << "Opcion no valida" << endl;
            }
            }
            system("pause");
        }
    }

    static int getValidInt() {
        int number;

        while (!(std::cin >> number)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return 0;
        }

        return number;
    }
};
int main()
{
    Program::run();
}

