//
// Created by migav on 29/08/2023.
//

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 8e5;

typedef vector<int> vi;
typedef vector<long long> vll;

class SegmentTree { // the segment tree is stored like a heap array
private: vll st; vi A; // recall that vi is: typedef vector<int> vi;
    int n;
    int left (int p) { return p << 1; } // same as binary heap operations
    int right(int p) { return (p << 1) + 1; }
    void build(int p, int L, int R) { // O(n)
        if (L == R) // as L == R, either one is fine
            st[p] = A[L]; // store the value
        else { // recursively compute the values
            build(left(p) , L , (L + R) / 2);
            build(right(p), (L + R) / 2 + 1, R );
            st[p] = min(st[left(p)], st[right(p)]);
        }
    }
    long long rmq(int p, int L, int R, int i, int j) { // O(log n)
        if (i > R || j < L) return -1; // current segment outside query range
        if (L >= i && R <= j) return st[p]; // inside query range
// compute the min position in the left and right part of the interval
        long long p1 = rmq(left(p) , L , (L+R) / 2, i, j);
        long long p2 = rmq(right(p), (L+R) / 2 + 1, R , i, j);
        if (p1 == -1) return p2; // if we try to access segment outside query
        if (p2 == -1) return p1; // same as above
        return min(p1, p2); // as in build routine
    }
    void update(int p, int L, int R, int i, int val) {
        if(L == R)
            st[p] = val;
        else {
            int M = (L+R)/2;
            if(i <= M) update(left(p), L, M, i, val);
            else update(right(p), M+1, R, i, val);
            st[p] = min(st[left(p)], st[right(p)]);
        }
    }
public:
    SegmentTree(const vi &_A) {
        A = _A; n = (int)A.size(); // copy content for local usage
        st.assign(4 * n, 0); // create large enough vector of zeroes
        build(1, 0, n - 1); // recursive build
    }
    long long rmq(int i, int j) { return rmq(1, 0, n - 1, i, j); } // overloading
    void update(int i, int val) { return update(1, 0, n - 1, i, val); }
};

int main() {
    vi A;
    int n, q, t, a, b;
    cin >> n >> q;
    A.assign(n, 0);
    for(int i = 0; i < n; i++)
        cin >> A[i];
    SegmentTree st(A);
    while(q--) {
        cin >> t >> a >> b;
        if(t == 1)
            st.update(a-1, b);
        else cout << st.rmq(a-1, b-1) << endl;
    }
}