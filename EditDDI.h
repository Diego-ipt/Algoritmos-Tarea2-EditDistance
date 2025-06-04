#ifndef EDIT_DDI_H
#define EDIT_DDI_H

#include <string>
#include <vector>
#include <algorithm>
#include "lcs.h"

using namespace std;

// Calcula la distancia de edición usando recursividad pura (basada en lcs_recursive).
inline int editDistanceRecursive(const string &s, const string &t) {
    int lcs = lcs_recursive_str(s, t, s.size(), t.size());
    return static_cast<int>(s.size() + t.size() - 2 * lcs);
}

// Calcula la distancia de edición usando recursividad con memoización.
inline int editDistanceMemo(const string &s, const string &t) {
    int lcs = lcs_memo_str(s, t);
    return static_cast<int>(s.size() + t.size() - 2 * lcs);
}

// Calcula la distancia de edición usando programación dinámica (tabla 2D completa).
inline int editDistanceDP(const string &s, const string &t) {
    int n = static_cast<int>(s.size()), m = static_cast<int>(t.size());
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            if (i == 0 || j == 0) dp[i][j] = 0;
            else if (s[i - 1] == t[j - 1]) dp[i][j] = 1 + dp[i - 1][j - 1];
            else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    return n + m - 2 * dp[n][m];
}

// Calcula la distancia de edición usando programación dinámica optimizada en espacio (dos vectores).
inline int editDistanceDPOptimized(const string &s, const string &t) {
    int n = static_cast<int>(s.size()), m = static_cast<int>(t.size());
    vector<int> prev(m + 1, 0), curr(m + 1, 0);
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            if (i == 0 || j == 0) curr[j] = 0;
            else if (s[i - 1] == t[j - 1]) curr[j] = 1 + prev[j - 1];
            else curr[j] = max(prev[j], curr[j - 1]);
        }
        prev = curr;
    }
    return n + m - 2 * prev[m];
}

#endif // EDIT_DDI_H
