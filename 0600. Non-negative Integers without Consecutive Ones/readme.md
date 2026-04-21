# 600. Non-negative Integers without Consecutive Ones

🔗 https://leetcode.com/problems/non-negative-integers-without-consecutive-ones/

---

## 🧾 Problem Statement

Given a positive integer `n`, return the number of integers in the range **[0, n]** whose binary representations do **not contain consecutive ones**.

In simple terms:
- Convert numbers to binary
- Count how many have **no substring "11"**

---

## 💡 Key Idea

This is Digit DP, but in **binary instead of decimal**.

We build the number bit by bit (MSB → LSB) and ensure:


No two consecutive 1s appear


---

## 🧠 DP State


dp(pos, tight, prevOne)


Where:
- pos → current bit index
- tight → still matching prefix of n
- prevOne → whether previous bit was 1

---

## ⚙️ Transition

For each bit `b ∈ {0, 1}`:

Rules:
- If prevOne == 1 and b == 1 → invalid (skip)
- Respect tight constraint


newTight = tight && (b == limit)
newPrevOne = b


---

## 🎯 Base Case


if pos == number of bits:
return 1


Every valid binary number counts as 1.

---

## 📥 Example

### Input:

n = 5


Binary range:

0 → 000
1 → 001
2 → 010
3 → 011 ❌
4 → 100
5 → 101


Valid count:

5


---

## ⏱️ Complexity


Time: O(bits × 2 × 2)
Space: O(bits × 2 × 2)


Very small because bits ≤ 31.

---

## 🧪 Edge Cases

- n = 0 → 1
- n = 1 → 2
- n = power of 2
- all ones like 7 (111)

---

## 🏁 Summary

We use binary Digit DP to ensure no consecutive ones while counting all valid numbers ≤ n.

Key constraint:

prevOne == 1 && currentBit == 1 → invalid
