#include <iostream>
using namespace std;
// iterative tower of hanoi, each peg is a simple array used like a stack
// the pattern repeats every 3 moves:
//   move 1: make the legal move between peg A and peg C
//   move 2: make the legal move between peg A and peg B
//   move 3: make the legal move between peg B and peg C
// if the number of disks is even, we swap the names of B and C first
// total moves = 2^n - 1 and each move is O(1), so time is O(2^n)
int peg[3][30];       // peg[i] holds the disks on peg i
int top[3];           // top[i] = how many disks are on peg i
char name[3] = {'A', 'B', 'C'};
// move one disk between peg x and peg y, whichever direction is legal
void moveDisk(int x, int y) {
    int from, to;
    if (top[x] == 0) {
        from = y; to = x;
    }
    else if (top[y] == 0) {
        from = x; to = y;
    }
    else if (peg[x][top[x] - 1] < peg[y][top[y] - 1]) {
        from = x; to = y;
    }
    else {
        from = y; to = x;
    }
    // take the top disk off 'from' and put it on 'to'
    int disk = peg[from][top[from] - 1];
    top[from]--;
    peg[to][top[to]] = disk;
    top[to]++;
    cout << "Move disk " << disk << " from " << name[from] << " to " << name[to] << endl;
}
int main() {
    int n = 3;
    for (int i = 0; i < 3; i++) top[i] = 0;
    // even number of disks, swap names of B and C
    if (n % 2 == 0) {
        char temp = name[1];
        name[1] = name[2];
        name[2] = temp;
    }
    // biggest disk first so the smallest is on top
    for (int i = n; i >= 1; i--) {
        peg[0][top[0]] = i;
        top[0]++;
    }
    int total = 1;
    for (int i = 0; i < n; i++) total = total * 2;
    total = total - 1;
    for (int i = 1; i <= total; i++) {
        if (i % 3 == 1) moveDisk(0, 2);
        else if (i % 3 == 2) moveDisk(0, 1);
        else moveDisk(1, 2);
    }
    return 0;
}