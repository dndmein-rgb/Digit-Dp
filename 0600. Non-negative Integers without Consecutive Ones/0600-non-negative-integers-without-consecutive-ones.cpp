class Solution {
public:
int dp[30][2][2];
int solve(string&s ,int idx,bool tight,bool prev){
    if(idx==s.length())return 1;
    if(dp[idx][tight][prev]!=-1)return dp[idx][tight][prev];
    int lb=0;
    int ub=tight?s[idx]-'0':1;

    int res=0;
    for(int dig=lb;dig<=ub;dig++){
        if(dig==1 && prev)continue;
    res+=solve(s,idx+1,(tight && dig==ub),dig==1);
    }
    return dp[idx][tight][prev]=res;
}
    int findIntegers(int n) {
        string s=bitset<32>(n).to_string();
        memset(dp,-1,sizeof(dp));
        int first_idx_of_1=s.find('1');
        s=s.substr(first_idx_of_1);
        return solve(s,0,1,0);
    }
};
