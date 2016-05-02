#include <iostream>
#include "awsv4.hpp"
#include <future>
#include <vector>


int main(int argc, char** argv) {

  std::vector<std::future<std::string>> futures;
  std::vector<double> start_times;
  std::vector<double> end_times;
  AWSV4::RequestParams req_params = AWSV4::get_request_params();
  for(int i = 0; i < 100; ++i) {
        futures.push_back(std::async(std::launch::async,AWSV4::invoke_request,req_params));
   }
  for(auto &e : futures) {

	
	auto json = nlohmann::json::parse(e.get());
	std::string output = json.find("output").value();
	if(output.compare("Hello World") == 0){		
		 start_times.push_back(json.find("start_time").value());
		 end_times.push_back(json.find("end_time").value());
	}
   } 
   int i =0, j = 0, max_count = 0, count = 0;
   std::sort(start_times.begin(), start_times.end());
   std::sort(end_times.begin(), end_times.end());
   std::cout.precision(2);
   for (int i = 0; i < start_times.size(); i++)
	std::cout << std::fixed << start_times[i] << " " << end_times[i] << "\n";

   while(i < start_times.size() && j < start_times.size()){
   	if(start_times[i] < end_times[j]){
		count++;
		i++;
	}else{
		count--;
		j++;
	}
	if(count > max_count)
		max_count = count;
   }
  std::cout << "LambdaExecuted =  " << start_times.size() << "\n";
  std::cout << "LambdaConcurrent = " << max_count << "\n";
   
  
}
