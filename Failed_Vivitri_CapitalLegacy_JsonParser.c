#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

typedef long long int lli;
typedef unsigned long long  llu;

typedef struct primitive{
	short _short;
	int _int;
	llu _ullong;
	lli _llong;
	long double _ldouble;
	char* _string;
	char _ch;
}_pdata_type;

typedef struct json_type {
	// tagged union
	short identifier; // for detecting datatype of value
	char* key_name;	
	typedef union _value{
		short _short;
		int _int;
		llu _ullong;
		lli _llong;
		long double _ldouble;
		char* _string;
		char _ch;
		short* _lshort;
		int* _lint;
		llu* _lullong;
		lli* _lllong;
		long double* _lldouble;
		char** _lstring;
		struct json_type* _lobj;

	}_value;
}json;


// vivitri capital - json parser and queries to get value for json path org.division.team.emp_details.name for ex. 

void solve(){
	// use recursion ?
	//printf("%s ",s);	
}

int main(){
	int tt=1;
	// assert(fscanf(stdin,"%d",&tt)>0);
	while(tt--){
		solve();
	}
}

// organiz.division.PU_unit.region.team.employee_name

// Longest common subsequence ?
