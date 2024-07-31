#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> operation;


struct Result {
    //vi parking_slots;
    vector<operation> operations;
};

void print(int a[],int n){
    for(int i=0;i<n;i++){
        cout<<a[i]<<" ";
    }
    cout<<endl;
}

int input() {
    string s;
    cin >> s;
    int ans = 0;
    for (auto i : s) {
        if (i != ':') {
            ans *= 10;
            ans += int(i) - int('0');
        }
    }
    return ans;
}
int minmimum_energy(int present,int i,int k){
            return min(abs(present-i),min(abs(present+k-i),abs(i+k-present)));
}
int nearest_empty(vi &parking_queue,int present){
    if(parking_queue[present] == -1) return present;
    else {
        int k = parking_queue.size();
        int left = k+present,right = present,first_left = present,first_right = present;
        while(left>=0){
            if(parking_queue[(--left)%k] == -1){
                first_left = left%k;
                break;
            }
        }
        while(right<2*k){
            if(parking_queue[(++right)%k] == -1){
                first_right = right%k;
                break;
            }
        }
        if(minmimum_energy(present,first_left,k)<minmimum_energy(present,first_right,k)) return first_left;
        else return first_right;
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,k;
    cin>>n>>k;
    vi in_time,out_time,parking_queue(k,-1);
    map<int,int> m;
    Result ans;
    for(int i=0;i<n;i++) in_time.push_back(input());
    for(int i=0;i<n;i++){
        int x = input();
        out_time.push_back(x);
        m[in_time[i]] = x;
    }
    sort(in_time.begin(),in_time.end());
    sort(out_time.begin(),out_time.end());
    int pointer_in = 0,pointer_out = 0,energy = 0,present = 0;
    while(pointer_in<n){
        if(in_time[pointer_in]<out_time[pointer_out]){
            int index = nearest_empty(parking_queue,present);
            energy+=minmimum_energy(present,index,k);
            parking_queue[index] = m[in_time[pointer_in]];
            present = index;
            pointer_in++;
            ans.operations.push_back({pointer_in,present+1});
        }
        else if(in_time[pointer_in]>out_time[pointer_out]){
            int index;
            for(int i=0;i<parking_queue.size();i++){
                if(parking_queue[i] == out_time[pointer_out]){
                    index = i;
                    break;
                }
            }
            energy+=minmimum_energy(present,index,k);
            parking_queue[index] = -1;
            present = index;
            pointer_out++;
        }
    }
    while(pointer_out<n){
            int index;
            for(int i=0;i<parking_queue.size();i++){
                if(parking_queue[i] == out_time[pointer_out]){
                    index = i;
                    break;
                }
            }
            energy+=minmimum_energy(present,index,k);
            parking_queue[index] = -1;
            present = index;
            pointer_out++;
    }
    cout<<energy<<endl;
    for (const auto& op : ans.operations) {
        cout << "Car " << op.first << " parked in slot " << op.second << endl;
    }
    return 0;
}