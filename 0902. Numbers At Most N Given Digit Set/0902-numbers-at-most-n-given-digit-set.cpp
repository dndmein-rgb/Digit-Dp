class Solution {
public:
int dp[10][2][2];
int f(string& s,int idx,bool  tight,bool lz,int mask){
    if(idx==s.length())return 1;
    if(dp[idx][tight][lz]!=-1)return dp[idx][tight][lz];
    int lb=0;
    int ub=tight?s[idx]-'0':9;
    int res=0;
    for(int dig=lb;dig<=ub;dig++){
        if(lz && dig==0)res+=f(s,idx+1,0,1,mask);
        else {
            if(!(1&(mask>>dig)))continue;
            res+=f(s,idx+1,(tight && dig==ub),0,mask);
        }
        
    }
    return dp[idx][tight][lz]=res;
    }

    int atMostNGivenDigitSet(vector<string>& digits, int n) {
        int mask=0;
        memset(dp,-1,sizeof(dp));
        for(auto& c:digits)mask|=(1<<stoi(c));
        string s=to_string(n);
        return f(s,0,1,1,mask)-1;
    }
};
