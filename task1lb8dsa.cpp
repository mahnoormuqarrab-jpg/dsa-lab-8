#include <iostream>
using namespace std;
// binary search on columns
// take the middle column and find the biggest number in it
// if the left or right neighbour is bigger, a peak must be on that side
// so we drop the other half. if not, this number is a peak
// we scan a column (n) and do it about log n times -> O(n log n)
int main() {
    int a[4][4] = {
        {10, 8, 10, 10},
        {14, 13, 12, 11},
        {15, 9, 11, 21},
        {16, 17, 19, 20}
    };
    int rows = 4;
    int cols = 4;
    int low = 0, high = cols - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        // row of the biggest number in the middle column
        int r = 0;
        for (int i = 0; i < rows; i++) {
            if (a[i][mid] > a[r][mid]) r = i;
        }
        int val = a[r][mid];
        int left = -1000000, right = -1000000;
        if (mid > 0) left = a[r][mid - 1];
        if (mid < cols - 1) right = a[r][mid + 1];
        if (val >= left && val >= right) {
            cout << "Peak is " << val << " at row " << r << ", column " << mid << endl;
            return 0;
        }
        else if (left > val) {
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }
    return 0;
}