#include<bits/stdc++.h>
#include <sys/types.h>
#include <unistd.h>
using namespace std;

void sort(vector<int> &A) {
    int n = A.size();
    for (int i = 0; i < n; ++i)
    {
        for (int j = i+1; j < n; j++)
        {
            if(A[j-1] > A[j]) {
                swap(A[j-1], A[j]);
            }
        }
        
    }
    
}

int main() {
    int N;
    cout << "Enter No. of Elements: ";
    cin >> N;

    cout << "Enter Elements (Space Seperated): ";
    vector<int> nums(N);
    for (size_t i = 0; i < N; i++) cin >> nums[i];

    int pid = fork();

    if(pid == 0) {
        sort(nums.begin(), nums.end());
        for (size_t i = 0; i < 10; i++) {
            sleep(1);
            printf("Child => \t PID: %d, PPID: %d\n", getpid(), getppid());
        }

        cout << "Child Terminating!" << endl;
        cout << "Array sorted by Child: ";
        for (int num: nums) cout << num << " ";
        cout << '\n';

    }
    else if(pid > 0) {
        sort(nums.begin(), nums.end());
        for (size_t i = 0; i < 5; i++) {
            sleep(1);
            printf("Parent => \t PID: %d, PPID: %d\n", getpid(), getppid());
        }

        cout << "Parent Terminating" << endl;
        cout << "Array sorted by Parent: ";
        for (int num: nums) cout << num << " ";
        cout << '\n';

    }
    else {
        cout << "Process Creation failed" << endl;
    }

    return 0;
}