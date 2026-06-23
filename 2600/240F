#include <bits/stdc++.h>
#pragma optimize "Ofast"
// #define int long long
using namespace std;
struct seg {
    int total;
    int lazy;
    bool set;
};
seg tree[26][400005];
void prop(int arr, int pos, int l, int r) {
    if(tree[arr][pos].set) {
        tree[arr][pos].total = 0;
        tree[arr][pos].lazy = 0;
        if(l + 1 != r) {
            tree[arr][pos * 2].lazy = 0;
            tree[arr][pos * 2 + 1].lazy = 0;
            tree[arr][pos * 2].set = true;
            tree[arr][pos *2 + 1].set = true;
        }
        tree[arr][pos].set = false;
    }
}
void propogate(int arr, int pos, int l, int r) {
    //We want this node to not be set, and also have no lazyness.
    if(l + 1 == r) {
        if(tree[arr][pos].set) {
            tree[arr][pos].set = false;
            tree[arr][pos].total = 0;
        }else {
            tree[arr][pos].total += tree[arr][pos].lazy;
            tree[arr][pos].lazy = 0;
        }
    }else {
        int mid = (l + r ) / 2;
        if(tree[arr][pos].set) {
            tree[arr][pos].total = 0;
            tree[arr][pos * 2].lazy = 0;
            tree[arr][pos * 2 + 1].lazy = 0;
            tree[arr][pos * 2].set = true;
            tree[arr][pos *2 + 1].set = true;
            tree[arr][pos].set = false;
        }else if(tree[arr][pos].lazy){
            if(tree[arr][pos*2].set)prop(arr,pos*2,l,mid);
            if(tree[arr][pos*2+1].set)prop(arr,pos*2+1,mid,r);
            tree[arr][pos*2].lazy += tree[arr][pos].lazy;
            tree[arr][pos * 2 + 1].lazy += tree[arr][pos].lazy;
            tree[arr][pos].total += (r - l) * tree[arr][pos].lazy;
            tree[arr][pos].lazy = 0;
        }
    }
}
int query(int arr, int left, int right, int pos = 1, int l = 0, int r = 100005, int lazy = 0, bool set = false) {
    if(tree[arr][pos].set) set = true;
    if(!set) lazy += tree[arr][pos].lazy;
    if(l >= left && right >= r) {
        if(set) return (r - l) * lazy;
        return tree[arr][pos].total + (r - l) * lazy;
    }
    int mid = (l + r) / 2;
    int total = 0;
    if(left < mid) {
        total += query(arr, left, right, pos * 2, l, mid, lazy, set);
    }
    if(right > mid) {
        total += query(arr, left, right, pos * 2 + 1, mid, r, lazy, set);
    }
    return total;
}
void updateadd(int arr, int left, int right, int pos = 1, int l = 0, int r = 100005) {
    propogate(arr, pos, l, r);
    if(l >= left && right >= r) {
        tree[arr][pos].lazy ++;
        return;
    }
    int mid = (l +r) / 2;
    if(mid > left) {
        updateadd(arr,left,right,pos*2,l,mid);
    }
    if(mid < right) {
        updateadd(arr,left,right,pos*2+1,mid,r);
    }
    propogate(arr, pos*2, l, mid);
    propogate(arr, pos*2+1, mid, r);
    tree[arr][pos].total = tree[arr][pos * 2].total + tree[arr][pos *2 +1].total;
}

void updateset(int arr, int left, int right, int pos = 1, int l = 0, int r = 100005) {
    propogate(arr, pos, l, r);
    if(l >= left && right >= r) {
        tree[arr][pos].set = true;
        return;
    }
    int mid = (l +r) / 2;
    if(mid > left) {
        updateset(arr,left,right,pos*2,l,mid);
    }
    if(mid < right) {
        updateset(arr,left,right,pos*2+1,mid,r);
    }
    propogate(arr, pos*2, l, mid);
    propogate(arr, pos*2+1, mid, r);
    tree[arr][pos].total = tree[arr][pos * 2].total + tree[arr][pos *2 +1].total;
}
int rdint() {
    bool isneg = false;
    char c = getchar();
    while((c < '0' || c > '9')) {
        if(c == '-') {
            isneg = true;
        }
        c = getchar();
    }
    int a = 0;
    while(true) {
        a*=10;
        a+= c-'0';
        c = getchar();
        if(c < '0' || c > '9') break;
    }
    if(isneg) a *= -1;
    return a;
}
void prtint(int num) {
    if(num == 0) {
        putchar('0');
        putchar('\n');
        return;
    }
    if(num < 0) {
        num *= -1;
        putchar('-');
    }
    int val = 1000000000;
    while(num < val) {
        val /= 10;
    }
    while(val >= 1) {
        putchar('0' + (num / val) % 10);
        val /= 10;
    }
}
string rdstring() {
    string s;
    char c = getchar();
    while(isspace(c)) c = getchar();
    while(true) {
        s.push_back(c);
        if(isspace(c)) break;
        c = getchar();
    }
    return s;
}
void prtstr(string s) {
    for(char i : s) {
        putchar(i);
    }
}
signed main() {
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int n = rdint();
    int m = rdint();
    for(int i = 0; i < n; i++) {
        char c = getchar();
        updateadd(c-'a', i, i+1);
    }
    for(int i = 0; i < m; i++) {
        int l = rdint();
        int r = rdint();
        int ma[2];
        ma[0] = 0;
        ma[1] = 0;
        int qrange[26];
        for(int j = 0; j < 26; j++) qrange[j] = query(j, l-1, r);
        for(int j = 0; j < 26; j++) ma[qrange[j] %2]++;
        if(ma[1] == (r - l +1) % 2) {
            int pos = 0;
            int total = 0;
            for(int j = 0; j < 26; j++) {
                int a = qrange[j];
                total += a;
                if(a != 0) {
                    updateset(j, l-1, r);
                    if(a % 2 == 1) {
                        updateadd(j, (r + l-1) / 2, (r + l-1)/2+1);
                        a--;
                    }
                    if(a != 0) {
                        updateadd(j, l-1 + pos, l-1+pos + a/2);
                        updateadd(j, r - pos - a/2, r - pos);
                        pos += a/2;
                    }
                }
            }
        }
    }

    string s;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < 26; j++) {
            if(query(j, i, i+ 1) == 1) {
                s += (char)('a' +j);
            }
        }
    }
    s+='\n';
    prtstr(s);
    return 0;
}
