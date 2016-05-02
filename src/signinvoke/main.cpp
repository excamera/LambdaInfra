#include <iostream>
#include "awsv4.hpp"

int main(int argc, char** argv) {
	std::cout << AWSV4::invoke_request(AWSV4::get_request_params());
}
