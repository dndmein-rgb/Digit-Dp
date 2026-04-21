# 1012. Numbers With Repeated Digits

🔗 https://leetcode.com/problems/numbers-with-repeated-digits/

---

## 🧾 Problem Statement

Given an integer `n`, return the number of positive integers in the range **[1, n]** that have at least one repeated digit.

In simple terms:
- Count numbers ≤ n
- That contain at least one digit appearing more than once

---

## 💡 Key Idea

Instead of directly counting numbers with repeated digits, we flip the problem:

We compute:

- Total numbers from 1 to n
- Minus numbers with all unique digits


answer = total - unique_digits


---

## 🧠 DP State


dp(pos, tight, started, mask)


Where:
- pos → current digit index
- tight → prefix matches n or not
- started → avoids leading zeros
- mask → used digits bitmask

---

## ⚙️ Transition

For digit `d` from 0 → limit:

- Skip if digit already used (when started)
- Update mask only after number starts


newTight = tight && (d == limit)
newStarted = started || (d != 0)
newMask = (started || d != 0) ? (mask | (1 << d)) : mask


Skip rule:

if started && (mask & (1 << d)) → skip


---

## 🎯 Base Case


if pos == digits.size():
return started ? 1 : 0


We count only numbers with all unique digits.

---

## 🧮 Final Answer


answer = f(n) - g(n)


Where:
- f(n) = total numbers ≤ n
- g(n) = numbers with all unique digits

---

## 📥 Example

Input:

n = 20


Repeated-digit numbers:

11


Output:

1


---

## ⏱️ Complexity


Time: O(digits × 2 × 1024 × 10)
Space: O(digits × 1024)


Digits are small, so this is efficient.

---

## 🧪 Edge Cases

- n < 10 → 0
- n = 1000 (many repeats)
- all digits identical numbers (111, 222)
- leading zero handling critical

---

## 🏁 Summary

We avoid brute force by:
- Counting all numbers ≤ n
- Subtracting numbers with unique digits using bitmask Digit DP
