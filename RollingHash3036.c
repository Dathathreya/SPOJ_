#define M ((int)1e6+1)
#define mod ((int)1e9+9)
char pat[M],text[M];
int modmul(int a,int b){
    a = (1ll*a*b)%mod;
    return a; 
}
int modadd(int a,int b){
    a += b;
    if(a>=mod) a -= mod;
    if(a<0) a+=mod;
    return a; 
}
int countMatchingSubarrays(int* nums, int numsSize, int* pattern, int patternSize) {
    // 1 - a , 0 - b , -1 - c
    int n = numsSize,m=patternSize,count=0,pat_hs=0,width=0,pow=1,pr=37,text_hs=0;
    memset(text,'\0',sizeof(text));memset(pat,'\0',sizeof(pat));
    for(int i=0;i<=n-2;i++){
        text[i] = (nums[i]==nums[i+1])?('b'):((nums[i]<nums[i+1])?('a'):('c'));
    }
    for(int i=0;i<=m-1;i++){
        pat[i] = (pattern[i]==0)?('b'):((pattern[i]==1)?('a'):('c'));
    }
    width = 0;
    int end = 0;
    while(width<m){ // once
                    pat_hs = modadd(modmul(pat_hs,pr),(pat[end++]-'a'+1)*1);
                    pow = modmul(pow,pr);
                    width++;
    }
    pow = 1,width = 0,end = 0;
    for(;end<n;){
           if(width<m)
            {
                while(width<m){ // once
                    text_hs = modadd(modmul(text_hs,pr),(text[end++]-'a'+1)*1);
                    if(width<(m-1))
                     pow = modmul(pow,pr);
                    width++;
                }
                //printf("%d ",pow);    
                if(text_hs==pat_hs) count++;
            }
            else{
                // width == m
                text_hs = modadd(text_hs,-modmul(text[end-m]-'a'+1,pow)); // 4321 -> _321   // remove at front FIFO
                text_hs = modadd(modmul(text_hs,pr),(text[end++]-'a'+1)*1); // _321 -> 432_ , 4321 add at end  FIFO
                if(text_hs==pat_hs) count++;
            }       
    }
    return count;
}
