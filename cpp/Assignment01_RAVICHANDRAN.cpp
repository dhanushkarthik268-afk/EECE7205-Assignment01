// Assignment #01 - EECE 7205: Fundamentals of Computer Engineering
// Author: Dhanush Karthik Ravichandran
//
// Single program with a menu that runs any of the 10 problems.
// Each problem lives in its own function.

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <queue>
using namespace std;

// =====================================================================
// Problem function declarations
// =====================================================================
void problem1();
void problem2();
void problem3();
void problem4();
void problem5();
void problem6();
void problem7();
void problem8();
void problem9();
void problem10();

// =====================================================================
// Problem 1: Merge Intervals
// =====================================================================
void printIntervals(const vector<vector<int>>& intervals) {
    cout << "[";
    for (size_t i = 0; i < intervals.size(); i++) {
        cout << "[" << intervals[i][0] << "," << intervals[i][1] << "]";
        if (i + 1 < intervals.size()) cout << ", ";
    }
    cout << "]\n";
}

vector<vector<int>> mergeIntervals(vector<vector<int>> intervals) {
    vector<vector<int>> merged;
    if (intervals.empty()) return merged;   // edge case: nothing to merge

    sort(intervals.begin(), intervals.end(),
         [](const vector<int>& a, const vector<int>& b) {
             return a[0] < b[0];
         });

    merged.push_back(intervals[0]);

    for (size_t i = 1; i < intervals.size(); i++) {
        vector<int>& last = merged.back();
        if (intervals[i][0] <= last[1]) {
            last[1] = max(last[1], intervals[i][1]);
        } else {
            merged.push_back(intervals[i]);
        }
    }
    return merged;
}

void problem1() {
    cout << "\n--- Problem 1: Merge Intervals ---\n";

    vector<vector<int>> t1 = {{1,3},{2,6},{8,10},{15,18}};
    cout << "Input:  "; printIntervals(t1);
    cout << "Output: "; printIntervals(mergeIntervals(t1));

    vector<vector<int>> t2 = {{1,4},{2,5},{3,6}};
    cout << "\nInput:  "; printIntervals(t2);
    cout << "Output: "; printIntervals(mergeIntervals(t2));

    vector<vector<int>> t3 = {};
    cout << "\nInput:  "; printIntervals(t3);
    cout << "Output: "; printIntervals(mergeIntervals(t3));
}

// =====================================================================
// Problem 2: Sort Colors (0s, 1s, 2s)
// =====================================================================
void printArray(const vector<int>& a) {
    cout << "[";
    for (size_t i = 0; i < a.size(); i++) {
        cout << a[i];
        if (i + 1 < a.size()) cout << ", ";
    }
    cout << "]\n";
}

vector<int> sortColorsCounting(vector<int> nums) {
    int count[3] = {0, 0, 0};
    for (int x : nums) count[x]++;

    int index = 0;
    for (int value = 0; value < 3; value++) {
        for (int c = 0; c < count[value]; c++) {
            nums[index++] = value;
        }
    }
    return nums;
}

vector<int> sortColorsDNF(vector<int> nums) {
    int low = 0;
    int mid = 0;
    int high = (int)nums.size() - 1;

    while (mid <= high) {
        if (nums[mid] == 0) {
            swap(nums[low], nums[mid]);
            low++; mid++;
        } else if (nums[mid] == 1) {
            mid++;
        } else {
            swap(nums[mid], nums[high]);
            high--;
        }
    }
    return nums;
}

void problem2() {
    cout << "\n--- Problem 2: Sort Colors ---\n";

    vector<int> t1 = {2, 0, 2, 1, 1, 0};
    cout << "Input:            "; printArray(t1);
    cout << "Counting sort:    "; printArray(sortColorsCounting(t1));
    cout << "Dutch Nat. Flag:  "; printArray(sortColorsDNF(t1));

    vector<int> t2 = {0, 0, 1, 2, 2};
    cout << "\nInput:            "; printArray(t2);
    cout << "Counting sort:    "; printArray(sortColorsCounting(t2));
    cout << "Dutch Nat. Flag:  "; printArray(sortColorsDNF(t2));

    vector<int> t3 = {};
    cout << "\nInput:            "; printArray(t3);
    cout << "Counting sort:    "; printArray(sortColorsCounting(t3));
    cout << "Dutch Nat. Flag:  "; printArray(sortColorsDNF(t3));
}

// =====================================================================
// Problem 3: Largest Number
// =====================================================================
string largestNumber(vector<int>& nums) {
    if (nums.empty()) return "";

    vector<string> strNums;
    for (int num : nums) {
        strNums.push_back(to_string(num));
    }

    sort(strNums.begin(), strNums.end(), [](const string& a, const string& b) {
        return a + b > b + a;
    });

    if (strNums[0] == "0") return "0";

    string result = "";
    for (const string& s : strNums) {
        result += s;
    }

    return result;
}

void problem3() {
    cout << "\n--- Problem 3: Largest Number ---\n";

    vector<int> nums1 = {10, 2};
    cout << "Input: [10, 2]\n";
    cout << "Output: " << largestNumber(nums1) << "\n\n";

    vector<int> nums2 = {3, 30, 34, 5, 9};
    cout << "Input: [3, 30, 34, 5, 9]\n";
    cout << "Output: " << largestNumber(nums2) << "\n\n";

    vector<int> nums3 = {0, 0};
    cout << "Input: [0, 0]\n";
    cout << "Output: " << largestNumber(nums3) << "\n";
}

// =====================================================================
// Problem 4: Group Anagrams
// =====================================================================
void printGroups(const vector<vector<string>>& groups) {
    cout << "Output: [\n";
    for (const auto& group : groups) {
        cout << "  [";
        for (size_t i = 0; i < group.size(); ++i) {
            cout << "\"" << group[i] << "\"" << (i + 1 < group.size() ? ", " : "");
        }
        cout << "]\n";
    }
    cout << "]\n";
}

vector<vector<string>> groupAnagrams(vector<string>& strs) {
    unordered_map<string, vector<string>> anagramMap;

    for (const string& str : strs) {
        string key = str;
        sort(key.begin(), key.end()); // Sorted string acts as the map key
        anagramMap[key].push_back(str);
    }

    vector<vector<string>> result;
    for (auto& pair : anagramMap) {
        result.push_back(pair.second);
    }

    return result;
}

void problem4() {
    cout << "\n--- Problem 4: Group Anagrams ---\n";

    vector<string> strs1 = {"eat", "tea", "tan", "ate", "nat", "bat"};
    cout << "Input: [\"eat\", \"tea\", \"tan\", \"ate\", \"nat\", \"bat\"]\n";
    vector<vector<string>> result1 = groupAnagrams(strs1);
    printGroups(result1);
    cout << "\n";

    vector<string> strs2 = {""};
    cout << "Input: [\"\"]\n";
    vector<vector<string>> result2 = groupAnagrams(strs2);
    printGroups(result2);
    cout << "\n";

    vector<string> strs3 = {};
    cout << "Input: []\n";
    vector<vector<string>> result3 = groupAnagrams(strs3);
    printGroups(result3);
}

// =====================================================================
// Problem 5: Meeting Rooms (can one person attend all meetings?)
// =====================================================================
bool canAttendMeetings(vector<vector<int>>& intervals) {
    if (intervals.empty()) return true;

    sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
        return a[0] < b[0];
    });

    for (size_t i = 1; i < intervals.size(); ++i) {
        if (intervals[i][0] < intervals[i - 1][1]) {
            return false;
        }
    }

    return true;
}

void problem5() {
    cout << "\n--- Problem 5: Meeting Rooms ---\n";

    vector<vector<int>> intervals1 = {{0, 30}, {5, 10}, {15, 20}};
    cout << "Input: [[0,30], [5,10], [15,20]] -> "
         << (canAttendMeetings(intervals1) ? "true" : "false") << "\n";

    vector<vector<int>> intervals2 = {{7, 10}, {2, 4}};
    cout << "Input: [[7,10], [2,4]] -> "
         << (canAttendMeetings(intervals2) ? "true" : "false") << "\n";

    vector<vector<int>> intervals3 = {{1, 5}, {5, 10}}; // Back-to-back allowed
    cout << "Input: [[1,5], [5,10]] -> "
         << (canAttendMeetings(intervals3) ? "true" : "false") << "\n";
}

// =====================================================================
// Problem 6: K Closest Points to Origin
// =====================================================================
void printPoints(const vector<vector<int>>& points) {
    cout << "[";
    for (size_t i = 0; i < points.size(); ++i) {
        cout << "[" << points[i][0] << "," << points[i][1] << "]"
             << (i + 1 < points.size() ? ", " : "");
    }
    cout << "]\n";
}

// Approach 1: Max-Heap Solution - O(N log K)
vector<vector<int>> kClosestHeap(vector<vector<int>>& points, int k) {
    if (k > static_cast<int>(points.size())) {
        k = static_cast<int>(points.size());
    }

    priority_queue<pair<int, int>> maxHeap;

    for (size_t i = 0; i < points.size(); ++i) {
        int dist = points[i][0] * points[i][0] + points[i][1] * points[i][1];
        maxHeap.push({dist, static_cast<int>(i)});

        if (static_cast<int>(maxHeap.size()) > k) {
            maxHeap.pop();
        }
    }

    vector<vector<int>> result;
    while (!maxHeap.empty()) {
        result.push_back(points[maxHeap.top().second]);
        maxHeap.pop();
    }
    return result;
}

// Approach 2: Full Sorting Solution - O(N log N)
vector<vector<int>> kClosestSort(vector<vector<int>>& points, int k) {
    if (k > static_cast<int>(points.size())) {
        k = static_cast<int>(points.size());
    }

    vector<vector<int>> sortedPoints = points;
    sort(sortedPoints.begin(), sortedPoints.end(), [](const vector<int>& a, const vector<int>& b) {
        return (a[0]*a[0] + a[1]*a[1]) < (b[0]*b[0] + b[1]*b[1]);
    });
    return vector<vector<int>>(sortedPoints.begin(), sortedPoints.begin() + k);
}

void problem6() {
    cout << "\n--- Problem 6: K Closest Points to Origin ---\n";

    vector<vector<int>> points1 = {{1, 3}, {-2, 2}};
    int k1 = 1;
    cout << "Test Case 1:\n";
    cout << "Input: points = [[1,3], [-2,2]], k = 1\n";
    cout << "Output (Heap): ";
    vector<vector<int>> res1_heap = kClosestHeap(points1, k1);
    printPoints(res1_heap);
    cout << "Output (Sort): ";
    vector<vector<int>> res1_sort = kClosestSort(points1, k1);
    printPoints(res1_sort);
    cout << "\n";

    vector<vector<int>> points2 = {{3, 3}, {5, -1}, {-2, 4}};
    int k2 = 2;
    cout << "Test Case 2:\n";
    cout << "Input: points = [[3,3], [5,-1], [-2,4]], k = 2\n";
    cout << "Output (Heap): ";
    vector<vector<int>> res2_heap = kClosestHeap(points2, k2);
    printPoints(res2_heap);
    cout << "Output (Sort): ";
    vector<vector<int>> res2_sort = kClosestSort(points2, k2);
    printPoints(res2_sort);
    cout << "\n";

    vector<vector<int>> points3 = {{1, 1}, {2, 2}};
    int k3 = 5;
    cout << "Test Case 3 (k > N edge case):\n";
    cout << "Input: points = [[1,1], [2,2]], k = 5\n";
    cout << "Output (Heap): ";
    vector<vector<int>> res3_heap = kClosestHeap(points3, k3);
    printPoints(res3_heap);
    cout << "Output (Sort): ";
    vector<vector<int>> res3_sort = kClosestSort(points3, k3);
    printPoints(res3_sort);
}

// =====================================================================
// Problem 7: Top K Frequent Elements (tie -> smaller value first)
// =====================================================================
void printVectorP7(const vector<int>& vec) {
    cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        cout << vec[i] << (i + 1 < vec.size() ? ", " : "");
    }
    cout << "]\n";
}

struct CompareP7 {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
        // Higher frequency comes first (max-heap on frequency)
        if (a.second != b.second) {
            return a.second < b.second;
        }
        // Tie-breaker: smaller value comes first
        return a.first > b.first;
    }
};

vector<int> topKFrequent(const vector<int>& nums, int k) {
    unordered_map<int, int> freqMap;
    for (int num : nums) {
        freqMap[num]++;
    }

    if (k > static_cast<int>(freqMap.size())) {
        k = static_cast<int>(freqMap.size());
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, CompareP7> maxHeap;
    for (const auto& entry : freqMap) {
        maxHeap.push({entry.first, entry.second}); // {value, frequency}
    }

    vector<int> result;
    while (!maxHeap.empty() && static_cast<int>(result.size()) < k) {
        result.push_back(maxHeap.top().first);
        maxHeap.pop();
    }
    return result;
}

void problem7() {
    cout << "\n--- Problem 7: Top K Frequent Elements ---\n";

    vector<int> nums1 = {1, 1, 1, 2, 2, 3, 4, 4};
    int k1 = 2;
    cout << "Input: nums = [1, 1, 1, 2, 2, 3, 4, 4], k = 2\n";
    cout << "Output: ";
    printVectorP7(topKFrequent(nums1, k1));
    cout << "\n";

    // Edge case: k exceeds number of unique elements
    vector<int> nums2 = {5, 5, 6};
    int k2 = 10;
    cout << "Input: nums = [5, 5, 6], k = 10 (k > unique count)\n";
    cout << "Output: ";
    printVectorP7(topKFrequent(nums2, k2));
}

// =====================================================================
// Problem 8: Merge K Sorted Integer Arrays
// =====================================================================
void printVectorP8(const vector<int>& vec) {
    cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        cout << vec[i] << (i + 1 < vec.size() ? ", " : "");
    }
    cout << "]\n";
}

struct ElementP8 {
    int val;
    int arrayIdx;
    int elementIdx;

    bool operator>(const ElementP8& other) const {
        return val > other.val; // Min-heap behavior
    }
};

vector<int> mergeKSortedArrays(const vector<vector<int>>& arrays) {
    priority_queue<ElementP8, vector<ElementP8>, greater<ElementP8>> minHeap;

    for (size_t i = 0; i < arrays.size(); ++i) {
        if (!arrays[i].empty()) {
            minHeap.push({arrays[i][0], static_cast<int>(i), 0});
        }
    }

    vector<int> mergedResult;
    while (!minHeap.empty()) {
        ElementP8 curr = minHeap.top();
        minHeap.pop();

        mergedResult.push_back(curr.val);

        if (curr.elementIdx + 1 < static_cast<int>(arrays[curr.arrayIdx].size())) {
            minHeap.push({
                arrays[curr.arrayIdx][curr.elementIdx + 1],
                curr.arrayIdx,
                curr.elementIdx + 1
            });
        }
    }
    return mergedResult;
}

void problem8() {
    cout << "\n--- Problem 8: Merge K Sorted Integer Arrays ---\n";

    vector<vector<int>> arrays1 = {{1, 4, 7}, {2, 5, 8}, {0, 3, 6, 9}};
    cout << "Test Case 1:\n";
    cout << "Input: [[1, 4, 7], [2, 5, 8], [0, 3, 6, 9]]\n";
    cout << "Output: ";
    printVectorP8(mergeKSortedArrays(arrays1));
    cout << "\n";

    vector<vector<int>> arrays2 = {{1, 10}, {}, {2, 3, 4, 11}, {5}};
    cout << "Test Case 2 (Varying lengths & empty array edge case):\n";
    cout << "Input: [[1, 10], [], [2, 3, 4, 11], [5]]\n";
    cout << "Output: ";
    printVectorP8(mergeKSortedArrays(arrays2));
}

// =====================================================================
// Problem 9: Kth Largest Element in an Array
// =====================================================================
int findKthLargest(const vector<int>& nums, int k) {
    if (nums.empty()) return -1;

    if (k > static_cast<int>(nums.size())) {
        k = static_cast<int>(nums.size());
    }

    // Min-heap of size k keeps the k largest; its top is the kth largest
    priority_queue<int, vector<int>, greater<int>> minHeap;

    for (int num : nums) {
        minHeap.push(num);
        if (static_cast<int>(minHeap.size()) > k) {
            minHeap.pop();
        }
    }
    return minHeap.top();
}

void problem9() {
    cout << "\n--- Problem 9: Kth Largest Element ---\n";

    vector<int> nums1 = {3, 2, 1, 5, 6, 4};
    int k1 = 2;
    cout << "Test Case 1:\n";
    cout << "Input: nums = [3, 2, 1, 5, 6, 4], k = 2\n";
    cout << "Output: " << findKthLargest(nums1, k1) << "\n\n";

    vector<int> nums2 = {3, 2, 3, 1, 2, 4, 5, 5, 6};
    int k2 = 4;
    cout << "Test Case 2 (Duplicates counting as separate positions):\n";
    cout << "Input: nums = [3, 2, 3, 1, 2, 4, 5, 5, 6], k = 4\n";
    cout << "Output: " << findKthLargest(nums2, k2) << "\n";
}

// =====================================================================
// Problem 10: Count Inversions   <-- NOT DONE YET
// Question: count pairs (i, j) with i < j and values[i] > values[j].
// Requirement: primary solution must run in O(n log n) by modifying
// merge sort. Use a 64-bit integer (long long) for the count.
// =====================================================================
static void printVectorP10(const vector<int>& vec) {
    cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        cout << vec[i] << (i + 1 < vec.size() ? ", " : "");
    }
    cout << "]";
}

// Merge step that counts cross-inversions in O(n)
long long mergeAndCount(vector<int>& arr, vector<int>& temp, int left, int mid, int right) {
    int i = left;    // Index for left subarray [left...mid]
    int j = mid + 1; // Index for right subarray [mid+1...right]
    int k = left;    // Index for merged result in temp
    long long invCount = 0;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            // arr[i] > arr[j] implies an inversion!
            // All remaining elements in left subarray arr[i...mid] are greater than arr[j]
            temp[k++] = arr[j++];
            invCount += (mid - i + 1);
        }
    }

    // Copy remaining elements of left subarray, if any
    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    // Copy remaining elements of right subarray, if any
    while (j <= right) {
        temp[k++] = arr[j++];
    }

    // Copy merged elements back into original array
    for (i = left; i <= right; i++) {
        arr[i] = temp[i];
    }

    return invCount;
}

// Recursive function that divides array and sums inversions
long long mergeSortAndCount(vector<int>& arr, vector<int>& temp, int left, int right) {
    long long invCount = 0;
    if (left < right) {
        int mid = left + (right - left) / 2;

        invCount += mergeSortAndCount(arr, temp, left, mid);
        invCount += mergeSortAndCount(arr, temp, mid + 1, right);
        invCount += mergeAndCount(arr, temp, left, mid, right);
    }
    return invCount;
}

// Main algorithm for Problem 10
long long countInversions(vector<int> arr) {
    if (arr.empty()) return 0;
    vector<int> temp(arr.size());
    return mergeSortAndCount(arr, temp, 0, static_cast<int>(arr.size()) - 1);
}

// Function called by menu loop
void problem10() {
    cout << "=== Problem 10: Count Inversions ===\n";

    // Test Case 1: Example from problem statement
    vector<int> nums1 = {2, 4, 1, 3, 5};
    cout << "Test Case 1:\n";
    cout << "Input: ";
    printVectorP10(nums1);
    cout << "\nOutput: " << countInversions(nums1) << "\n\n";

    // Test Case 2: Fully reversed array (maximum inversions case)
    vector<int> nums2 = {5, 4, 3, 2, 1};
    cout << "Test Case 2 (Reversed array):\n";
    cout << "Input: ";
    printVectorP10(nums2);
    cout << "\nOutput: " << countInversions(nums2) << "\n";
}

// =====================================================================
// Menu / Driver
// =====================================================================
int main() {
    int choice = -1;

    while (choice != 0) {
        cout << "\n========== Assignment 01 ==========\n";
        cout << " 1. Merge Intervals\n";
        cout << " 2. Sort Colors (0/1/2)\n";
        cout << " 3. Largest Number\n";
        cout << " 4. Group Anagrams\n";
        cout << " 5. Meeting Rooms (can attend all?)\n";
        cout << " 6. K Closest Points to Origin\n";
        cout << " 7. Top K Frequent Elements\n";
        cout << " 8. Merge K Sorted Arrays\n";
        cout << " 9. Kth Largest Element\n";
        cout << "10. Count Inversions\n";
        cout << " 0. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input, please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1:  problem1();  break;
            case 2:  problem2();  break;
            case 3:  problem3();  break;
            case 4:  problem4();  break;
            case 5:  problem5();  break;
            case 6:  problem6();  break;
            case 7:  problem7();  break;
            case 8:  problem8();  break;
            case 9:  problem9();  break;
            case 10: problem10(); break;
            case 0:  cout << "Goodbye!\n"; break;
            default: cout << "No such option, try again.\n"; break;
        }
    }
    return 0;
}
