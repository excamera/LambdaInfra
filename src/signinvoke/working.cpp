#include <iostream>

#include <cpr/cpr.h>
//#include <json.hpp>


int main(int argc, char** argv) {
    auto endpoint = "https://lambda.eu-west-1.amazonaws.com/2015-03-31/functions/HelloWorld/invocations";
    auto url = cpr::Url{endpoint} ;
    auto auth = "AWS4-HMAC-SHA256 Credential=AKIAJIL4IVPNC7TI536A/20160430/eu-west-1/lambda/aws4_request, SignedHeaders=content-type;host;x-amz-date, Signature=40ac26755a2e744155a69ec48e1a90461b113c0379aecd2ef18486b48dc79aa3";
    auto header = cpr::Header{{"host", "lambda.eu-west-1.amazonaws.com"}, {"Content-type", "application/x-amz-json-1.0"},{"x-amz-date","20160430T024946Z"}, {"Authorization", auth}};
    auto payload = cpr::Body{"{}"};
    auto response = cpr::Post(url, header, payload);
    std::cout << "here " << response.text << "here";
//    auto json = nlohmann::json::parse(response.text);
//    std::cout << json.dump(4) << std::endl;
}
