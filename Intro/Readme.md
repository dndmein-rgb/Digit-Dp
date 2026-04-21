/*
============================================================
  DIGIT DP — Complete Pattern Guide
  
  Topics Covered:
  1.  Core Template
  2.  Digit Sum Constraints
  3.  Divisibility / Modular Arithmetic
  4.  No Consecutive Same Digits
  5.  Digit Bitmask
  6.  Non-Decreasing Digits
  7.  Sum of All Valid Numbers
  8.  Palindrome Numbers
  9.  Count of a Specific Digit
  10. At Most N Given Digit Set
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

// ============================================================
// UTILITY
// ============================================================

vi getDigits(ll N) {
    vi d;
    string s = to_string(N);
    for (char c : s) d.push_back(c - '0');
    return d;
}

// ============================================================
// PATTERN 1 — CORE TEMPLATE (Digit Sum == K)
//
// Problem : Count numbers in [L, R] whose digit sum == K
// State   : (pos, tight, started, sum)
// ============================================================

namespace DigitSumEqual {

    vi digits;
    int K;
    ll memo[20][2][2][200]; // pos, tight, started, sum

    ll dp(int pos, bool tight, bool started, int sum) {
        if (sum > K) return 0; // prune early

        if (pos == (int)digits.size())
            return (started && sum == K) ? 1 : 0;

        ll &ret = memo[pos][tight][started][sum];
        if (ret != -1) return ret;

        int limit = tight ? digits[pos] : 9;
        ret = 0;

        for (int d = 0; d <= limit; d++) {
            bool newTight   = tight && (d == limit);
            bool newStarted = started || (d != 0);
            int  newSum     = (started || d != 0) ? sum + d : sum;
            ret += dp(pos + 1, newTight, newStarted, newSum);
        }

        return ret;
    }

    ll f(ll N) {
        if (N < 0) return 0;
        digits = getDigits(N);
        memset(memo, -1, sizeof(memo));
        return dp(0, true, false, 0);
    }

    ll solve(ll L, ll R, int k) {
        K = k;
        return f(R) - f(L - 1);
    }
}

// ============================================================
// PATTERN 2 — DIGIT SUM <= K
//
// Problem : Count numbers in [L, R] whose digit sum <= K
// State   : (pos, tight, started, sum)
// ============================================================

namespace DigitSumAtMost {

    vi digits;
    int K;
    ll memo[20][2][2][200];

    ll dp(int pos, bool tight, bool started, int sum) {
        if (sum > K) return 0;

        if (pos == (int)digits.size())
            return started ? 1 : 0;

        ll &ret = memo[pos][tight][started][sum];
        if (ret != -1) return ret;

        int limit = tight ? digits[pos] : 9;
        ret = 0;

        for (int d = 0; d <= limit; d++) {
            bool newTight   = tight && (d == limit);
            bool newStarted = started || (d != 0);
            int  newSum     = (started || d != 0) ? sum + d : sum;
            ret += dp(pos + 1, newTight, newStarted, newSum);
        }

        return ret;
    }

    ll f(ll N) {
        if (N < 0) return 0;
        digits = getDigits(N);
        memset(memo, -1, sizeof(memo));
        return dp(0, true, false, 0);
    }

    ll solve(ll L, ll R, int k) {
        K = k;
        return f(R) - f(L - 1);
    }
}

// ============================================================
// PATTERN 3 — DIVISIBILITY
//
// Problem : Count numbers in [L, R] divisible by K
// State   : (pos, tight, started, mod)
// Trick   : new_mod = (mod * 10 + d) % K
// ============================================================

namespace Divisibility {

    vi digits;
    int K;
    ll memo[20][2][2][1000]; // mod can be up to K-1; resize as needed

    ll dp(int pos, bool tight, bool started, int mod) {
        if (pos == (int)digits.size())
            return (started && mod == 0) ? 1 : 0;

        ll &ret = memo[pos][tight][started][mod];
        if (ret != -1) return ret;

        int limit = tight ? digits[pos] : 9;
        ret = 0;

        for (int d = 0; d <= limit; d++) {
            bool newTight   = tight && (d == limit);
            bool newStarted = started || (d != 0);
            int  newMod     = (started || d != 0) ? (mod * 10 + d) % K : 0;
            ret += dp(pos + 1, newTight, newStarted, newMod);
        }

        return ret;
    }

    ll f(ll N) {
        if (N < 0) return 0;
        digits = getDigits(N);
        memset(memo, -1, sizeof(memo));
        return dp(0, true, false, 0);
    }

    ll solve(ll L, ll R, int k) {
        K = k;
        return f(R) - f(L - 1);
    }
}

// ============================================================
// PATTERN 4 — NO CONSECUTIVE SAME DIGITS
//
// Problem : Count numbers in [L, R] with no two adjacent
//           digits being equal
// State   : (pos, tight, started, lastDigit)
// ============================================================

namespace NoConsecutiveSame {

    vi digits;
    ll memo[20][2][2][10]; // last digit 0-9

    ll dp(int pos, bool tight, bool started, int last) {
        if (pos == (int)digits.size())
            return started ? 1 : 0;

        ll &ret = memo[pos][tight][started][last];
        if (ret != -1) return ret;

        int limit = tight ? digits[pos] : 9;
        ret = 0;

        for (int d = 0; d <= limit; d++) {
            if (started && d == last) continue; // skip consecutive

            bool newTight   = tight && (d == limit);
            bool newStarted = started || (d != 0);
            int  newLast    = (started || d != 0) ? d : last;
            ret += dp(pos + 1, newTight, newStarted, newLast);
        }

        return ret;
    }

    ll f(ll N) {
        if (N < 0) return 0;
        digits = getDigits(N);
        memset(memo, -1, sizeof(memo));
        return dp(0, true, false, -1); // -1 = no last digit yet
    }

    ll solve(ll L, ll R) {
        return f(R) - f(L - 1);
    }
}

// ============================================================
// PATTERN 5 — DIGIT BITMASK (No Repeated Digits)
//
// Problem : Count numbers in [L, R] with all distinct digits
//           (no digit appears more than once)
// State   : (pos, tight, started, mask)
// mask    : bitmask of digits 0-9 already used
// ============================================================

namespace NoRepeatedDigits {

    vi digits;
    ll memo[20][2][2][1 << 10]; // 2^10 = 1024 masks

    ll dp(int pos, bool tight, bool started, int mask) {
        if (pos == (int)digits.size())
            return started ? 1 : 0;

        ll &ret = memo[pos][tight][started][mask];
        if (ret != -1) return ret;

        int limit = tight ? digits[pos] : 9;
        ret = 0;

        for (int d = 0; d <= limit; d++) {
            if (started && (mask >> d & 1)) continue; // digit already used

            bool newTight   = tight && (d == limit);
            bool newStarted = started || (d != 0);
            int  newMask    = (started || d != 0) ? mask | (1 << d) : mask;
            ret += dp(pos + 1, newTight, newStarted, newMask);
        }

        return ret;
    }

    ll f(ll N) {
        if (N < 0) return 0;
        digits = getDigits(N);
        memset(memo, -1, sizeof(memo));
        return dp(0, true, false, 0);
    }

    ll solve(ll L, ll R) {
        return f(R) - f(L - 1);
    }
}

// ============================================================
// PATTERN 6 — NON-DECREASING DIGITS
//
// Problem : Count numbers in [L, R] whose digits are
//           non-decreasing left to right (e.g. 1 2 2 5 9)
// State   : (pos, tight, last)
// Trick   : start inner loop from `last` instead of 0
// ============================================================

namespace NonDecreasing {

    vi digits;
    ll memo[20][2][10];

    ll dp(int pos, bool tight, int last) {
        if (pos == (int)digits.size()) return 1;

        ll &ret = memo[pos][tight][last];
        if (ret != -1) return ret;

        int limit = tight ? digits[pos] : 9;
        ret = 0;

        // Start from `last` — elegantly enforces non-decreasing
        for (int d = last; d <= limit; d++) {
            bool newTight = tight && (d == limit);
            ret += dp(pos + 1, newTight, d);
        }

        return ret;
    }

    // Note: 0-padded numbers (like 007) count as 007 here.
    // If only positive numbers are wanted, subtract the count
    // of all-zero "numbers" = 1 (the number 0 itself).
    ll f(ll N) {
        if (N < 0) return 0;
        digits = getDigits(N);
        memset(memo, -1, sizeof(memo));
        return dp(0, true, 0);
    }

    ll solve(ll L, ll R) {
        return f(R) - f(L - 1);
    }
}

// ============================================================
// PATTERN 7 — SUM OF ALL VALID NUMBERS
//
// Problem : Return the SUM (not count) of all numbers in
//           [L, R] whose digit sum == K
// State   : (pos, tight, started, sum)
// Returns : pair<count, total_sum>
// Trick   : contribution = d * 10^(remaining) * count_below
// ============================================================

namespace SumOfValid {

    vi digits;
    int K;
    // memo stores {count, sum}
    map<tuple<int,bool,bool,int>, pair<ll,ll>> memo;

    pair<ll,ll> dp(int pos, bool tight, bool started, int sum) {
        if (sum > K) return {0, 0};

        if (pos == (int)digits.size())
            return (started && sum == K) ? make_pair(1LL, 0LL) : make_pair(0LL, 0LL);

        auto key = make_tuple(pos, tight, started, sum);
        auto it = memo.find(key);
        if (it != memo.end()) return it->second;

        int limit = tight ? digits[pos] : 9;
        ll totalCount = 0, totalSum = 0;
        int remaining = (int)digits.size() - pos - 1;

        for (int d = 0; d <= limit; d++) {
            bool newTight   = tight && (d == limit);
            bool newStarted = started || (d != 0);
            int  newSum     = (started || d != 0) ? sum + d : sum;

            auto [cnt, s] = dp(pos + 1, newTight, newStarted, newSum);

            totalCount += cnt;
            // d at position `pos` contributes d * 10^remaining to each of the cnt numbers
            ll placeValue = 1;
            for (int i = 0; i < remaining; i++) placeValue *= 10;
            totalSum += s + (ll)d * placeValue * cnt;
        }

        return memo[key] = {totalCount, totalSum};
    }

    ll f(ll N) {
        if (N < 0) return 0;
        digits = getDigits(N);
        memo.clear();
        return dp(0, true, false, 0).second;
    }

    ll solve(ll L, ll R, int k) {
        K = k;
        return f(R) - f(L - 1);
    }
}

// ============================================================
// PATTERN 8 — PALINDROME NUMBERS
//
// Problem : Count palindrome numbers in [L, R]
// Approach: Fill digits symmetrically from outside in.
//           Fix first half, mirror to second half,
//           then check tight constraint.
// Note    : This uses a different construction strategy —
//           we enumerate palindromes directly rather than
//           building digit by digit.
// ============================================================

namespace Palindromes {

    // Count palindromes with exactly `len` digits, <= N if tight
    // Strategy: place digits[0..mid], mirror, compare with N
    ll countPalindromes(int len, ll N) {
        string s = to_string(N);
        if (len > (int)s.size()) {
            // All len-digit palindromes are <= N
            // First digit: 1-9, middle digits: 0-9
            ll count = 9;
            for (int i = 1; i < (len + 1) / 2; i++) count *= 10;
            return count;
        }
        if (len < (int)s.size()) {
            // No len-digit number can be <= N if len < digits of N
            // (handled by the calling loop)
            ll count = 9;
            for (int i = 1; i < (len + 1) / 2; i++) count *= 10;
            return count;
        }

        // len == digits of N: count len-digit palindromes <= N
        int half = (len + 1) / 2;
        string prefix = s.substr(0, half);
        ll count = 0;

        // Try all prefixes from 10...0 to prefix
        for (int i = 0; i < half; i++) {
            int lo = (i == 0) ? 1 : 0;
            int hi = prefix[i] - '0';
            count += (hi - lo) * (ll)pow(10, half - i - 1);
        }

        // Check if the palindrome formed by prefix itself is <= N
        string pal = prefix;
        string rev = prefix;
        reverse(rev.begin(), rev.end());
        if (len % 2 == 0) pal += rev;
        else              pal += rev.substr(1);

        if (pal <= s) count++;

        return count;
    }

    ll f(ll N) {
        if (N <= 0) return 0;
        string s = to_string(N);
        int maxLen = s.size();
        ll total = 0;

        for (int len = 1; len < maxLen; len++) {
            // All len-digit palindromes
            ll cnt = 9;
            for (int i = 1; i < (len + 1) / 2; i++) cnt *= 10;
            total += cnt;
        }

        total += countPalindromes(maxLen, N);
        return total;
    }

    ll solve(ll L, ll R) {
        return f(R) - f(L - 1);
    }
}

// ============================================================
// PATTERN 9 — COUNT OF A SPECIFIC DIGIT
//
// Problem : Count how many times digit D appears across
//           all numbers in [1, N]  (LeetCode 233 generalized)
// State   : (pos, tight, started, cnt)
// ============================================================

namespace CountSpecificDigit {

    vi digits;
    int D;
    ll memo[20][2][2][20]; // cnt can be at most 19 (for 19-digit numbers)

    ll dp(int pos, bool tight, bool started, int cnt) {
        if (pos == (int)digits.size())
            return started ? cnt : 0; // return count of D in this number

        ll &ret = memo[pos][tight][started][cnt];
        if (ret != -1) return ret;

        int limit = tight ? digits[pos] : 9;
        ret = 0;

        for (int d = 0; d <= limit; d++) {
            bool newTight   = tight && (d == limit);
            bool newStarted = started || (d != 0);
            int  newCnt     = (started || d != 0) ? cnt + (d == D ? 1 : 0) : cnt;
            ret += dp(pos + 1, newTight, newStarted, newCnt);
        }

        return ret;
    }

    // Returns total occurrences of digit D in all numbers [1, N]
    ll f(ll N) {
        if (N < 0) return 0;
        digits = getDigits(N);
        memset(memo, -1, sizeof(memo));
        return dp(0, true, false, 0);
    }

    ll solve(ll L, ll R, int digit) {
        D = digit;
        return f(R) - f(L - 1);
    }
}

// ============================================================
// PATTERN 10 — AT MOST N GIVEN DIGIT SET
//
// Problem : Given a sorted array of allowed digits and
//           integer N, count how many positive integers
//           <= N can be formed using only those digits.
//           (LeetCode 902)
// ============================================================

namespace AtMostNGivenDigitSet {

    vi digits;         // digits of N
    vi allowed;        // sorted list of allowed digits
    ll memo[20][2][2];

    ll dp(int pos, bool tight, bool started) {
        if (pos == (int)digits.size())
            return started ? 1 : 0;

        ll &ret = memo[pos][tight][started];
        if (ret != -1) return ret;

        ret = 0;
        int limit = tight ? digits[pos] : 9;

        // Option 1: place 0 as leading zero (only if not started)
        if (!started)
            ret += dp(pos + 1, false, false);

        // Option 2: place an allowed digit
        for (int d : allowed) {
            if (d > limit) break; // allowed is sorted
            bool newTight = tight && (d == limit);
            ret += dp(pos + 1, newTight, true);
        }

        return ret;
    }

    ll f(ll N) {
        if (N < 0) return 0;
        digits = getDigits(N);
        memset(memo, -1, sizeof(memo));
        return dp(0, true, false);
    }

    ll solve(ll N, vi &digitSet) {
        allowed = digitSet;
        sort(allowed.begin(), allowed.end());
        return f(N);
    }
}

// ============================================================
// MAIN — Demo of all patterns
// ============================================================

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "========================================\n";
    cout << "   DIGIT DP — Pattern Demonstrations\n";
    cout << "========================================\n\n";

    ll L = 1, R = 1000;

    // Pattern 1: Digit Sum == K
    cout << "[Pattern 1] Count numbers in [" << L << ", " << R << "] with digit sum == 10: ";
    cout << DigitSumEqual::solve(L, R, 10) << "\n";

    // Pattern 2: Digit Sum <= K
    cout << "[Pattern 2] Count numbers in [" << L << ", " << R << "] with digit sum <= 5: ";
    cout << DigitSumAtMost::solve(L, R, 5) << "\n";

    // Pattern 3: Divisibility
    cout << "[Pattern 3] Count numbers in [" << L << ", " << R << "] divisible by 7: ";
    cout << Divisibility::solve(L, R, 7) << "\n";

    // Pattern 4: No Consecutive Same Digits
    cout << "[Pattern 4] Count numbers in [" << L << ", " << R << "] with no consecutive same digits: ";
    cout << NoConsecutiveSame::solve(L, R) << "\n";

    // Pattern 5: No Repeated Digits
    cout << "[Pattern 5] Count numbers in [" << L << ", " << R << "] with all distinct digits: ";
    cout << NoRepeatedDigits::solve(L, R) << "\n";

    // Pattern 6: Non-Decreasing Digits
    cout << "[Pattern 6] Count numbers in [" << L << ", " << R << "] with non-decreasing digits: ";
    cout << NonDecreasing::solve(L, R) << "\n";

    // Pattern 7: Sum of Valid Numbers
    cout << "[Pattern 7] Sum of numbers in [" << L << ", " << R << "] with digit sum == 5: ";
    cout << SumOfValid::solve(L, R, 5) << "\n";

    // Pattern 8: Palindromes
    cout << "[Pattern 8] Count palindromes in [" << L << ", " << R << "]: ";
    cout << Palindromes::solve(L, R) << "\n";

    // Pattern 9: Count of Specific Digit
    cout << "[Pattern 9] Total occurrences of digit 1 across all numbers in [1, 100]: ";
    cout << CountSpecificDigit::solve(1, 100, 1) << "\n";

    // Pattern 10: At Most N Given Digit Set
    vi digitSet = {1, 3, 5, 7};
    cout << "[Pattern 10] Count numbers <= 100 using only digits {1,3,5,7}: ";
    cout << AtMostNGivenDigitSet::solve(100, digitSet) << "\n";

    cout << "\n========================================\n";
    cout << "   STATE SPACE QUICK REFERENCE\n";
    cout << "========================================\n";
    cout << "pos        : current digit index (0 = MSB)\n";
    cout << "tight      : true if prefix == prefix of N\n";
    cout << "started    : true if non-zero digit placed\n";
    cout << "sum        : running digit sum\n";
    cout << "mod        : running value mod K\n";
    cout << "last       : last digit placed\n";
    cout << "mask       : bitmask of digits seen (2^10)\n";
    cout << "cnt        : count of specific digit seen\n";
    cout << "\n";
    cout << "COMPLEXITY: O(10 * log(N) * |state_space|)\n";
    cout << "FORMULA   : answer(L,R) = f(R) - f(L-1)\n";

    return 0;
}
