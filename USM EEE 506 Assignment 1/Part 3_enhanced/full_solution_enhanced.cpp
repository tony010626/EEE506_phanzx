#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int** allocateImage(int rows, int cols);
void freeImage(int** image, int rows);
void printImage(int** image, int rows, int cols);
void applyFilter(int** image, int rows, int cols, int adjustmentValue);
void applyFilter(int** image, int rows, int cols, int* rowExposure);

int** allocateImage(int rows, int cols)
{
    int** image = new int*[rows];

    for (int i = 0; i < rows; i++)
    {
        image[i] = new int[cols];
    }

    return image;
}

void freeImage(int** image, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        delete[] image[i];
    }

    delete[] image;
}

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

void applyFilter(int** image, int rows, int cols, int adjustmentValue)
{
    for (int i = 0; i < rows; i++)
    {
        int* rowPtr = image[i];

        for (int j = 0; j < cols; j++)
        {
            int result = *(rowPtr + j) + adjustmentValue;

            if (result > 255)
            {
                *(rowPtr + j) = 255;
            }
            else
            {
                *(rowPtr + j) = result;
            }
        }
    }
}

void applyFilter(int** image, int rows, int cols, int* rowExposure)
{
    for (int i = 0; i < rows; i++)
    {
        int exposure = rowExposure[i];

        for (int j = 0; j < cols; j++)
        {
            int result = image[i][j] + exposure;

            if (result > 255)
            {
                image[i][j] = 255;
            }
            else
            {
                image[i][j] = result;
            }
        }
    }
}

int main()
{
    srand((unsigned int)time(0));

    int rows, cols;

    cout << "=== EEE506 Assignment 1 - Embedded Image Processing ===" << endl;
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

    cout << "\n--- Before Uniform Brightness Filter ---";
    printImage(image, rows, cols);

    applyFilter(image, rows, cols, 50);

    cout << "\n--- After Uniform Brightness Filter ---";
    printImage(image, rows, cols);

    cout << "\n--- Before Row-Specific Exposure Filter ---";
    printImage(image, rows, cols);

    applyFilter(image, rows, cols, rowExposure);

    cout << "\n--- After Row-Specific Exposure Filter ---";
    printImage(image, rows, cols);

    freeImage(image, rows);
    delete[] rowExposure;

    cout << "\n[INFO] All memory freed. Program ended." << endl;

    return 0;
}