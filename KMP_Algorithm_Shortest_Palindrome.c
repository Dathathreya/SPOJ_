char rev_s[69005];int pos_begin[50005];
//https://leetcode.com/problems/shortest-palindrome/
void kmpPrefixFunc(char* pattern){
    int n = strlen(pattern),i=0,j=0;
    pos_begin[0] = 0;
    for(i=1;i<n;){
          while((j>0)&&(pattern[i]!=pattern[j]))  {
               j = pos_begin[j-1];        
          }
          if((j>=0)&&(pattern[i]==pattern[j])){ pos_begin[i++] = ++j; }  
          else {pos_begin[i++] = 0;j=0;}  
    }
}
char* shortestPalindrome(char* s) {
   int i=0,n=strlen(s),j=0;
   memset(pos_begin,0,sizeof(pos_begin));
   for(i=0;i<n;i++){
    rev_s[n-i-1] = s[i];
   }
   rev_s[n]='\0';
   j=0;
   kmpPrefixFunc(s);
   int last = 0;
   for(i=0;i<n;){
          while((j>0)&&(s[j]!=rev_s[i]))  {
               j = pos_begin[j-1];        
          }
          if((j>=0)&&(rev_s[i]==s[j])){ 
           if(i==(n-1)) last=j;
          i++;j++; }  
          else {j=0;i++;}  
   }
   memset(rev_s,'\0',sizeof(rev_s));
   for(i=n-1;(i>=(last+1));i--){
            rev_s[n-1-i] = s[i];
   }
   int nlen = strlen(rev_s);
   for(i=0;i<n;i++){
            rev_s[i+nlen] = s[i];
   }
   return rev_s;
}
