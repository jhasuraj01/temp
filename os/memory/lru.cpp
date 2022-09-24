#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    int frames[n], counter[n];
    int size = 0;

    int m;
    cin >> m;

    for(int i = 0; i < m; ++i) {
        int new_page;
        cin >> new_page;

        bool page_present = false;
        for(int i = 0; i < size; ++i) {
            if(frames[i] == new_page) page_present = true;
        }

        if(size == n) {

            int indexRep = 0;
            int count = counter[0];
            for(int i = 0; i < n; ++i) {
                if(counter[i] > count) {
                    count = counter[i];
                    indexRep = i;
                }
            }

            for(int i = 0; i < n; ++i) {
                counter[i]++;
            }

            if(!page_present) {
                counter[indexRep] = 0;
                frames[indexRep] = new_page;
            }
            else {
                for(int i = 0; i < n; ++i) {
                    if(frames[i] == new_page) {
                        counter[i] = 0;
                    }
                }
            }
        }
        else if(!page_present) {
            for(int i = 0; i < size; ++i) {
                counter[i]++;
            }
            frames[size] = new_page;
            counter[size++] = 0;
        }

        cout << "Page Called: " << new_page << " => ";

        for(int i = 0; i < size; ++i) {
            cout << frames[i] << " ";
        }

        if(!page_present) {
            cout << "(F)\n";
        }
        else {
            cout << "(NF)\n";
        }
    }

    return 0;
}