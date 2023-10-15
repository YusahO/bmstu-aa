#include "algorithms.h"

template <typename T>
static T min(T x, T y, T z)
{
    return std::min(x, std::min(y, z));
}

int LevNonRec(const std::wstring &word1, const std::wstring &word2, bool verbose)
{
    int len1 = word1.length();
    int len2 = word2.length();

    int **mat = Matrix::Allocate(len1 + 1, len2 + 1);
    if (!mat)
        return -1;

    mat[0][0] = 0;
    for (int i = 0; i <= len1; ++i)
    {
        for (int j = 0; j <= len2; ++j)
        {
            if (i == 0)
            {
                mat[i][j] = j;
            }
            else if (j == 0)
            {
                mat[i][j] = i;
            }
            else
            {
                int subsCost = word1[j - 1] != word2[i - 1];

                mat[i][j] = min(
                    mat[i - 1][j] + 1,
                    mat[i][j - 1] + 1,
                    mat[i - 1][j - 1] + subsCost);
            }
        }
    }

    if (verbose)
        Matrix::Print(mat, word1, word2);

    int res = mat[len1][len2];
    Matrix::Free(mat, len1);

    return res;
}

int DamLevNonRec(const std::wstring &word1, const std::wstring &word2, bool verbose)
{
    int len1 = word1.length();
    int len2 = word2.length();

    int **mat = Matrix::Allocate(len1 + 1, len2 + 1);
    if (!mat)
        return -1;

    mat[0][0] = 0;
    for (int i = 0; i <= len1; ++i)
    {
        for (int j = 0; j <= len2; ++j)
        {
            if (i == 0)
            {
                mat[i][j] = j;
            }
            else if (j == 0)
            {
                mat[i][j] = i;
            }
            else
            {
                int subsCost = word1[i - 1] != word2[j - 1];

                mat[i][j] = min(
                    mat[i - 1][j] + 1,
                    mat[i][j - 1] + 1,
                    mat[i - 1][j - 1] + subsCost);

                if (word1[i - 2] == word2[j - 1] && word1[i - 1] == word2[j - 2])
                {
                    mat[i][j] = std::min(
                        mat[i][j],
                        mat[i - 2][j - 2] + 1);
                }
            }
        }
    }

    if (verbose)
        Matrix::Print(mat, word1, word2);

    int res = mat[len1][len2];
    Matrix::Free(mat, len1);

    return res;
}

int DamLevRec(const std::wstring &word1, const std::wstring &word2, int ind1, int ind2)
{
    if (ind1 == 0)
        return ind2;
    if (ind2 == 0)
        return ind1;

    if (word1[ind1 - 1] == word2[ind2 - 1])
        return DamLevRec(word1, word2, ind1 - 1, ind2 - 1);

    int res = 1 + min(
        DamLevRec(word1, word2, ind1, ind2 - 1),       // удаление
        DamLevRec(word1, word2, ind1 - 1, ind2),       // вставка
        DamLevRec(word1, word2, ind1 - 1, ind2 - 1));  // замена

    if (ind1 > 1 && ind2 > 1 && word1[ind1 - 1] == word2[ind2 - 2] && word1[ind1 - 2] == word2[ind2 - 1])
        res = std::min(res, DamLevRec(word1, word2, ind1 - 2, ind2 - 2) + 1);

    return res;
}

int DamLevRecCache(const std::wstring &word1, const std::wstring &word2, int ind1, int ind2, int **dp)
{
    if (ind1 == 0)
        return ind2;
    if (ind2 == 0)
        return ind1;

    if (dp[ind1 - 1][ind2 - 1] != -1)
        return dp[ind1 - 1][ind2 - 1];

    if (word1[ind1 - 1] == word2[ind2 - 1])
        return dp[ind1 - 1][ind2 - 1] = DamLevRecCache(word1, word2, ind1 - 1, ind2 - 1, dp);

    int res = dp[ind1 - 1][ind2 - 1] = 1 + min(
        DamLevRecCache(word1, word2, ind1, ind2 - 1, dp),       // удаление
        DamLevRecCache(word1, word2, ind1 - 1, ind2, dp),       // вставка
        DamLevRecCache(word1, word2, ind1 - 1, ind2 - 1, dp));  // замена  

    if (ind1 > 1 && ind2 > 1 && word1[ind1 - 1] == word2[ind2 - 2] && word1[ind1 - 2] == word2[ind2 - 1])
        res = std::min(res, DamLevRecCache(word1, word2, ind1 - 2, ind2 - 2, dp) + 1);

    return res;
}
