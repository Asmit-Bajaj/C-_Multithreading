#include<bits/stdc++.h>
#include<fstream>
#include<dirent.h>
#include<sys/types.h>
#include<string>
#include<future>

using namespace std;

struct my_file{
	string name;
	vector<string>content;
		pair<int,pair<int,int> > length;
		int similarWords;

	};

	vector<struct my_file*>files;

//read the content
vector<string> readContent(string str){
	cout<<"Thread id : "<<std::this_thread::get_id()<<endl;
	str = "../thread_task/"+str;
        char *name = &str[0];
	ifstream fin;
	string line;
        fin.open(name);
	vector<string>content;
	//read the content
        while(getline(fin,line)){
		content.push_back(line);
        }
	return content;
}

//count the length of file
pair<int,pair<int,int> > getLength(vector<string>content){
	cout<<"Thread id : "<<std::this_thread::get_id()<<endl;
	int words = 0;
	int character = 0;
	int line = 0;
	string temp = "";
	string temp1 = "";

	for(int i=0;i<content.size();i++){
		temp = content[i];
		line++;
		temp1 = "";
		//seperate the words and count it
		for(int j=0;j<temp.size();j++){	
			character++;
			if(temp[j] != ' '){
				temp1 = temp1+temp[j];
			}else{
				words++;
				temp1 = "";
			} 
		} 
		if(temp1 != ""){
			words++;
		}
	}
	pair<int,pair<int,int> > ans;
	ans.first = line;
	ans.second.first = words;
	ans.second.second = character;
	return ans;
}

//checking for similar words
int getSimilarWords(vector<string>content){
	cout<<"Thread id : "<<std::this_thread::get_id()<<endl;
	map<string,int>m;
	string temp;
	string temp1;
	int count = 0;

//read the content lines and check for similar words
	for(int i=0;i<content.size();i++){
		temp = content[i];
		temp1 = "";
		for(int j=0;j<temp.size();j++){
			if(temp[j] != ' '){
				temp1 = temp1+temp[j];
			}else{
				if(m.find(temp1) == m.end()){
					m[temp1] = 1;
				}else{
					m[temp1]++;
				}	
			temp1 = "";
			}
		}

		if(temp1 != ""){
			if(m.find(temp1) == m.end()){
                                        m[temp1] = 1;
                                }else{
                                        m[temp1]++;
                                }

		}
	}
	
	for(auto itr = m.begin();itr!=m.end();itr++){
		if(itr->second > 1)
			count++;
	}
	return count;
}

//stores the name of files 
void storeName(){

                DIR *dr;
                struct my_file *temp;
                struct dirent *en;
                string line;
                dr = opendir("../thread_task");
                cout<<"\n";
                if(dr){
                        while((en = readdir(dr)) != NULL){
                                string str = en->d_name;
                                if(str != ".." && str != "." && str != ""){

                                        temp = new struct my_file();
                                        temp->name = str;

                                        std::future<vector<string> > readCont = std::async(std::launch::async,readContent,str);
                                        temp->content = readCont.get();


                                std::future<pair<int,pair<int,int> > > getLth = std::async(std::launch::async,getLength,temp->content);

                                 std::future<int> getSm = std::async(std::launch::async,getSimilarWords,temp->content);

                                temp->length = getLth.get();
                                temp->similarWords = getSm.get();
                                files.push_back(temp);
                        }

                }

                closedir(dr);
        }else{

        }
}



int main(){
	cout<<"\nStarted Reading the files \n";

	thread t1(storeName);
	cout<<"Please Wait ..... \n";
	t1.join();

	cout<<"\nsuccesfully read the files The result is : \n\n";

	if(files.size() == 0){
		cout<<"No Files Found\n\n";
	}else{
		for(int i=0;i<files.size();i++){
			cout<<"File Name : "<<files[i]->name<<"\n";
			cout<<"File Content : \n";
		
			for(int j=0;j<files[i]->content.size();j++){
				cout<<files[i]->content[j]<<"\n";

			}
			cout<<"No of Lines : "<<files[i]->length.first<<"\n";
			cout<<"No of words : "<<files[i]->length.second.first<<"\n";
			cout<<"No Of Characters : "<<files[i]->length.second.second<<"\n";

			cout<<"No of Similar Words : "<<files[i]->similarWords<<"\n";

		}
		cout<<"\n\n";

	}
	cout<<"\n\n";
	return 0;

}