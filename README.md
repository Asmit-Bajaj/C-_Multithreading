--> task.cpp :
 Here I had performed a task where a one thread is reading the file names from a directory using storeName() method, second thread is reading the content of the file using readContent() method
 ,third thread is finding the no of word count using getLength() method and fourth thread is finding the count of repeated words in the file using getSimilarWords() method
 
 For This I had used async method with async launch policies and concept of 'promise and future'. launch::async makes sure that a new thread or older thread is used for performing
 the functionalities so that multiple threads can run at a time.
 
 We Can read any number of files from the directory as I Had Used a vector of structures for storing all the information
 
 -->Producer_consumer.cpp : 
 Here I had simulated the producer consumer problem using mutex and threads 
 Here The Producer makes a product using producer() method and while doing this acquires the lock over mutex so that consumer cannot consume product util their is atleast one    product was made by producer
 Consumer consumes the product using consumer() method. The Consumer gets notified by the producer when the product is ready by using notify_one() method of condition_variable
 
 
 --In Other Cpp files I had demonstrated How Threads are created and mutex is used
 
