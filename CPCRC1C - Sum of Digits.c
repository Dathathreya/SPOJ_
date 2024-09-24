#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

#define SZ 1<<21
#define M  ((int)3e5+1)
#define mod ((int)1e9+7)
typedef unsigned long long lli;
lli prec[18][2]; char str[M],stdIn[M]; // 0 equal to 0 , 1 - more than 0

lli modadd(lli a,lli b){
    a += b;
    return a;
}

void digit_dp_init(){
	lli expon = 1;
    memset(prec,0,sizeof(prec));
	for(int i=0;i<=17;i++){
	        // precompute number of 1's or any single digit from 0 to 99, 0 to 999 , 0 to 99999... under modulus 
	        prec[i+1][1] = (1llu*(i+1)*expon);
	        expon = (1ll*expon*10);
	        if(i>=2){
	        	prec[i][0] = (1llu*9*prec[i-1][1]);
	        	prec[i][0] = modadd(prec[i][0],prec[i-1][0]);
	        }
	}
	return;
}

lli countDigit(lli n,int digit) {
    int where=0; lli prefixDigit=0,ans=0;
    sprintf(str,"%llu",n);
    n = strlen(str);
    if(digit==0) ans = modadd(ans,prec[n-1][0]);
    for(int where=0;where<n;where++){
        int currDigit = str[where] - '0';
        // for each digit with a prefix part , its corresponding suffix repeats D number of times if curr is tight digit 
        // from 0 to D-1 with considering prefix part as coming before this number formed.
        // so numbers formed by suffxi part counts and repeats itself for D times 
        lli rem = (1llu*(currDigit-((where==0)&&(digit==0)))*prec[n-1-where][1]);
        //printf("%d %d %d\n",rem,prefixDigit,ans);
        ans = modadd(ans,rem);
        if((where==0)&&(digit==0)){
        	continue;
        }
        if(currDigit>0)
        {
            // same logic as above if currentDigit is more than 1 , suffix part repeats 1 time 
            // prefixPart having d digit in it counted will repeat d times from 0 to d-1 // part2 
            // above part2 is right shifted by powers of 10 so we need to multiply by 10^(n-curr)
            lli c1 = (currDigit>digit)+(1llu*prefixDigit*currDigit);
            rem = (1llu*(c1)*(prec[n-where][1]/(n-where))); // precompute powers of 10 ?                   
            ans = modadd(ans,rem);
            
        }
        // else its tight cant take    
        // last number formed considering everything is tight so we can take its count directly without any suffix
        prefixDigit += (currDigit==digit);
      //  printf("(%d %d)\n",rem,prefixDigit);
        
    }
    ans = modadd(ans,prefixDigit);
  //  printf("answer:%d ",ans);
    return ans; 
}

void querycountDigit(lli n,const void* mem1,bool sign){
	lli* mem = (lli*)mem1;
	for(int i=0;i<=9;i++){
		mem[2*i+sign] = countDigit(n,i);
	}
	return;
}

void solve(){
	//digit_dp_init();
	//while(true){
		fgets(stdIn,sizeof(stdIn),stdin);
		lli start,end;
		sscanf(stdIn,"%llu %llu",&start,&end);
		lli mem[10][2];
		memset(mem,0,sizeof(mem));
		if(start>end){
			lli t = start;
			start = end;
			end = t;
		}
		if((start==-1)&&(end==-1)){
			return;//break;
		}
		if((start==0)&&(end==0)){
			printf("0\n");return;
		}
		if(start<=1){
			 querycountDigit(end,mem,true);
		}
		else{
			querycountDigit(end,mem,true);
			querycountDigit(start-1,mem,false);
		}
		// 67500000000000001
		lli count = 0;
		for(int i=0;i<=9;i++){
			count += (1llu*i*(mem[i][true]-mem[i][false]));
		}
		printf("%llu",count);
		putchar('\n');
	//}
}

int main(int argc,char* argv[]){
	 digit_dp_init();
	int tt=1;
	fgets(stdIn,sizeof(stdIn),stdin);
	sscanf(stdIn,"%d",&tt);
	while(tt--){
		solve();
	}
}

//https://www.spoj.com/problems/MDIGITS/
//https://www.codechef.com/problems/ENCODING
//https://cses.fi/problemset/task/2220

// 1845294337
// 40500000001
