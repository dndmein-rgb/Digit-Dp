# 0233. Number of Digit One

🔗 https://leetcode.com/problems/number-of-digit-one/

---

## 🧾 Problem Statement

Given an integer `n`, count the total number of digit **'1'** appearing in all non-negative integers less than or equal to `n`.

You are not counting numbers. You are counting how many times digit `1` appears in the entire range `[0, n]`.

---

## 📥 Examples

### Example 1

Input:
n = 13

Output:
6

Explanation:
Numbers: 1, 10, 11, 12, 13  
Total count of digit `1` = 6

---

### Example 2

Input:
n = 0

Output:
0

---

## 📌 Constraints

- 0 <= n <= 10^9

---

## 💡 Key Idea

Instead of checking every number, we use Digit DP.

We construct numbers digit by digit and track how many times digit `1` appears.

---

## 🧠 DP State

dp(pos, tight, started, count_of_1)

Meaning:
- pos → current digit index
- tight → still matching prefix of n
- started → avoids leading zeros
- count_of_1 → number of 1s so far

---

## ⚙️ Transition

For each digit d from 0 to limit:

- limit = digits[pos] if tight else 9

Transitions:

newTight = tight && (d == limit)  
newStarted = started || (d != 0)  
newCount = count_of_1 + (d == 1 ? 1 : 0) if started or d != 0  

---

## 🎯 Base Case

If pos == number length:

return count_of_1

We return the accumulated count because we are summing digit occurrences, not counting valid numbers.

---

## ⏱️ Complexity

Time: O(digits × 10 × states)  
Space: O(digits × states)

Efficient for n up to 10^9.

---

## 🧪 Edge Cases

- n = 0 → 0
- Single digit numbers
- Repeated 1s (111, 1011)
- Large numbers up to 1e9

---

## 🧠 Insight

Digit DP is used here not to count numbers, but to aggregate contributions of a digit across all valid numbers.

Each DP path contributes partial counts.

---

## 🏁 Summary

Digit DP converts brute force enumeration into structured state transitions, enabling efficient counting of digit-level properties over large ranges.
