// In this case, I am assuming that All cars will arrive before any car, starts leaving.
// Algorithm used: Greedy approx algorithm
// My idea is that, we will insert the cars according to their departure time, so that we can depart each car in a continuous rotation.

// README:
/*
    Input Format:
        n - No. of slots
        k - No. of cars
        Arrival times of each k car - Ex: [08:15,09:00]
        Departure times of each k car - Ex: [22:00 , 21:00]

    Output Format:
        order of cars placed: Ex-[1700,1600,1550,1900], these are according to their departure times,we will keep cars in the order which departs at 17:00, next which departs at 16:00, like that, (A/s to example)
        Total Energy for the process.

    Time complexity: O(nlog(n))
*/

#include<bits/stdc++.h>
using namespace std;

// We will be using this function to sort according to departure times.
static bool compare(pair<int,int> a, const pair<int,int> b)
{
    return a.second < b.second;  
}

// This is the function where we are calculating the order and minimum of total_rotations approximately.
pair<vector<int>,int> calculate(int n, int k,vector<int>& arrival,vector<int>& departure)
{   
    vector<pair<int,int>> small;        // Here my idea is that, we are giving normal indexes based on the arrival times. Like if arrival times are {5,8,4,2,3} -> {4,5,3,1,2}. We are just going on taking permutations to represent lowest numbers in order.
                                        // Lowest number - 1, 2nd lowest number - 2, 3rd lowest number - 3, like that.
    for(int i=0;i<k;i++)
    {
        small.push_back(make_pair(arrival[i],i+1));     // Ignore this small vector, this is just for modifications between arrival and arrival2.
    }
    sort(small.begin(),small.end());

    vector<int> arrival2(k);
    for(int i=0;i<k;i++)
    {
        arrival2[small[i].second - 1] = (i+1);       // This arrival2 is the permutation, as mentioned in above comments.
    }    

    vector<pair<int,int>> v;
    for(int i=0;i<k;i++)
    {
        v.push_back(make_pair(arrival2[i],departure[i]));          // Took arrival_permuation and departure time of car as pair 
    }

    sort(v.begin(),v.end(),compare);       // Sort according to departure times, compare function given above.

    vector<int> arr(n,-1); // This vector is for order where the car is inserted. (Based on departure times).

    int total_rotations = 0; 
    int curr = 0; // current position
    int prev = 0; // previous position from which we left

    for(int i=0;i<k;i++)
    {
        prev = curr;
        curr = v[i].first - 1;
        arr[i] = v[i].second;
        
        total_rotations += min(abs(curr-prev), n-abs(curr-prev));   // (if min = abs(curr-prev) -> move clockwise else -> move anticlockwise or vice-versa, like that) .    
    }

    if(v[0].first - 1 != 0)   // For the first car, we do not need to rotate, as we are rotating for the 1st car above, we remove that. Like if car 3(based on departure arrives first), according to code, we are moving 2 times and keeping it there, but we can keep directly on the down one, without rotating, that's why this if statement.
    {                               
        total_rotations -= min(v[0].first-1,n-(v[0].first - 1));
    }

    int g = min(abs(n-curr),curr);   // This is for coming to our 0th index position since,departure starts from here. As we kept 1st-departing car on 0th index one.

    total_rotations += (g+n-1);   // (n-1) rotations for departure of all cars. Since all cars are in order.

    return {arr,total_rotations};
}

// This function is just for converting given string into integers like 08:15 to 0815.
int convert(string& clockTime) {
    
    string timeWithoutColon = clockTime;
    timeWithoutColon.erase(remove(timeWithoutColon.begin(), timeWithoutColon.end(), ':'), timeWithoutColon.end());

    int integerTime;
    istringstream(timeWithoutColon) >> integerTime;

    return integerTime;
}

int main()
{
    int n;  // No of parking slots
    cin>>n;

    int k;   // No. of cars arrived
    cin>>k;

    swap(n,k);

    vector<int> arrival;
    vector<int> departure;
    map<int,int> mapping;
    for(int i=0;i<k;i++)
    {
        string come;                  // Arrival times as a string like 08:30
        cin>>come;

        int income = convert(come);

        arrival.push_back(income);     // Arrival times of cars, like an integers.
    }

    for(int i=0;i<k;i++)
    {
        string come;                 // Departure times as a string like 22:00.
        cin>>come;
        
        int outgo = convert(come);

        departure.push_back(outgo);    // Departure times of cars, like an integers.
    }

    for(int i =0 ;i<k;i++){
        mapping[departure[i]] = arrival[i];
    }

    pair<vector<int>,int> p = calculate(n,k,arrival,departure);

    for(int i=n-1;i>=0;i--)
    {
        cout<<mapping[p.first[i]]<<" ";   // This gives the order of cars placed according to their departure times. (-1 indicates slot empty) 
    }
    cout<<endl;

    cout<<p.second<<endl;

    // Finally, we will get the order of parking of cars, and the total-energy needed for the machines
    // We assumed, each energy required for each rotation is 1 unit.

}