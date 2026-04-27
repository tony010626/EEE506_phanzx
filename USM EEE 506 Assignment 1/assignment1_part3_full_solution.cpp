/*
 The main execution part
*/

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
void applyFilter(int** image, int rows, int cols, int adjustmentValue)
{
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
void applyFilter(int** image, int rows, int cols, int* rowExposure)
{
    for (int i = 0; i < rows; i++)
    {
        int exposure = rowExposure[i];

        for (int j = 0; j < cols; j++)
        {
            image[i][j] = image[i][j] + exposure;
        }
    }
}

// ── main ──────────────────────────────────────────────────────────────────────
int main()
{
    srand((unsigned int)time(0));

    // Step 1: Prompt user for image dimensions
    int rows, cols;

    cout << "=== EEE506 Assignment 1 - Embedded Image Processing ===" << endl;
    cout << "Enter number of rows    : ";
    cin >> rows;
    cout << "Enter number of columns : ";
    cin >> cols;

    // Step 2: Dynamically allocate 2D image and fill with random pixels 0-255
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

    // Step 3: Dynamically allocate 1D rowExposure array and fill with values
    int* rowExposure = new int[rows];

    cout << "\n[INFO] Row exposure values: ";

    for (int i = 0; i < rows; i++)
    {
        rowExposure[i] = (i + 1) * 10;   // 10, 20, 30, ...
        cout << rowExposure[i];

        if (i < rows - 1)
        {
            cout << ", ";
        }
    }

    cout << endl;

    // Step 4a: Apply Version 1 - Uniform Brightness
    cout << "\n--- Before Uniform Brightness Filter ---";
    printImage(image, rows, cols);

    applyFilter(image, rows, cols, 50);

    cout << "\n--- After Uniform Brightness Filter ---";
    printImage(image, rows, cols);

    // Step 4b: Apply Version 3 - Row-Specific Exposure
    cout << "\n--- Before Row-Specific Exposure Filter ---";
    printImage(image, rows, cols);

    applyFilter(image, rows, cols, rowExposure);

    cout << "\n--- After Row-Specific Exposure Filter ---";
    printImage(image, rows, cols);

    // Step 5: Free all allocated memory
    freeImage(image, rows);
    delete[] rowExposure;

    cout << "\n[INFO] All memory freed. Program ended." << endl;

    return 0;
}