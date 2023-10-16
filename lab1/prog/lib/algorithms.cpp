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

    int **mat = Matrix::Allocate(len2 + 1, len1 + 1);
    if (!mat)
        return -1;

    mat[0][0] = 0;
    for (int i = 0; i <= len2; ++i)
    {
        for (int j = 0; j <= len1; ++j)
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
                int cost = (word1[j - 1] == word2[i - 1]) ? 0 : 1;

                mat[i][j] = min(
                    mat[i - 1][j] + 1,
                    mat[i][j - 1] + 1,
                    mat[i - 1][j - 1] + cost);
            }
        }
    }

    if (verbose)
        Matrix::Print(mat, word1, word2);

    int res = mat[len2][len1];
    Matrix::Free(mat, len2 + 1);

    return res;
}

int DamLevNonRec(const std::wstring &word1, const std::wstring &word2, bool verbose)
{
    int len1 = word1.length();
    int len2 = word2.length();

    int **mat = Matrix::Allocate(len2 + 1, len1 + 1);
    if (!mat)
        return -1;

    mat[0][0] = 0;
    for (int i = 0; i <= len2; ++i)
    {
        for (int j = 0; j <= len1; ++j)
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
                int cost = (word1[j - 1] == word2[i - 1]) ? 0 : 1;

                mat[i][j] = min(
                    mat[i - 1][j] + 1,
                    mat[i][j - 1] + 1,
                    mat[i - 1][j - 1] + cost);

                if (word1[j - 2] == word2[i - 1] && word1[j - 1] == word2[i - 2])
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

    int res = mat[len2][len1];
    Matrix::Free(mat, len2 + 1);

    return res;
}

int DamLevRec(const std::wstring &word1, const std::wstring &word2, int ind1, int ind2)
{
    if (ind1 == 0)
        return ind2;
    if (ind2 == 0)
        return ind1;

    int cost = (word1[ind1 - 1] == word2[ind2 - 1]) ? 0 : 1;

    int res = min(
        DamLevRec(word1, word2, ind1, ind2 - 1) + 1,
        DamLevRec(word1, word2, ind1 - 1, ind2) + 1,
        DamLevRec(word1, word2, ind1 - 1, ind2 - 1) + cost);

    if (ind1 > 1 && ind2 > 1 && word1[ind1 - 1] == word2[ind2 - 2] && word1[ind1 - 2] == word2[ind2 - 1])
        res = std::min(res, DamLevRec(word1, word2, ind1 - 2, ind2 - 2) + 1);

    return res;
}

static int DamLevRecCacheImpl(const std::wstring &word1, const std::wstring &word2, int ind1, int ind2, int **memo)
{
    if (ind1 == 0)
        return ind2;

    if (ind2 == 0)
        return ind1;

    if (memo[ind2][ind1] != -1)
        return memo[ind2][ind1];
    
    int cost = (word1[ind1 - 1] == word2[ind2 - 1]) ? 0 : 1;

    int res = min(
        DamLevRecCacheImpl(word1, word2, ind1, ind2 - 1, memo) + 1,
        DamLevRecCacheImpl(word1, word2, ind1 - 1, ind2, memo) + 1,
        DamLevRecCacheImpl(word1, word2, ind1 - 1, ind2 - 1, memo) + cost
    );

    if (ind1 > 1 && ind2 > 1 && word1[ind1 - 1] == word2[ind2 - 2] && word1[ind1 - 2] == word2[ind2 - 1])
        res = std::min(res, DamLevRecCacheImpl(word1, word2, ind1 - 2, ind2 - 2, memo) + 1);

    memo[ind2][ind1] = res;
    return res;
}

int DamLevRecCache(const std::wstring &word1, const std::wstring &word2)
{
    int len1 = word1.length();
    int len2 = word2.length();

    int **memo = Matrix::Allocate(len2 + 1, len1 + 1, -1);
    if (!memo)
        return -1;
    
    int res = DamLevRecCacheImpl(word1, word2, len1, len2, memo);
    
    Matrix::Free(memo, len2 + 1);
    return res;
}
