#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> frames;
    queue<int> qu;

    int m;
    cin >> m;

    for(int i = 0; i < m; ++i) {
        int new_page;
        cin >> new_page;

        bool page_present = false;

        if(frames.size() == n) {
            int replacement = qu.front(); qu.pop();
            qu.push(new_page);

            for(int frame: frames) {
                if(frame == new_page) page_present = true;
            }

            if(!page_present) {
                for(int &frame: frames) {
                    if(frame == replacement) frame = new_page;
                }
            }
        }
        else {
            frames.push_back(new_page);
            qu.push(new_page);
        }

        cout << "Page Called: " << new_page << " => ";

        for(int frame: frames) {
            cout << frame << " ";
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