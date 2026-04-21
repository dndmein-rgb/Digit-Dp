# 902. Numbers At Most N Given Digit Set

🔗 https://leetcode.com/problems/numbers-at-most-n-given-digit-set/

---

## 🧾 Problem Statement

Given a sorted array of digits, you can use each digit unlimited times to form numbers.

Return the number of **positive integers ≤ n** that can be formed using these digits only.

---

## 💡 Key Idea

This is a Digit DP problem with a twist:

Instead of choosing digits 0–9, we only choose from a **restricted digit set**.

We count:
- All valid numbers with length < len(n)
- Plus numbers with same length as n using tight Digit DP

---

## 🧠 DP State


dp(pos, tight)


Where:
- pos → current digit index
- tight → still matching prefix of n

---

## ⚙️ Transition

For each digit `d` in allowed set:

- If tight is true, `d` must be ≤ current digit of n
- Otherwise free choice from digit set


newTight = tight && (d == limit)


---

## 🎯 Base Case


if pos == digits.size():
return 1


Every valid construction is one number.

---

## 🔥 Important Insight

We solve this in **two parts**:

### 1. Numbers with length < len(n)

count += sum(|digits|^k) for k < len(n)


### 2. Numbers with same length as n
Handled using Digit DP.

---

## 📥 Example

### Input:

digits = ["1","3","5","7"]
n = 100


### Valid numbers:
- 1,3,5,7
- 11,13,15,17, ...
- 77, 135, etc (≤ 100 only)

---

## ⏱️ Complexity


Time: O(len(n) × |digits|)
Space: O(len(n))


Very efficient due to small digit set.

---

## 🧪 Edge Cases

- n smaller than smallest digit
- digit set missing 0 (important)
- single-digit n
- large n with small digit set

---

## 🏁 Summary

We count numbers ≤ n using only allowed digits by:

- Building numbers digit by digit
- Using tight constraint for prefix matching
- Separating length-based counting from DP

Classic restricted Digit DP pattern.
