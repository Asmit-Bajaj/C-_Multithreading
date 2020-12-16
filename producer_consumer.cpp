/*this program demonstrates the producer consumer problem
 * here the producer makes the product and then consumer consumes it
 *But we need to ensure that the consumer consumes the product when the product is ready
 *both the opertions need to be conducted simultaneously with the help of threads
 */

#include<iostream>
#include<thread>
#include<queue>
#include<mutex>
#include<condition_variable>

std::mutex m;
std::condition_variable cv;

using namespace std;
//queue is for storing the products
queue<int>q;
int maxSize = 10;
int flag = 0;
//here the producer will make the product uptil the queue is full
//here we had defined value as max size of queue that is produce can produce maximum size products
//we will keep keep track whether the size of queue is not more than size
//then producer will wait until the consumer consumes one product 
void producer(int val){
	int no=1;

	while(val){
	//the producer will lock the mutex
		std::unique_lock<mutex>lock(m);
		//now we will check whether we have space in queue or not
		cv.wait(lock,[](){
			return q.size() < maxSize;
		});
		q.push(no);
		cout<<endl<<"Producer made the product : "<<no<<endl;
		no++;
		val--;
		//producer add the product now 
		lock.unlock();
		cv.notify_one();
	}
	flag = 1;
	cv.notify_one();
}

//now consumer will consume the product
//we will check whether product is availabel for use or not
//if queue is empty it means that the no product is made
//so we will put the thread to sleep
//then when product is available consume it

void consumer(){
	while(1){
		std::unique_lock<mutex>ul(m);

		cv.wait(ul,[](){
			return q.size() > 0 || flag == 1;
		});
		if(flag == 1 && q.size() == 0)
			break;
		cout<<"Consumer Consumed : "<<q.front()<<endl;
		q.pop();
		ul.unlock();
		cv.notify_one();
	}
}

int main(){
	cout<<endl<<endl<<"Producer Consumer Problem "<<endl<<endl;
	std::thread t1(producer,20);
	std::thread t2(consumer);

	t1.join();
	t2.join();
	return 0;

} 