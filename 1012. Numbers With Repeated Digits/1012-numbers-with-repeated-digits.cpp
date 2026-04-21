class Solution {
public:
    // dp[index][tight_constraint][has_repetition][mask][leading_zeros]
    int dp[11][2][2][1024][2];

    int f(string &s, int idx, bool tight, bool repetition, bool lz, int mask) {
        // Base case: if we've processed all digits, return 1 if we found a repetition
        if (idx == s.size()) {
            return repetition;
        }

        // Memoization check
        if (dp[idx][tight][repetition][mask][lz] != -1) {
            return dp[idx][tight][repetition][mask][lz];
        }

        int lb = 0;
        int ub = tight ? s[idx] - '0' : 9;
        int res = 0;

        for (int dig = lb; dig <= ub; dig++) {
            if (lz && dig == 0) {
                // Case: Still handling leading zeros
                res += f(s, idx + 1, (tight && dig == ub), 0, 1, 0);
            } else {
                // Case: Placing a significant digit
                bool isDigitUsed = (mask >> dig) & 1;
                res += f(s, idx + 1, 
                         (tight && dig == ub), 
                         (repetition || isDigitUsed), 
                         0, 
                         (mask | (1 << dig)));
            }
        }

        return dp[idx][tight][repetition][mask][lz] = res;
    }

    int numDupDigitsAtMostN(int n) {
        string s = to_string(n);
        // Initialize DP table with -1
        memset(dp, -1, sizeof(dp));

        // Start recursion: index 0, tight constraint true, no repetition, leading zeros true, empty mask
        return f(s, 0, 1, 0, 1, 0);
    }
};
