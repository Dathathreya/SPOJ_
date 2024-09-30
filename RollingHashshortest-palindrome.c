int mod=1000000007;
char ans_s[60005];
int modadd(int a,int b){
    a+=b;
    if(a>=mod) a-=mod;
    return a;
}
int modmul(int a,int b){
    a = (1ll*a*b)%mod;
    return a;
}
char* shortestPalindrome(char* s) {
   int n = strlen(s),i=0,pr = 31,pref = 0,suff=0,pow=1,mx=-1;
   for(i=0;i<n;i++){
        if(i==0){
            pref = (s[i]-'a'+1)*pow;
            suff = (s[i]-'a'+1)*pow; 
        }
        else{
            // shwttwrtwr
            // 1234567 - pref 
            // 7654321 - suff
            pref = modadd(pref,modmul((s[i]-'a'+1),pow));
            suff = modadd(s[i]-'a'+1,modmul(suff,pr)); // 1 = (pr)^0
        }
        if(suff==pref) {
            mx = i;
        }
        pow = modmul(pow,pr);
   }
   memset(ans_s,'\0',sizeof(ans_s));
   // from ending till just after end of that perfect palindrome take everything
   for(i=n-1;i>=(mx+1);i--){
        ans_s[n-1-i] = s[i];
   }
   int nlen  = strlen(ans_s);
   // take entire string
   for(i=0;i<n;i++){
        ans_s[i+nlen] = s[i];
   }
   return ans_s;
}
