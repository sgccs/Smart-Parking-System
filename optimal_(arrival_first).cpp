#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
void print(int a[],int n){
    for(int i=0;i<n;i++){
        cout<<a[i]<<" ";
    }
    cout<<endl;
}
void print(vi a){
    for(auto i : a){
        cout<<i<<" ";
    }
    cout<<endl;
}
int input(){
        string s;
        cin>>s;
        int ans=0;
        for(auto i :s){
            if(i!=':'){
                ans*=10;
                ans+=int(i)-int('0');
            }
        }
        return ans;
}
void input_processing(int in_time[],int out_time[],int n,map<int,int> m){
    int j=0;
    for(auto i : m){
        in_time[j] = i.first;
        out_time[j] = i.second;
        j++;
    }
}
int minimum_energy(int parking_queue[],int k,int present){
    set<pair<int,int>> removing_order;
    for(int i=0;i<k;i++) if(parking_queue[i]!=-1)removing_order.insert({parking_queue[i],i});
    int energy = 0;
    for(auto i : removing_order){
        energy+=min(abs(present-i.second),min(abs(present+k-i.second),abs(i.second+k-present)));
        present = i.second;
    }
    return energy;
}
void parking_combinations(int out_time[],int n,int parking_queue[],int k,int l,int r,int i,int present,pair<vi,int> &ans,int pre_energy){
        if(i == n){
            int energy = minimum_energy(parking_queue,k,present);
            if(ans.first.empty()) {
                for (int i=0;i<k;i++) ans.first.push_back(parking_queue[i]);
                ans.second = pre_energy+energy;
            }
            else{
                if(ans.second>energy+pre_energy){
                    for (int i=0;i<k;i++) ans.first[i] = parking_queue[i];
                    ans.second = energy+pre_energy;                    
                }
            }
            return;
        }
        parking_queue[l] = out_time[i];
        int energy = min(abs(present-l),min(abs(present+k-l),abs(l+k-present)));
        parking_combinations(out_time,n,parking_queue,k,l-1,r,i+1,l%k,ans,pre_energy+energy);
        parking_queue[l] = -1;
        parking_queue[r%k] = out_time[i];
        energy = min(abs(present-r+k),min(abs(present+k-r+k),abs(r-present)));
        parking_combinations(out_time,n,parking_queue,k,l,r+1,i+1,r%k,ans,pre_energy+energy);
        parking_queue[r%k] = -1;       
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,k;
    cin>>n>>k;
    int in_time[n],out_time[n],parking_queue[k];
    for(int i=0;i<k;i++) parking_queue[i] = -1;
    map<int,int> m;
    for(int i=0;i<n;i++) in_time[i] = input();
    for(int i=0;i<n;i++) out_time[i] = input(),m[in_time[i]] = out_time[i];
    input_processing(in_time,out_time,n,m);
    pair<vi,int> ans = {{},0};
    parking_combinations(out_time,n,parking_queue,k,k-1,k,0,k-1,ans,0);
    print(ans.first);
    cout<<ans.second<<endl;
    return 0;
}