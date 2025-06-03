#ifndef LCS_H
#define LCS_H

#include <string>
#include <vector>
#include <algorithm>

// Longitud de LCS usando recursividad pura
inline int lcs_recursive_str(const std::string &s, const std::string &t, int i, int j) {
    if (i == 0 || j == 0) return 0;
    if (s[i - 1] == t[j - 1])
        return 1 + lcs_recursive_str(s, t, i - 1, j - 1);
    else
        return std::max(lcs_recursive_str(s, t, i - 1, j), lcs_recursive_str(s, t, i, j - 1));
}

// Longitud de LCS usando recursividad con memoización
inline int lcs_memo_helper(const std::string &s, const std::string &t, int i, int j, std::vector<std::vector<int>> &memo) {
    if (i == 0 || j == 0) return 0;
    if (memo[i][j] != -1) return memo[i][j];
    if (s[i - 1] == t[j - 1])
        memo[i][j] = 1 + lcs_memo_helper(s, t, i - 1, j - 1, memo);
    else
        memo[i][j] = std::max(lcs_memo_helper(s, t, i - 1, j, memo), lcs_memo_helper(s, t, i, j - 1, memo));
    return memo[i][j];
}

inline int lcs_memo_str(const std::string &s, const std::string &t) {
    std::vector<std::vector<int>> memo(s.size() + 1, std::vector<int>(t.size() + 1, -1));
    return lcs_memo_helper(s, t, s.size(), t.size(), memo);
}

#endif // LCS_H
