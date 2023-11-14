#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>

#include "matrix.h"
#include "algorithms.h"
#include "measure.h"

static constexpr const char *s_FirstMatrixPath = "prog/matrix_data/matrix_01.txt";
static constexpr const char *s_SecondMatrixPath = "prog/matrix_data/matrix_02.txt";

bool IsPowerOfTwo(int val)
{
    while ((val & 1) != 1)
        val >>= 1;
    return val == 1;
}

int menu()
{
    std::cout << "\n\t\tМеню\n"
        "1. Стандартное умножение матриц.\n"
        "2. Умножение алгоритмом Винограда.\n"
        "3. Умножение оптимизированным алгоритмом Винограда.\n"
        "4. Умножение алгоритмом Штрассена.\n"
        "5. Замерить время для реализованных алгоритмов.\n"
        "6. Редактировать матрицы\n"
        "0. Выход.\n\n"
        "Выберите опцию (0-6): ";

    int choice;
    std::cin >> choice;
    std::cout << std::endl;

    return choice;
}

void MultiplyCommon(const Matrix &m1, const Matrix &m2)
{
    if (m1.rows() == 0)
    {
        std::cout << "Первая матрица имеет недопустимый размер\n";
        return;
    }
    else if (m2.rows() == 0)
    {
        std::cout << "Вторая матрица имеет недопустимый размер\n";
        return;
    }
    else if (m1.columns() != m2.rows())
    {
        std::cout << "Количество столбцов первой матрицы (" << m1.columns() <<
            ") не совпадает с количеством строк второй матрицы (" << m2.rows() << ")\n";
        return;
    }

    std::cout << Multiply::Common(m1, m2);
}

void MultiplyWinograd(const Matrix &m1, const Matrix &m2, Matrix(*Winograd)(const Matrix &m1, const Matrix &m2))
{
    if (m1.rows() == 0)
    {
        std::cout << "Первая матрица имеет недопустимый размер\n";
        return;
    }
    else if (m2.rows() == 0)
    {
        std::cout << "Вторая матрица имеет недопустимый размер\n";
        return;
    }
    else if (m1.rows() != m1.columns() or m2.rows() != m2.columns())
    {
        std::cout << "Матрицы должны быть квадратными\n";
        return;
    }
    else if (m1.rows() != m2.rows())
    {
        std::cout << "Размер первой матрицы (" << m1.rows() << "x" << m1.rows() <<
            ") не совпадает с размером второй (" << m2.rows() << "x" << m2.columns() << ")\n";
        return;
    }
    std::cout << Winograd(m1, m2);
}

void MultiplyStrassen(const Matrix &m1, const Matrix &m2)
{
    if (m1.rows() == 0)
    {
        std::cout << "Первая матрица имеет недопустимый размер\n";
        return;
    }
    else if (m2.rows() == 0)
    {
        std::cout << "Вторая матрица имеет недопустимый размер\n";
        return;
    }
    else if (m1.rows() != m1.columns() or m2.rows() != m2.columns())
    {
        std::cout << "Матрицы должны быть квадратными\n";
        return;
    }
    else if (!IsPowerOfTwo(m1.rows()))
    {
        std::cout << "Размер матриц должен степенью 2\n";
        return;
    }
    std::cout << Multiply::Strassen(m1, m2);
}

int main()
{
    int choice = 0;
    while ((choice = menu()))
    {
        if (choice == 0)
        {
            break;
        }
        else if (choice == 1)
        {
            MultiplyCommon(
                Matrix::fromFile(s_FirstMatrixPath),
                Matrix::fromFile(s_SecondMatrixPath)
            );
        }
        else if (choice == 2)
        {
            MultiplyWinograd(
                Matrix::fromFile(s_FirstMatrixPath),
                Matrix::fromFile(s_SecondMatrixPath),
                Multiply::Winograd
            );
        }
        else if (choice == 3)
        {
            MultiplyWinograd(
                Matrix::fromFile(s_FirstMatrixPath),
                Matrix::fromFile(s_SecondMatrixPath),
                Multiply::WinogradOpt
            );
        }
        else if (choice == 4)
        {
            MultiplyStrassen(
                Matrix::fromFile(s_FirstMatrixPath),
                Matrix::fromFile(s_SecondMatrixPath)
            );
        }
        else if (choice == 5)
        {
            TimeMeasure(0, 100, 100);
            TimeMeasure(1, 100, 100);
            TimeMeasure(2, 128, 100);
        }
        else if (choice == 6)
        {
            for (int c = 0;;)
            {
                std::cout << "Файл какой матрицы необходимо отредактировать? (1 или 2): ";
                std::cin >> c;
                if (c != 1 && c != 2)
                    break;
                std::system((std::string("nano ") +
                    std::string(c == 1 ? s_FirstMatrixPath : s_SecondMatrixPath)).c_str());
            }
        }
        else
        {
            continue;
        }
    }
    return 0;
}
