/*mutex is used to avoid race condition
 *in thread
 *
 */
#include<iostream>
#include<thread>
#include<mutex>
#include<chrono>
using namespace std::chrono;
using namespace std;
int amt = 0;
int amt2 = 0;
std::mutex m;

//increasing amt by two threads
//without mutex the value of amt can be 1 even though it should be 2
//using mutex it will always be 2
//one thread will acquire the lock and other thread will wait till the thread-1 release the lock
void incAmt(int i){
	m.lock();
	amt++;
	cout<<"Thread - "<<i<<" locked it "<<endl;	
	 std::this_thread::sleep_for(std::chrono::seconds(2));
	m.unlock();
	cout<<"Thread - "<<i<<" executed it "<<endl;
}

//using try lock 
//here one thread will check it will be able to to lock the mutex or not if not then proceed further

void incAmt2(int i){
	if(m.try_lock()){
		cout<<"Thread - "<<i<<" acquire the lock and inc the amount"<<endl;
		amt2++;
		std::this_thread::sleep_for(std::chrono::seconds(2));
		m.unlock();
		return;
	}

	cout<<"Thread - "<<i<<" didnot get the chance to acquire lock "<<endl;
}
int main(){

	std::thread t1(incAmt,1);
	std::thread t2(incAmt,2);
	t1.join();
	t2.join();

	std::thread t3(incAmt2,1);
	std::thread t4(incAmt2,2);
	t3.join();
	t4.join();

	cout<<"Amount : "<<amt<<endl;
	cout<<"Amount - 2 : "<<amt2<<endl;
 
	return 0;
}