/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Lampy sloneczne                               *
 *   Autor:                Adam Karczmarz                                *
 *   Zlozonosc czasowa:    O(n log^2 n)                                  *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Lista z przeskokami (skiplist)                *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>
#include <sstream>
#include <iostream>
#include <set>
#include <map>
#include <cassert>

#define REP(AA,BB) for(int AA=0; AA<(BB); ++AA)
#define FOR(AA,BB,CC) for(int AA=(BB); AA<(CC); ++AA)
#define FC(AA,BB) for(__typeof((AA).begin()) BB=(AA).begin(); BB!=(AA).end(); ++BB)
#define SZ(AA) ((int)((AA).size()))
#define ALL(AA) (AA).begin(), (AA).end()
#define PB push_back
#define MP make_pair

using namespace std;

typedef vector<int> VI;
typedef pair<int, int> PII;
typedef long long LL;
typedef long double LD;

const int MAXH = 15, INF = 1000000000;

struct sptr;

struct node {
    vector<sptr> next;
    int key;
    node (int k = -1) : key(k) {}
};

struct sptr {
    node *p;
    int len;
    sptr(node* _p = NULL, int _len = 0) : p(_p), len(_len) {}
};

int rand_h() {
    int res = 1;
    for (; res < MAXH && rand() % 2; ++res);
    return res;
}

sptr vis_st[MAXH];

struct skiplist {
    node head;
    int adv(node* &l, int q, int k) {
        int sum = 0;
        while (l->next[q].p != NULL && l->next[q].p->key <= k) {
            sum += l->next[q].len;
            l = l->next[q].p;
        }
        return sum;
    }
    int count_le(int k) {
        int res = 0;
        node *l = &head;
        for (int q = SZ(l->next) - 1; q >= 0; --q) {
            res += adv(l, q, k);
        }
        return res;
    }
    void insert(int k) {
        int H = rand_h();
        if (SZ(head.next) < H) {
            int ts = size();
            while (SZ(head.next) < H) {
                head.next.PB(sptr(NULL, ts));
            }
        }
        node *l = &head;
        for (int q = SZ(head.next) - 1; q >= 0; --q) {
            int j = adv(l, q, k);
            vis_st[q] = sptr(l, j);
        }
        node *t = new node(k);
        t->next = vector<sptr>(H);
        for (int q = 0, j = 1; q < H; ++q) {
            node *g = vis_st[q].p;
            t->next[q] = sptr(g->next[q].p, g->next[q].len - j + 1);
            g->next[q] = sptr(t, j);
            j += vis_st[q].len;
        }
        for (int q = H; q < SZ(head.next); ++q) {
            ++vis_st[q].p->next[q].len;
        }
    }
    int size() {
        if (head.next.empty()) {
            return 0;
        }
        node *l = &head;
        int res = adv(l, SZ(head.next) - 1, INF);
        return res + l->next.back().len;
    }
};

struct point {
    int x, y, k, id;
    bool operator<(const point &p) const {
        if (x == p.x) {
            return y < p.y;
        }
        return x < p.x;
    }
};

const int MAXN = 200000;
int BASE;
skiplist drz[1 << 19];
VI used;

void add(int t, int y) {
    t += BASE;
    while (t > 0) {
        used.PB(t);
        drz[t].insert(y);
        t /= 2;
    }
}

int find_time(int y, int K) {
    if (drz[1].count_le(y) < K) {
        return -1;
    }
    int p = 1;
    while (p < BASE) {
        int z = drz[2 * p].count_le(y);
        if (z >= K) {
            p = 2 * p;
        } else {
            K -= z;
            p = 2 * p + 1;
        }
    }
    return p - BASE;
}

point P[MAXN + 10];
int res[MAXN + 10];

void comp(point *p, int n) {
    FC (used, it) {
        drz[*it] = skiplist();
    }
    used.clear();
    REP (i, n) {
        int z = find_time(p[i].y, p[i].k);
        if (z == -1 || z > p[i].id) {
            z = p[i].id;
        }
        res[p[i].id] = z;
        add(z, p[i].y);
    }
}

int main(void) {
    bool zero = false;
    int n, X1, Y1, X2, Y2;
    scanf("%d%d%d%d%d", &n, &X1, &Y1, &X2, &Y2);
    if ((LL)X1 * Y2 - (LL)X2 * Y1 < 0) {
        swap(X1, X2);
        swap(Y1, Y2);
    } else if ((LL)X1 * Y2 == (LL)X2 * Y1) {
        X2 = X1;
        Y2 = Y1;
        zero = true;
    }
    REP (i, n) {
        scanf("%d%d", &P[i].x, &P[i].y);
        P[i].id = i;
    }
    REP (i, n) {
        scanf("%d", &P[i].k);
    }
    vector<LL> sX, sY;
    REP (i, n) {
        LL tx = (LL)P[i].x * Y2 - (LL)X2 * P[i].y;
        LL ty = zero ? (LL)X1 * P[i].x + (LL)Y2 * P[i].y : (LL)X1 * P[i].y - (LL)P[i].x * Y1;
        sX.PB(tx);
        sY.PB(ty);
    }
    sort(ALL(sX));
    sX.erase(unique(ALL(sX)), sX.end());
    sort(ALL(sY));
    sY.erase(unique(ALL(sY)), sY.end());
    REP (i, n) {
        LL tx = (LL)P[i].x * Y2 - (LL)X2 * P[i].y;
        LL ty = zero ? (LL)X1 * P[i].x + (LL)Y2 * P[i].y : (LL)X1 * P[i].y - (LL)P[i].x * Y1;
        P[i].x = lower_bound(ALL(sX), tx) - sX.begin();
        P[i].y = lower_bound(ALL(sY), ty) - sY.begin();
        ++P[i].x;
        ++P[i].y;
    }
    for (BASE = 1; BASE < n; BASE <<= 1);
    sort(P, P + n);
    if (!zero) {
        comp(P, n);
    } else {
        for (int i = 0; i < n; ) {
            int j;
            for (j = i; j < n && P[j].x == P[i].x; ++j);
            comp(P + i, j - i);
            i = j;
        }
    }
    REP (i, n) {
        if (i > 0) {
            putchar(' ');
        }
        printf("%d", res[i] + 1);
    }
    puts("");
    return 0;
}


