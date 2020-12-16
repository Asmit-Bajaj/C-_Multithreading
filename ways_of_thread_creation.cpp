/*There are 5 ways to create thread in c++
 * 1. using function pointer
 * 2. using lambda expression
 * 3. using non static function of class
 * 4. using static function of class
 * 5. using functor
 */

#include<iostream>
#include<thread>
using namespace std;
typedef unsigned long long int ull;
//using function pointer
//calculating sum  till values
ull sum = 0;
ull evenSum = 0;
ull oddSum = 0;
void findSum(ull value){
	for(ull i=1;i<=value;i++){
		sum+=i;

	}

}

class Base{
	public :
		void findEvenSum(ull);
		static void findOddSum(ull);
		void operator()(ull);
};

//using non static function
////calculating even sum uptil given value
void Base :: findEvenSum(ull value){
	for(ull i=0;i<=value;i+=2){
		evenSum+=i;
	}

}

ull fiveSum=0;
void Base::operator ()(ull value){
	for(ull i=0;i<=value;i+=5){
		fiveSum+=value;

	}
}

//using static function
//calculating the odd sum
void Base::findOddSum(ull value){
	for(ull i=1;i<=value;i+=2){
		oddSum+=i;
	}
}
ull tripleSum = 0;
int main(){
	//creating thread
	ull value = 900000000;
	Base b;
	std::thread t1(findSum,value);
	std::thread t2(&Base::findEvenSum,&b,value);
	std::thread t3(&Base::findOddSum,value);
	//using lambda expression
	auto func = [](ull val){
		for(ull i = 0;i<=val;i+=3){
			tripleSum+=i;
		}
	};

	std::thread t4(func,value);
	//using functor
	std::thread t5((Base()),value);

	cout<<endl<<endl<<"All Threads Started "<<endl<<endl;
	t1.join();
	t2.join();

	t3.join();
	t4.join();
	t5.join();

	cout<<"Sum : "<<sum<<endl;
	cout<<"Even Sum : "<<evenSum<<endl;
	cout<<"Odd Sum : "<<oddSum<<endl;
	cout<<"Triplet Sum : "<<tripleSum<<endl;
	cout<<"Five Sum : "<<fiveSum<<endl<<endl;	

	return 0;

	return 0;
}

