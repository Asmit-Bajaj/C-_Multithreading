#include<iostream>
#include<thread>
#include<chrono>
#include<ctime>
#include<ratio>
using namespace std::chrono;

using namespace std;
typedef unsigned long long int ull;

ull es = 0;
ull os = 0;

//calculating the even sum
void evenSum(ull val){
	for(int i=2;i<=val;i+=2){
		es+=i;
	}
}

//calculating the odd sum
void oddSum(ull val){
        for(ull i=1;i<=val;i+=2){
                os+=i;
        }
}

int main(){
	auto start = high_resolution_clock::now();
	thread t1(evenSum,900000000);
	thread t2(oddSum,900000000);

	t1.join();
	t2.join();
	auto end = high_resolution_clock::now();
	//calculating the duration with thread
	auto duration = duration_cast<microseconds>(end-start);


	cout<<"\nevenSum : "<<es<<"\n";
	cout<<"\nodd Sum : "<<os<<"\n";
	cout<<"\n duration in sec with thread : "<<duration.count()/1000000<<"\n";

	es = os = 0;
	//without using thread
	start =  high_resolution_clock::now();
	evenSum(900000000);
	oddSum(900000000);

	end =  high_resolution_clock::now();

	duration = duration_cast<microseconds>(end-start);
	cout<<"\n";
	cout<<"\nevenSum : "<<es<<"\n";
        cout<<"\nodd Sum : "<<os<<"\n";
        cout<<"\n duration in sec without thread : "<<duration.count()/1000000<<"\n";
	cout<<"\n";
	return 0;
}

