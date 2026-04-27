
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// int** is used because the assignment requires a dynamically allocated 2D array of integers
int** allocateImage(int rows, int cols);
void freeImage(int** image, int rows);
void printImage(int** image, int rows, int cols);

// ── allocateImage ─────────────────────────────────────────────────────────────
int** allocateImage(int rows, int cols)
{
    int** image = new int*[rows];

    for (int i = 0; i < rows; i++)
    {
        image[i] = new int[cols];
    }

    return image;
}

// ── freeImage ─────────────────────────────────────────────────────────────────
void freeImage(int** image, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        delete[] image[i];
    }

    delete[] image;
}

// ── printImage ────────────────────────────────────────────────────────────────
void printImage(int** image, int rows, int cols)
{
    cout << "\n+-- Image Grid (" << rows << " x " << cols << ") --+" << endl;

    for (int i = 0; i < rows; i++)
    {
        cout << "| ";

        for (int j = 0; j < cols; j++)
        {
            cout << image[i][j];

            if (j < cols - 1)
            {
                cout << "\t";
            }
        }

        cout << " |" << endl;
    }

    cout << "+----------------------------+" << endl;
}

int main()
{
    srand((unsigned int)time(0));

    int rows, cols;

    cout << "=== Part 1: Dynamic Memory Management ===" << endl;
    cout << "Enter number of rows    : ";
    cin >> rows;
    cout << "Enter number of columns : ";
    cin >> cols;

    int** image = allocateImage(rows, cols);

    cout << "\n[INFO] Image allocated on heap (" << rows << " x " << cols << ")" << endl;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            image[i][j] = rand() % 256;
        }
    }

    cout << "\n--- Image Contents ---";
    printImage(image, rows, cols);

    freeImage(image, rows);

    cout << "\nMemory freed. Program ended." << endl;

    return 0;
}