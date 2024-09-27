#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define M 300005
#define mod 998244353
int prevcnt[M],currcnt[M],sumMod[M];


int modadd(int a,int b){
	a += b;
	if(a>=mod){
		a -= mod;
	}
	return a;
}

void solve(){
	int n,k,start=0;
	assert(fscanf(stdin,"%d %d",&n,&k)>0);
	// from origin we make a move to a number with a step of any num divisible by (k+i) each time i increases by 1 value 
	// brute force approach - to enumerate all list of multiples of (k+i) (expensive) which need to be 
	// added count for  each numbers  which we got from prev iter to get current count 
	// for that number initially 0 is achievable  o(curr*multiples*list_of_numbers) - worsttimeC


	// contribution dp method 
	// we have 2 arrays to save count of prev and current of a number at index i-1 and i 
	// sumMod to have count of numbers leaving same reminder as current number from previous layer 
	// we need to maintain this count because we can construct  current number by putting multiples of (K+S) to 
	// list of numbers leaving same reminder as current number
	
	// Example 
	// important property of reminder i ~= (j)%(k+s)
	// ~= means equivalence 
	// n 						= 3, 10, 17, 24, 31, 38, 45, 52, 59, 66 
	// 							  (count of smaller numbers will be saved in prevcnt less than bigger)
	// k+s 						= 7 
	//							= 3+7*10,10+9*7,17+8*7,24+7*7,31+6*7,38+5*7,45+4*7,52+3*7,59+2*7,66+1*7
	// target_current_number	= 66+7 = 73	(bigger) this should be upto n atmost
	// leaving same reminder part is found out using sumMod

	// 0 - k - k+(k+1) - k+(k+1)+(k+2) - k+(k+1)+(k+2)+(k+3) -- sequence of starting numbers in this problem
	memset(prevcnt,0,sizeof(prevcnt));memset(currcnt,0,sizeof(currcnt));
	memset(sumMod,0,sizeof(sumMod));	
	prevcnt[0] = 1; // count of 0's at start is 1
	for(start=0;start+k<=n;){
		memset(sumMod,0,sizeof(sumMod));	
		for(int target=start;target<=n;++target){
			int count_of_nums_reaching_target = prevcnt[target];
			prevcnt[target] = sumMod[target%k]; // list of previous smaller numbers leaving same reminder 
			
			sumMod[target%k] = modadd(sumMod[target%k],count_of_nums_reaching_target); // consider current as it leaves same reminder 
			currcnt[target] = modadd(currcnt[target],prevcnt[target]);
		}
		start += (k++);
	}
	for(int each=1;each<=n;each++){
		printf("%d ",currcnt[each]);
	}
	putchar('\n');
}

int main(int  argc,char* argv[]){
	int tt=1;
	// assert(fscanf(stdin,"%d",&tt)>0);
	while(tt--){
		solve();
	}
}

//D. Chip Move

// There is a chip on the coordinate line. Initially, the chip is located at the point 0 . You can perform any number of moves; each move increases the coordinate of the chip by some positive integer (which is called the length of the move). The length of the first move you make should be divisible by k , the length of the second move — by k+1 , the third — by k+2 , and so on.
// For example, if k=2 , then the sequence of moves may look like this: 0→4→7→19→44 , because 4−0=4 is divisible by 2=k , 7−4=3 is divisible by 3=k+1 , 19−7=12 is divisible by 4=k+2 , 44−19=25 is divisible by 5=k+3 .

// You are given two positive integers n and k. Your task is to count the number of ways to reach the point x, starting from 0 , for every x∈[1,n] . The number of ways can be very large, so print it modulo 998244353 . Two ways are considered different if they differ as sets of visited positions.
// Input
// The first (and only) line of the input contains two integers n and k (1≤k≤n≤2⋅105).

// Output
// Print n integers — the number of ways to reach the point x , starting from 0 , for every x∈[1,n] , taken modulo 998244353.

// time limit per test2 seconds
// memory limit per test256 megabytes
// https://leetcode.com/problems/house-robber-iii/?envType=problem-list-v2&envId=dynamic-programming
