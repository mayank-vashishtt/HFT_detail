# Binary Search on Answer - Complete Notes

## Core Concept

**Binary Search on Answer** is a technique where we binary search on the possible answer range rather than searching in an array. We need:

1. A **monotonic function** - if answer X works, all values > X also work (or vice versa)
2. A **search space** with defined boundaries (low, high)
3. A **check function** to validate if a value is valid

---

## Problem 1: Minimum Days to Make Bouquets

### Problem Statement
Given an array `bloomDay` where `bloomDay[i]` is the day when the i-th flower blooms, make `m` bouquets each requiring `k` adjacent flowers. Find minimum days needed.

### Intuition
- If we can make bouquets in `d` days, we can also make them in `d+1, d+2, ...` days
- This creates a pattern: `N N N Y Y Y Y` (No, No, Yes, Yes...)
- We want the **first Y** (minimum days)

### Approach
1. **Search Space**: `[min(bloomDay), max(bloomDay)]`
2. **Check Function**: For a given day, count how many bouquets we can make
3. **Binary Search**: Find the minimum day where we can make ≥ m bouquets

### Code
```cpp
class Solution {
public:
    // Check if we can make m bouquets in 'day' days
    bool canMakeBouquets(vector<int>& bloomDay, int m, int k, int day) {
        int bouquets = 0;    // Count of complete bouquets
        int flowers = 0;      // Count of consecutive bloomed flowers
        
        for (int bloom : bloomDay) {
            if (bloom <= day) {
                flowers++;
                if (flowers == k) {
                    bouquets++;   // Made one bouquet
                    flowers = 0;  // Reset for next bouquet
                }
            } else {
                flowers = 0;      // Break in consecutive flowers
            }
        }
        
        return bouquets >= m;
    }
    
    int minDays(vector<int>& bloomDay, int m, int k) {
        int n = bloomDay.size();
        long long need = 1LL * m * k;
        
        // Impossible case
        if (need > n) return -1;
        
        // Define search space
        int low = *min_element(bloomDay.begin(), bloomDay.end());
        int high = *max_element(bloomDay.begin(), bloomDay.end());
        int ans = -1;
        
        // Binary search
        while (low <= high) {
            int mid = low + (high - low) / 2;
            
            if (canMakeBouquets(bloomDay, m, k, mid)) {
                ans = mid;
                high = mid - 1;  // Try to find smaller answer
            } else {
                low = mid + 1;   // Need more days
            }
        }
        
        return ans;
    }
};
```

### Complexity
- **Time**: O(n log(max - min)) where n is array size
- **Space**: O(1)

---

## Problem 2: Koko Eating Bananas

### Problem Statement
Koko wants to eat all banana piles in `h` hours. Each hour she can eat at most `speed` bananas from one pile. Find minimum eating speed.

### Intuition
- If speed `s` works, all speeds > s also work
- Pattern: `N N N Y Y Y Y`
- We want the minimum speed (first Y)

### Approach
1. **Search Space**: `[1, max(piles)]`
2. **Check Function**: Calculate total hours needed for given speed
3. **Binary Search**: Find minimum speed where total hours ≤ h

### Code
```cpp
class Solution {
public:
    // Calculate total hours needed for given speed
    long long totalHours(const vector<int>& piles, long long speed, long long limitH) {
        long long hrs = 0;
        for (int chocolates : piles) {
            hrs += (chocolates + speed - 1) / speed;  // Ceiling division
            if (hrs > limitH) return hrs;  // Early exit optimization
        }
        return hrs;
    }
    
    int minEatingSpeed(vector<int>& piles, int h) {
        int max_pile = *max_element(piles.begin(), piles.end());
        long long lo = 1, hi = max_pile;
        int ans = max_pile;
        
        while (lo <= hi) {
            long long mid = lo + (hi - lo) / 2;
            long long need = totalHours(piles, mid, (long long)h);
            
            if (need <= (long long)h) {
                ans = (int)mid;
                hi = mid - 1;  // Try smaller speed
            } else {
                lo = mid + 1;  // Need faster speed
            }
        }
        
        return ans;
    }
};
```

### Complexity
- **Time**: O(n log(max_pile))
- **Space**: O(1)

---

## Problem 3: Square Root (Floor Value)

### Problem Statement
Find floor of square root of x without using built-in sqrt function.

### Intuition
- If `mid² ≤ x`, then mid could be answer
- All values from 1 to √x satisfy: `their square ≤ x`
- Pattern: `Y Y Y Y N N N`
- We want the **last Y** (largest value whose square ≤ x)

### Approach
1. **Search Space**: `[1, x/2]`
2. **Check Function**: Check if mid² ≤ x
3. **Binary Search**: Find largest mid where mid² ≤ x

### Code
```cpp
class Solution {
public:
    int mySqrt(int x) {
        if (x < 2) return x;
        
        int left = 1, right = x / 2, ans = 0;
        
        while (left <= right) {
            long long mid = left + (right - left) / 2;
            
            if (mid * mid <= x) {
                ans = mid;        // Store potential answer
                left = mid + 1;   // Try to find larger answer
            } else {
                right = mid - 1;  // mid is too large
            }
        }
        
        return ans;
    }
};
```

### Complexity
- **Time**: O(log x)
- **Space**: O(1)

---

## Problem 4: N-th Root of M

### Problem Statement
Find the n-th root of m. Return -1 if it doesn't exist as an integer.

### Intuition
- We need to find x such that x^n = m
- Search space: [1, m]
- Check if mid^n equals m

### Approach
1. **Search Space**: `[1, m]`
2. **Check Function**: Calculate mid^n and compare with m
3. **Binary Search**: Find exact value or return -1

### Code
```cpp
class Solution {
public:
    int nthRoot(int n, int m) {
        int low = 1, high = m;
        
        while (low <= high) {
            int mid = low + (high - low) / 2;
            
            // Calculate mid^n
            long long ans = 1;
            for (int i = 0; i < n; i++) {
                ans *= mid;
                if (ans > m) break;  // Overflow prevention
            }
            
            if (ans == m) return mid;      // Found exact root
            else if (ans < m) low = mid + 1;   // Need larger value
            else high = mid - 1;           // Need smaller value
        }
        
        return -1;  // No integer root exists
    }
};
```

### Complexity
- **Time**: O(n log m)
- **Space**: O(1)

---

## Problem 5: Smallest Divisor Given Threshold

### Problem Statement
Find the smallest divisor such that sum of `ceil(arr[i]/divisor)` ≤ threshold.

### Intuition
- Larger divisor → smaller sum
- If divisor `d` works, all divisors > d also work
- Pattern: `N N N Y Y Y Y`
- We want the **first Y** (smallest divisor)

### Approach
1. **Search Space**: `[1, max(arr)]`
2. **Check Function**: Calculate sum of divisions
3. **Binary Search**: Find minimum divisor where sum ≤ threshold

### Code
```cpp
class Solution {
public:
    // Calculate sum of ceiling divisions
    int sumByD(vector<int>& arr, int div) {
        int sum = 0;
        for (int num : arr) {
            sum += (num + div - 1) / div;  // Ceiling division
        }
        return sum;
    }
    
    int smallestDivisor(vector<int>& arr, int limit) {
        if (arr.size() > limit) return -1;
        
        int low = 1;
        int high = *max_element(arr.begin(), arr.end());
        
        while (low <= high) {
            int mid = low + (high - low) / 2;
            
            if (sumByD(arr, mid) <= limit) {
                high = mid - 1;  // Try smaller divisor
            } else {
                low = mid + 1;   // Need larger divisor
            }
        }
        
        return low;
    }
};
```

### Complexity
- **Time**: O(n log(max_element))
- **Space**: O(1)

---

## Common Patterns Summary

### When to Use Binary Search on Answer
1. Problem asks for "minimum" or "maximum" value
2. You can write a function to check if a value works
3. If value X works, all values on one side also work (monotonic)

### Template
```cpp
int binarySearchOnAnswer(/* parameters */) {
    int low = /* minimum possible answer */;
    int high = /* maximum possible answer */;
    int ans = /* default answer */;
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        if (checkFunction(mid)) {
            ans = mid;
            // For minimum: high = mid - 1
            // For maximum: low = mid + 1
        } else {
            // Opposite direction
        }
    }
    
    return ans;
}
```

### Key Points
1. **Avoid Overflow**: Use `long long` for calculations
2. **Ceiling Division**: `(a + b - 1) / b` or `ceil((double)a / b)`
3. **Early Exit**: In check functions, return early if threshold exceeded
4. **Edge Cases**: Handle impossible cases before binary search

---

## Practice Tips
1. Identify if the problem has a **monotonic property**
2. Define **search space boundaries** clearly
3. Write **check function** first, then binary search
4. Test with **edge cases**: minimum, maximum, impossible scenarios
5. Watch for **integer overflow** in calculations