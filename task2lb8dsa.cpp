#include <iostream>
using namespace std;
// backtracking knight's tour with a small optimization (Warnsdorff's rule)
// before moving, we try the square that has the fewest moves left first
// this way the knight rarely gets stuck, so it almost never backtracks
//
// best case: no backtracking, N*N squares with at most 8 moves each -> O(N^2)
// worst case: lots of backtracking, it becomes exponential (about 8^(N*N))
int n = 8;
int board[20][20];
int dx[8] = {2, 1, -1, -2, -2, -1, 1, 2};
int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};
bool canGo(int x, int y) {
    return x >= 0 && y >= 0 && x < n && y < n && board[x][y] == -1;
}
// how many free squares can the knight reach from (x, y)
int countMoves(int x, int y) {
    int count = 0;
    for (int k = 0; k < 8; k++) {
        if (canGo(x + dx[k], y + dy[k])) count++;
    }
    return count;
}
bool solve(int x, int y, int step) {
    board[x][y] = step;
    if (step == n * n - 1) return true;
    bool tried[8];
    for (int k = 0; k < 8; k++) tried[k] = false;
    // each round pick the untried move whose square has the fewest moves left
    for (int round = 0; round < 8; round++) {
        int best = -1;
        int bestCount = 100;
        for (int k = 0; k < 8; k++) {
            if (tried[k]) continue;
            int nx = x + dx[k];
            int ny = y + dy[k];
            if (canGo(nx, ny)) {
                int c = countMoves(nx, ny);
                if (c < bestCount) {
                    bestCount = c;
                    best = k;
                }
            }
        }
        if (best == -1) break;   // no more moves to try
        tried[best] = true;
        if (solve(x + dx[best], y + dy[best], step + 1)) return true;
    }
    // dead end, undo this square and go back
    board[x][y] = -1;
    return false;
}
int main() {
    int startX = 0, startY = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            board[i][j] = -1;
    if (solve(startX, startY, 0)) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout.width(3);
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
    }
    else {
        cout << "No tour found" << endl;
    }
    return 0;
}