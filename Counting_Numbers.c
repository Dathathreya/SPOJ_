#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SZ 1<<21
#define M  ((int)3e5+1)
#define mod ((int)1e9+7)
typedef unsigned long long llu;
llu prec[10],temp[10]; char str[M]; 


llu queryNoAdjDigit(llu n,bool sign){
	llu answer = 0;
	short prefixPart = 0; bool carried = true;
	sprintf(str,"%llu",n);
	int sz = strlen(str);
	memset(prec,0,sizeof(prec));
	for(int where=0;where<sz;where++)
	{
		short currDigit = str[where] - '0';
		memset(temp,0,sizeof(temp));
		llu prev=0;
		if(where>0){
			for(short digit=0;digit<=9;digit++){
				prev += prec[digit];
			}	
		}
		for(short digit=0;digit<=9;digit++){
			if(where==0)
			{
				if(currDigit>digit){
					if(digit>0)
						{temp[digit] = 1;}
				}			
				else{
					break;
				}
			}
			else{
				// current can be mapped to all previous part ending with any digit which doesnt have same value 
				temp[digit] += (prev-prec[digit]);
				// each non-zero digit can start from itself 
				if(digit>0)
					temp[digit] += 1;
				// link prefixtightdigit with current number
				if((currDigit>digit)&&(carried)){
					bool holds = (prefixPart!=digit);
					if(holds){
						temp[digit] += 1; 
					}
				}
			}		
		}
		carried &= (currDigit!=prefixPart);
		prefixPart = currDigit;
		memcpy(prec,temp,sizeof(temp));
	}
	for(short digit=0;digit<=9;digit++){
		answer += prec[digit]; // sum of all digits at last index
	}
	answer += carried;
	return answer;
}

void solve(){
	llu a,b; 
	assert(scanf("%llu %llu",&a,&b)>0);
	llu start = (a>10)?(queryNoAdjDigit(a-1,false)):(a-1);
	llu end   = (b>10)?(queryNoAdjDigit(b,true)):(b);
	printf("%llu",end-start);
}

int main(int argc,char* argv[]){
	int tt=1;
	// assert(fscanf(stdin,"%d",&tt)>0);
	while(tt--){
		solve();
	}
}
