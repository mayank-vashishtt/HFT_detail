# Binary Search - Complete Guide (Basic to Advanced)

## Table of Contents
1. [Introduction](#introduction)
2. [Basic Binary Search](#basic-binary-search)
3. [Lower Bound](#lower-bound)
4. [Upper Bound](#upper-bound)
5. [Search Insert Position](#search-insert-position)
6. [Floor and Ceil](#floor-and-ceil)
7. [First and Last Occurrence](#first-and-last-occurrence)
8. [Count Occurrences](#count-occurrences)
9. [Search in Rotated Sorted Array I](#search-in-rotated-sorted-array-i)
10. [Search in Rotated Sorted Array II](#search-in-rotated-sorted-array-ii)
11. [Find Minimum in Rotated Sorted Array](#find-minimum-in-rotated-sorted-array)
12. [Count Rotations](#count-rotations)
13. [Single Element in Sorted Array](#single-element-in-sorted-array)
14. [Find Peak Element](#find-peak-element)

---

## Introduction

**Binary Search** is a divide-and-conquer algorithm that efficiently finds a target value in a **sorted array** by repeatedly dividing the search space in half.

### Key Concepts
- **Time Complexity**: O(log n)
- **Space Complexity**: O(1) iterative, O(log n) recursive
- **Prerequisite**: Array must be sorted

### Basic Intuition
Instead of checking every element (linear search), we:
1. Check the middle element
2. If target is smaller, search left half
3. If target is larger, search right half
4. Repeat until found or search space is empty

---

## 1. Basic Binary Search

### Problem
Find if element `X` exists in a sorted array.

### Intuition
Start with the entire array. Compare middle element with target. Eliminate half the array based on comparison.

### Code

```cpp
// Iterative Approach (Preferred)
int binarySearch(vector<int>& arr, int target) {
    int low = 0, high = arr.size() - 1;
    
    while (low <= high) {
        int mid = low + (high - low) / 2; // Prevents overflow
        
        if (arr[mid] == target) {
            return mid; // Found
        }
        else if (arr[mid] < target) {
            low = mid + 1; // Search right half
        }
        else {
            high = mid - 1; // Search left half
        }
    }
    
    return -1; // Not found
}

// Recursive Approach
int binarySearchRecursive(vector<int>& arr, int low, int high, int target) {
    if (low > high) return -1;
    
    int mid = low + (high - low) / 2;
    
    if (arr[mid] == target) return mid;
    else if (arr[mid] < target) return binarySearchRecursive(arr, mid + 1, high, target);
    else return binarySearchRecursive(arr, low, mid - 1, target);
}
```

### Example
```
Array: [1, 3, 5, 7, 9, 11, 13]
Target: 7

Step 1: low=0, high=6, mid=3, arr[3]=7 ✓ Found!
```

---

## 2. Lower Bound

### Problem
Find the first position where `arr[i] >= X` (smallest index where element is >= target).

### Intuition
Similar to binary search, but when we find an element >= target, we store it and continue searching left for a potentially smaller index.

### Code

```cpp
int lowerBound(vector<int>& arr, int target) {
    int low = 0, high = arr.size() - 1;
    int ans = arr.size(); // If not found, return size
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        if (arr[mid] >= target) {
            ans = mid;           // Possible answer
            high = mid - 1;      // Search left for smaller index
        }
        else {
            low = mid + 1;       // Search right
        }
    }
    
    return ans;
}

// STL Alternative
int lb = lower_bound(arr.begin(), arr.end(), target) - arr.begin();
```

### Example
```
Array: [1, 2, 4, 4, 6, 8]
Target: 4

Lower Bound = 2 (first occurrence of 4)
```

---

## 3. Upper Bound

### Problem
Find the first position where `arr[i] > X` (smallest index where element is strictly greater than target).

### Intuition
Find the first element that is strictly greater than the target.

### Code

```cpp
int upperBound(vector<int>& arr, int target) {
    int low = 0, high = arr.size() - 1;
    int ans = arr.size();
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        if (arr[mid] > target) {
            ans = mid;
            high = mid - 1;      // Search left
        }
        else {
            low = mid + 1;       // Search right
        }
    }
    
    return ans;
}

// STL Alternative
int ub = upper_bound(arr.begin(), arr.end(), target) - arr.begin();
```

### Example
```
Array: [1, 2, 4, 4, 6, 8]
Target: 4

Upper Bound = 4 (index of 6)
```

---

## 4. Search Insert Position

### Problem
Find the index where target should be inserted to maintain sorted order.

### Intuition
This is exactly the **lower bound** problem! The position where we should insert target is where the first element >= target exists.

### Code

```cpp
int searchInsert(vector<int>& arr, int target) {
    int low = 0, high = arr.size() - 1;
    int ans = arr.size();
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        if (arr[mid] >= target) {
            ans = mid;
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }
    
    return ans;
}
```

### Example
```
Array: [1, 3, 5, 6]
Target: 2 → Insert at index 1
Target: 7 → Insert at index 4
```

---

## 5. Floor and Ceil

### Problem
- **Floor**: Largest element <= target
- **Ceil**: Smallest element >= target

### Intuition
- **Floor**: Keep updating answer when arr[mid] <= target
- **Ceil**: Same as lower bound

### Code

```cpp
// Floor: Largest element <= target
int findFloor(vector<int>& arr, int target) {
    int low = 0, high = arr.size() - 1;
    int ans = -1;
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        if (arr[mid] <= target) {
            ans = mid;           // Possible floor
            low = mid + 1;       // Search right for larger floor
        }
        else {
            high = mid - 1;
        }
    }
    
    return ans;
}

// Ceil: Smallest element >= target (Same as Lower Bound)
int findCeil(vector<int>& arr, int target) {
    int low = 0, high = arr.size() - 1;
    int ans = -1;
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        if (arr[mid] >= target) {
            ans = mid;
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }
    
    return ans;
}

// Combined function
pair<int, int> getFloorAndCeil(vector<int>& arr, int target) {
    return {findFloor(arr, target), findCeil(arr, target)};
}
```

### Example
```
Array: [1, 2, 4, 6, 8, 10]
Target: 5

Floor = 4 (largest <= 5)
Ceil = 6 (smallest >= 5)
```

---

## 6. First and Last Occurrence

### Problem
Find first and last position of target in sorted array with duplicates.

### Intuition
- **First occurrence**: Lower bound
- **Last occurrence**: Upper bound - 1

### Code

```cpp
// First Occurrence
int firstOccurrence(vector<int>& arr, int target) {
    int low = 0, high = arr.size() - 1;
    int first = -1;
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        if (arr[mid] == target) {
            first = mid;
            high = mid - 1;      // Continue searching left
        }
        else if (arr[mid] < target) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    
    return first;
}

// Last Occurrence
int lastOccurrence(vector<int>& arr, int target) {
    int low = 0, high = arr.size() - 1;
    int last = -1;
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        if (arr[mid] == target) {
            last = mid;
            low = mid + 1;       // Continue searching right
        }
        else if (arr[mid] < target) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    
    return last;
}

// Combined
pair<int, int> firstAndLast(vector<int>& arr, int target) {
    int first = firstOccurrence(arr, target);
    if (first == -1) return {-1, -1};
    int last = lastOccurrence(arr, target);
    return {first, last};
}
```

### Example
```
Array: [1, 2, 2, 2, 3, 4]
Target: 2

First = 1, Last = 3
```

---

## 7. Count Occurrences

### Problem
Count how many times target appears in sorted array.

### Intuition
Count = Last Occurrence - First Occurrence + 1

### Code

```cpp
int countOccurrences(vector<int>& arr, int target) {
    int first = firstOccurrence(arr, target);
    if (first == -1) return 0;
    
    int last = lastOccurrence(arr, target);
    return last - first + 1;
}

// Alternative: Using bounds
int countOccurrencesAlt(vector<int>& arr, int target) {
    int lb = lower_bound(arr.begin(), arr.end(), target) - arr.begin();
    int ub = upper_bound(arr.begin(), arr.end(), target) - arr.begin();
    return ub - lb;
}
```

### Example
```
Array: [1, 2, 2, 2, 3, 4]
Target: 2

Count = 3
```

---

## 8. Search in Rotated Sorted Array I

### Problem
Array is rotated at some pivot. Find target (all elements unique).

### Intuition
At least one half is always sorted. Identify the sorted half and check if target lies in that range.

### Code

```cpp
int searchRotated(vector<int>& arr, int target) {
    int low = 0, high = arr.size() - 1;
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        if (arr[mid] == target) return mid;
        
        // Check which half is sorted
        if (arr[low] <= arr[mid]) {
            // Left half is sorted
            if (arr[low] <= target && target < arr[mid]) {
                high = mid - 1;  // Target in left half
            } else {
                low = mid + 1;   // Target in right half
            }
        }
        else {
            // Right half is sorted
            if (arr[mid] < target && target <= arr[high]) {
                low = mid + 1;   // Target in right half
            } else {
                high = mid - 1;  // Target in left half
            }
        }
    }
    
    return -1;
}
```

### Example
```
Array: [4, 5, 6, 7, 0, 1, 2]
Target: 0

Step 1: mid=3, arr[3]=7, left sorted, target not in [4,7], go right
Step 2: mid=5, arr[5]=1, right sorted, target in [0,1], go left
Step 3: mid=4, arr[4]=0 ✓
```

---

## 9. Search in Rotated Sorted Array II

### Problem
Same as above but with **duplicates** allowed.

### Intuition
When arr[low] == arr[mid] == arr[high], we can't determine which half is sorted. Shrink search space by moving both pointers.

### Code

```cpp
bool searchRotatedWithDuplicates(vector<int>& arr, int target) {
    int low = 0, high = arr.size() - 1;
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        if (arr[mid] == target) return true;
        
        // Handle duplicates
        if (arr[low] == arr[mid] && arr[mid] == arr[high]) {
            low++;
            high--;
            continue;
        }
        
        // Check which half is sorted
        if (arr[low] <= arr[mid]) {
            if (arr[low] <= target && target < arr[mid]) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        else {
            if (arr[mid] < target && target <= arr[high]) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
    }
    
    return false;
}
```

### Example
```
Array: [2, 5, 6, 0, 0, 1, 2]
Target: 0

Worst case: O(n) when all elements are same
```

---

## 10. Find Minimum in Rotated Sorted Array

### Problem
Find the minimum element in a rotated sorted array (no duplicates).

### Intuition
The minimum element is at the rotation point. If right half is unsorted, minimum is there.

### Code

```cpp
int findMin(vector<int>& arr) {
    int low = 0, high = arr.size() - 1;
    int ans = INT_MAX;
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        // Optimization: If entire remaining array is sorted
        if (arr[low] <= arr[high]) {
            ans = min(ans, arr[low]);
            break;
        }
        
        // Check which half is sorted
        if (arr[low] <= arr[mid]) {
            // Left half sorted, min is arr[low]
            ans = min(ans, arr[low]);
            low = mid + 1;  // Search in unsorted right half
        }
        else {
            // Right half sorted, min is arr[mid]
            ans = min(ans, arr[mid]);
            high = mid - 1; // Search in unsorted left half
        }
    }
    
    return ans;
}
```

### Example
```
Array: [4, 5, 6, 7, 0, 1, 2]

Minimum = 0 (rotation point)
```

---

## 11. Count Rotations

### Problem
Find how many times the array has been rotated.

### Intuition
Number of rotations = Index of minimum element.

### Code

```cpp
int countRotations(vector<int>& arr) {
    int low = 0, high = arr.size() - 1;
    int ans = INT_MAX;
    int index = -1;
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        // Optimization: If entire array is sorted
        if (arr[low] <= arr[high]) {
            if (arr[low] < ans) {
                ans = arr[low];
                index = low;
            }
            break;
        }
        
        if (arr[low] <= arr[mid]) {
            if (arr[low] < ans) {
                ans = arr[low];
                index = low;
            }
            low = mid + 1;
        }
        else {
            if (arr[mid] < ans) {
                ans = arr[mid];
                index = mid;
            }
            high = mid - 1;
        }
    }
    
    return index;
}
```

### Example
```
Array: [4, 5, 6, 7, 0, 1, 2]

Rotations = 4 (index of 0)
```

---

## 12. Single Element in Sorted Array

### Problem
Every element appears twice except one. Find the single element.

### Intuition
Before the single element:
- First instance at even index, second at odd index
After the single element:
- First instance at odd index, second at even index

### Code

```cpp
int singleNonDuplicate(vector<int>& arr) {
    int n = arr.size();
    
    // Edge cases
    if (n == 1) return arr[0];
    if (arr[0] != arr[1]) return arr[0];
    if (arr[n-1] != arr[n-2]) return arr[n-1];
    
    int low = 1, high = n - 2;
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        // Check if mid is the single element
        if (arr[mid] != arr[mid-1] && arr[mid] != arr[mid+1]) {
            return arr[mid];
        }
        
        // Check which half to search
        if ((mid % 2 == 0 && arr[mid] == arr[mid+1]) ||
            (mid % 2 == 1 && arr[mid] == arr[mid-1])) {
            // We are in the left half
            low = mid + 1;
        }
        else {
            // We are in the right half
            high = mid - 1;
        }
    }
    
    return -1;
}
```

### Example
```
Array: [1, 1, 2, 2, 3, 4, 4, 5, 5]

Single Element = 3
```

---

## 13. Find Peak Element

### Problem
Find an element that is greater than its neighbors.

### Intuition
Always move toward the higher neighbor. If arr[mid] < arr[mid+1], peak must be on right.

### Code

```cpp
int findPeakElement(vector<int>& arr) {
    int n = arr.size();
    
    // Edge cases
    if (n == 1) return 0;
    if (arr[0] > arr[1]) return 0;
    if (arr[n-1] > arr[n-2]) return n-1;
    
    int low = 1, high = n - 2;
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        // Check if mid is peak
        if (arr[mid] > arr[mid-1] && arr[mid] > arr[mid+1]) {
            return mid;
        }
        
        // Move toward higher neighbor
        if (arr[mid] < arr[mid+1]) {
            low = mid + 1;  // Peak is on right
        }
        else {
            high = mid - 1; // Peak is on left
        }
    }
    
    return -1;
}
```

### Example
```
Array: [1, 2, 3, 1]

Peak = index 2 (element 3)
```

---

## Summary Table

| Problem | Key Technique | Time Complexity |
|---------|---------------|-----------------|
| Basic Binary Search | Standard template | O(log n) |
| Lower Bound | First >= target | O(log n) |
| Upper Bound | First > target | O(log n) |
| Search Insert | Same as lower bound | O(log n) |
| Floor/Ceil | Track last valid answer | O(log n) |
| First/Last Occurrence | Modified BS | O(log n) |
| Count Occurrences | Last - First + 1 | O(log n) |
| Rotated Array I | Identify sorted half | O(log n) |
| Rotated Array II | Handle duplicates | O(n) worst |
| Find Minimum | Find rotation point | O(log n) |
| Count Rotations | Index of minimum | O(log n) |
| Single Element | Check pair positions | O(log n) |
| Peak Element | Move toward higher | O(log n) |

---

## Key Takeaways

1. **Binary Search Template**: Master the basic template with `low`, `high`, and `mid`
2. **Prevent Overflow**: Use `mid = low + (high - low) / 2`
3. **Search Space Reduction**: Always eliminate half the search space
4. **Answer Storage**: Sometimes store potential answers while continuing search
5. **Edge Cases**: Handle single element, empty array, and boundary conditions
6. **Sorted Property**: Binary search works on monotonic functions (not just arrays)

Practice these patterns and you'll be able to solve any binary search problem! 🚀