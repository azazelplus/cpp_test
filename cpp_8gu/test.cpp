#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);    cin.tie(nullptr);

    int m,n; cin>>n>>m;
    string *arr = new string[n];
    int nn=n;
   for(int i=0;i<n;i++){
        cin >> arr[i];  
        reverse(arr[i].begin(),arr[i].end());    
    }

    for(int i=0;i<n;i++){
        cout << arr[n-i-1] << endl;
    }
}

