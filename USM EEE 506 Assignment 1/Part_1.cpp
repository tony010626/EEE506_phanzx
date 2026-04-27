

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// unsigned char: 8-bit (0-255), exact fit for grayscale pixel values - most memory efficient
unsigned char** allocateImage(int rows, int cols);
void freeImage(unsigned char** image, int rows);
void printImage(unsigned char** image, int rows, int cols);

// ── allocateImage ─────────────────────────────────────────────────────────────
unsigned char** allocateImage(int rows, int cols)
{
    unsigned char** image = new unsigned char*[rows];

    for (int i = 0; i < rows; i++)
        image[i] = new unsigned char[cols];

    return image;
}

// ── freeImage ─────────────────────────────────────────────────────────────────
void freeImage(unsigned char** image, int rows)
{
    for (int i = 0; i < rows; i++)
        delete[] image[i];

    delete[] image;
}

// ── printImage ────────────────────────────────────────────────────────────────
void printImage(unsigned char** image, int rows, int cols)
{
    cout << "\n+-- Image Grid (" << rows << " x " << cols << ") --+" << endl;
    for (int i = 0; i < rows; i++)
    {
        cout << "| ";
        for (int j = 0; j < cols; j++)
        {
            // cast to int so cout prints the numeric value, not the character
            cout << (int)image[i][j];
            if (j < cols - 1) cout << "\t";
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

    unsigned char** image = allocateImage(rows, cols);
    cout << "\n[INFO] Image allocated on heap (" << rows << " x " << cols << ")" << endl;

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            image[i][j] = rand() % 256;

    cout << "\n--- Image Contents ---";
    printImage(image, rows, cols);

    freeImage(image, rows);
    cout << "\n Memory freed. Program ended." << endl;

    return 0;
}