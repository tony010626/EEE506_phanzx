#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// int** is used because the assignment requires a dynamically allocated 2D array of integers
int** allocateImage(int rows, int cols);
void freeImage(int** image, int rows);
void printImage(int** image, int rows, int cols);
void applyFilter(int** image, int rows, int cols, int adjustmentValue);
void applyFilter(int** image, int rows, int cols, int* rowExposure);

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

// ── applyFilter: Version 1 – Uniform Brightness ───────────────────────────────
// Adds the same brightness adjustment value to every pixel.
void applyFilter(int** image, int rows, int cols, int adjustmentValue)
{
    cout << "\n[Version 1] Uniform Brightness (adjustmentValue = " << adjustmentValue << ")" << endl;

    for (int i = 0; i < rows; i++)
    {
        int* rowPtr = image[i];

        for (int j = 0; j < cols; j++)
        {
            *(rowPtr + j) = *(rowPtr + j) + adjustmentValue;
        }
    }
}

// ── applyFilter: Version 3 – Row-Specific Exposure ────────────────────────────
// Adds rowExposure[i] to every pixel in the i-th row.
void applyFilter(int** image, int rows, int cols, int* rowExposure)
{
    cout << "\n[Version 3] Row-Specific Exposure" << endl;

    for (int i = 0; i < rows; i++)
    {
        int exposure = rowExposure[i];

        for (int j = 0; j < cols; j++)
        {
            image[i][j] = image[i][j] + exposure;
        }
    }
}

int main()
{
    srand((unsigned int)time(0));

    int rows, cols;

    cout << "=== Part 2: Function Overloading & Pointer Manipulation ===" << endl;
    cout << "Enter number of rows    : ";
    cin >> rows;
    cout << "Enter number of columns : ";
    cin >> cols;

    int** image = allocateImage(rows, cols);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            image[i][j] = rand() % 256;
        }
    }

    cout << "\n--- Initial Image ---";
    printImage(image, rows, cols);

    // Version 1 – Uniform Brightness
    cout << "\n--- Before Uniform Brightness ---";
    printImage(image, rows, cols);

    applyFilter(image, rows, cols, 50);

    cout << "\n--- After Uniform Brightness ---";
    printImage(image, rows, cols);

    // Version 3 – Row-Specific Exposure
    int* rowExposure = new int[rows];

    cout << "\n[INFO] Row exposure values: ";

    for (int i = 0; i < rows; i++)
    {
        rowExposure[i] = (i + 1) * 10;
        cout << rowExposure[i];

        if (i < rows - 1)
        {
            cout << ", ";
        }
    }

    cout << endl;

    cout << "\n--- Before Row-Specific Exposure ---";
    printImage(image, rows, cols);

    applyFilter(image, rows, cols, rowExposure);

    cout << "\n--- After Row-Specific Exposure ---";
    printImage(image, rows, cols);

    freeImage(image, rows);
    delete[] rowExposure;

    cout << "\n[INFO] All memory freed. Program ended." << endl;

    return 0;
}