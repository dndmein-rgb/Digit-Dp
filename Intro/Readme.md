# 🧠 Digit DP — Complete Cheat Sheet

Digit DP is used to count numbers in a range **[L, R]** that satisfy digit-based constraints.

---

## 🔥 Core Formula

answer(L, R) = f(R) - f(L - 1)

---

## 📐 Universal State Space

| State     | Meaning                          | Range          |
|----------|----------------------------------|---------------|
| pos      | Current digit index              | 0 → 18        |
| tight    | Is prefix bounded by N           | true/false    |
| started  | Non-zero digit placed?           | true/false    |
| sum      | Digit sum                        | 0 → 180       |
| mod      | Value mod K                      | 0 → K-1       |
| last     | Last digit                       | 0 → 9         |
| mask     | Used digits (bitmask)            | 0 → 1023      |
| cnt      | Count of digit                   | 0 → 19        |

---

## 🏗️ Universal Template

```cpp
vector<int> digits;

vector<int> getDigits(long long N) {
    vector<int> d;
    string s = to_string(N);
    for (char c : s) d.push_back(c - '0');
    return d;
}

long long memo[20][2][2][200];

long long dp(int pos, bool tight, bool started, int sum) {
    if (pos == digits.size())
        return /* condition */;

    long long &ret = memo[pos][tight][started][sum];
    if (ret != -1) return ret;

    int limit = tight ? digits[pos] : 9;
    ret = 0;

    for (int d = 0; d <= limit; d++) {
        bool newTight   = tight && (d == limit);
        bool newStarted = started || (d != 0);

        ret += dp(pos + 1, newTight, newStarted, /* update */);
    }

    return ret;
}

long long f(long long N) {
    if (N < 0) return 0;
    digits = getDigits(N);
    memset(memo, -1, sizeof(memo));
    return dp(0, true, false, 0);
}

long long solve(long long L, long long R) {
    return f(R) - f(L - 1);
}

---


✅ Pattern 1 — Digit Sum == K
long long dp(int pos, bool tight, bool started, int sum) {
    if (sum > K) return 0;

    if (pos == digits.size())
        return (started && sum == K) ? 1 : 0;

    long long &ret = memo[pos][tight][started][sum];
    if (ret != -1) return ret;

    int limit = tight ? digits[pos] : 9;
    ret = 0;

    for (int d = 0; d <= limit; d++) {
        bool newTight   = tight && (d == limit);
        bool newStarted = started || (d != 0);
        int newSum      = (started || d != 0) ? sum + d : sum;

        ret += dp(pos + 1, newTight, newStarted, newSum);
    }
    return ret;
}

---

✅ Pattern 2 — Digit Sum ≤ K
if (pos == digits.size())
    return started ? 1 : 0;

---

✅ Pattern 3 — Divisible by K
long long dp(int pos, bool tight, bool started, int mod) {
    if (pos == digits.size())
        return (started && mod == 0) ? 1 : 0;

    long long &ret = memo[pos][tight][started][mod];
    if (ret != -1) return ret;

    int limit = tight ? digits[pos] : 9;
    ret = 0;

    for (int d = 0; d <= limit; d++) {
        bool newTight   = tight && (d == limit);
        bool newStarted = started || (d != 0);
        int newMod      = (started || d != 0) ? (mod * 10 + d) % K : 0;

        ret += dp(pos + 1, newTight, newStarted, newMod);
    }
    return ret;
}

---

✅ Pattern 4 — No Consecutive Same Digits
long long dp(int pos, bool tight, bool started, int last) {
    if (pos == digits.size())
        return started ? 1 : 0;

    long long &ret = memo[pos][tight][started][last + 1];
    if (ret != -1) return ret;

    int limit = tight ? digits[pos] : 9;
    ret = 0;

    for (int d = 0; d <= limit; d++) {
        if (started && d == last) continue;

        bool newTight   = tight && (d == limit);
        bool newStarted = started || (d != 0);
        int newLast     = (started || d != 0) ? d : last;

        ret += dp(pos + 1, newTight, newStarted, newLast);
    }
    return ret;
}

---

✅ Pattern 5 — No Repeated Digits (Bitmask)
long long dp(int pos, bool tight, bool started, int mask) {
    if (pos == digits.size())
        return started ? 1 : 0;

    long long &ret = memo[pos][tight][started][mask];
    if (ret != -1) return ret;

    int limit = tight ? digits[pos] : 9;
    ret = 0;

    for (int d = 0; d <= limit; d++) {
        if (started && (mask >> d & 1)) continue;

        bool newTight   = tight && (d == limit);
        bool newStarted = started || (d != 0);
        int newMask     = (started || d != 0) ? mask | (1 << d) : mask;

        ret += dp(pos + 1, newTight, newStarted, newMask);
    }
    return ret;
}

---

✅ Pattern 6 — Non-Decreasing Digits
long long dp(int pos, bool tight, int last) {
    if (pos == digits.size()) return 1;

    long long &ret = memo[pos][tight][last];
    if (ret != -1) return ret;

    int limit = tight ? digits[pos] : 9;
    ret = 0;

    for (int d = last; d <= limit; d++) {
        bool newTight = tight && (d == limit);
        ret += dp(pos + 1, newTight, d);
    }
    return ret;
}

---

✅ Pattern 7 — Sum of All Valid Numbers
pair<long long,long long> dp(int pos, bool tight, bool started, int sum) {
    if (sum > K) return {0, 0};

    if (pos == digits.size())
        return (started && sum == K) ? make_pair(1LL, 0LL)
                                    : make_pair(0LL, 0LL);

    int limit = tight ? digits[pos] : 9;
    long long totalCount = 0, totalSum = 0;
    int remaining = digits.size() - pos - 1;

    for (int d = 0; d <= limit; d++) {
        auto [cnt, s] = dp(pos + 1, tight && (d == limit),
                           started || (d != 0),
                           (started || d != 0) ? sum + d : sum);

        totalCount += cnt;

        long long placeValue = pow(10, remaining);
        totalSum += s + (long long)d * placeValue * cnt;
    }
    return {totalCount, totalSum};
}

---

📊 Complexity Summary
Pattern	State Size	Complexity
Digit Sum	20×2×2×181	O(18×181×10)
Divisible	20×2×2×K	O(18×K×10)
Consecutive	20×2×2×10	O(18×100)
Bitmask	20×2×2×1024	O(18×1024×10)
Non-Decreasing	20×2×10	O(18×100)

---

🎯 Decision Tree
Digit SUM?
 ├── == K → Pattern 1
 └── <= K → Pattern 2

Divisible?
 └── mod K → Pattern 3

Adjacent digits?
 └── No same → Pattern 4

Unique digits?
 └── Bitmask → Pattern 5

Ordering?
 └── Non-decreasing → Pattern 6

Need total sum?
 └── Pattern 7
