// #include<bits/stdc++.h>
// using namespace std;
// typedef long long ll;
// typedef vector<int> vi;
// void print(int a[],int n){
//     for(int i=0;i<n;i++){
//         cout<<a[i]<<" ";
//     }
//     cout<<endl;
// }
// void print(vi a){
//     for(auto i : a){
//         cout<<i<<" ";
//     }
//     cout<<endl;
// }
// int input(){
//         string s;
//         cin>>s;
//         int ans=0;
//         for(auto i :s){
//             if(i!=':'){
//                 ans*=10;
//                 ans+=int(i)-int('0');
//             }
//         }
//         return ans;
// }
// int minimum_energy(int parking_queue[],int k,int present){
//     set<pair<int,int>> removing_order;
//     for(int i=0;i<k;i++) if(parking_queue[i]!=-1)removing_order.insert({parking_queue[i],i});
//     int energy = 0;
//     for(auto i : removing_order){
//         energy+=min(abs(present-i.second),min(abs(present+k-i.second),abs(i.second+k-present)));
//         present = i.second;
//     }
//     return energy;
// }
// void parking_combinations(int out_time[],int in_time[],int n,int parking_queue[],int k,map<int,int> m,int i,int j,int present,pair<vi,int> &ans,int pre_energy){
//         if(i == n){
//             int energy = minimum_energy(parking_queue,k,present);
//             if(ans.first.empty()) {
//                 for (int i=0;i<k;i++) ans.first.push_back(parking_queue[i]);
//                 ans.second = pre_energy+energy;
//             }
//             else{
//                 if(ans.second>energy+pre_energy){
//                     for (int i=0;i<k;i++) ans.first[i] = parking_queue[i];
//                     ans.second = energy+pre_energy;                    
//                 }
//             }
//             return;
//         }
//         if(in_time[i]<out_time[j]){  
//             for(int z=0;z<k;z++){
//                 if(parking_queue[z]==-1){
//                     parking_queue[z] = m[in_time[i]];
//                     int energy=min(abs(present-z),min(abs(present+k-z),abs(z+k-present)));
//                     parking_combinations(out_time,in_time,n,parking_queue,k,m,i+1,j,z,ans,pre_energy+energy);
//                     parking_queue[z] = -1;
//                 }
//             }

//         }    
//         else if(in_time[i]>out_time[j]){
//             int energy = 0,prese=present;
//             for(int z=0;z<k;z++){
//                 if(parking_queue[z] == out_time[j]){
//                     parking_queue[z] = -1;
//                     energy =min(abs(present-z),min(abs(present+k-z),abs(z+k-present)));
//                     prese = z;
//                     break;
//                 }
//             }
//             parking_combinations(out_time,in_time,n,parking_queue,k,m,i,j+1,prese,ans,pre_energy+energy);
//             parking_queue[prese] = out_time[j];
//         }
// }
// int main(){
//     ios::sync_with_stdio(0);
//     cin.tie(0);
//     int n,k;
//     cin>>n>>k;
//     int in_time[n],out_time[n],parking_queue[k];
//     for(int i=0;i<k;i++) parking_queue[i] = -1;
//     // print(parking_queue,k);
//     map<int,int> m;
//     for(int i=0;i<n;i++) in_time[i] = input();
//     for(int i=0;i<n;i++) out_time[i] = input(),m[in_time[i]] = out_time[i];
//     sort(out_time,out_time+n);
//     sort(in_time,in_time+n);
//     pair<vi,int> ans = {{},0};
//     parking_combinations(out_time,in_time,n,parking_queue,k,m,0,0,0,ans,0);
//     print(ans.first);
//     cout<<ans.second<<endl;
//     return 0;
// }




#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> operation;

struct Result {
    //vi parking_slots;
    int energy;
    vector<operation> operations;
};

void print(int a[], int n) {
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
}

void print(vi a) {
    for (auto i : a) {
        cout << i << " ";
    }
    cout << endl;
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

int minimum_energy(int parking_queue[], int k, int present) {
    set<pair<int, int>> removing_order;
    for (int i = 0; i < k; i++) if (parking_queue[i] != -1)removing_order.insert({ parking_queue[i], i });
    int energy = 0;
    for (auto i : removing_order) {
        energy += min(abs(present - i.second), min(abs(present + k - i.second), abs(i.second + k - present)));
        present = i.second;
    }
    return energy;
}

void parking_combinations(int out_time[], int in_time[], int n, int parking_queue[], int k, map<int, int> m, int i, int j, int present, Result& ans, int pre_energy, vector<operation>& ops) {
    if (i == n) {
        int energy = minimum_energy(parking_queue, k, present);
        //if (ans.parking_slots.empty()) {
           // for (int i = 0; i < k; i++) ans.parking_slots.push_back(parking_queue[i]);
           if(ans.operations.empty()){
            ans.energy = pre_energy + energy;
            ans.operations = ops;
        } else {
            if (ans.energy > energy + pre_energy) {
               // for (int i = 0; i < k; i++) ans.parking_slots[i] = parking_queue[i];
                ans.energy = energy + pre_energy;
                ans.operations = ops;
            }
        }
        return;
    }
    if (in_time[i] < out_time[j]) {
        for (int z = 0; z < k; z++) {
            if (parking_queue[z] == -1) {
                parking_queue[z] = m[in_time[i]];
                int energy = min(abs(present - z), min(abs(present + k - z), abs(z + k - present)));
                ops.push_back({ i+1, z+1 });
                parking_combinations(out_time, in_time, n, parking_queue, k, m, i + 1, j, z, ans, pre_energy + energy, ops);
                parking_queue[z] = -1;
                ops.pop_back();
            }
        }
    } else if (in_time[i] > out_time[j]) {
        int energy = 0, prese = present;
        for (int z = 0; z < k; z++) {
            if (parking_queue[z] == out_time[j]) {
                parking_queue[z] = -1;
                energy = min(abs(present - z), min(abs(present + k - z), abs(z + k - present)));
                prese = z;
                break;
            }
        }
        parking_combinations(out_time, in_time, n, parking_queue, k, m, i, j + 1, prese, ans, pre_energy + energy, ops);
        parking_queue[prese] = out_time[j];
    }
}

int main() {
    time_t start, end;
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    int in_time[n], out_time[n], parking_queue[k];
    for (int i = 0; i < k; i++) parking_queue[i] = -1;
    map<int, int> m;
    for (int i = 0; i < n; i++) in_time[i] = input();
    for (int i = 0; i < n; i++) out_time[i] = input(), m[in_time[i]] = out_time[i];
    time(&start);
    sort(out_time, out_time + n);
    sort(in_time, in_time + n);
    Result ans;
    vector<operation> ops;
    parking_combinations(out_time, in_time, n, parking_queue, k, m, 0, 0, 0, ans, 0, ops);
    //print(ans.parking_slots);
    time(&end);
    cout << ans.energy << endl;
    for (const auto& op : ans.operations) {
        cout << "Car " << op.first << " parked in slot " << op.second << endl;
    }
        double time_taken = double(end - start);
    cout << "Time taken by program is : "<< fixed
        << time_taken << setprecision(5);
    cout << " sec " << endl;
    return 0;
}
