#include <iostream>

#include <cpr/cpr.h>
#include "awsv4.hpp"
//#include <json.hpp>

int print_final() {


    const std::time_t request_date = time(0);

    const std::string region{"eu-west-1"};
    const std::string service{"lambda"};
    const std::string lambda_name(std::getenv("LAMBDA_NAME"));	
    std::string base_uri{"https://lambda.eu-west-1.amazonaws.com/2015-03-31/functions/"};
    base_uri += lambda_name;
    base_uri += std::string("/invocations");
    const std::string query_args{""};
    const std::string uri_str{base_uri + "?" + query_args};

    Poco::URI uri;
    try {
        uri = Poco::URI(uri_str);
    } catch (std::exception& e) {
        throw std::runtime_error(e.what());
    }
    uri.normalize();
    const auto amz_date = AWSV4::ISO8601_date(request_date);
    const auto canonical_uri = AWSV4::canonicalize_uri(uri);
    const auto canonical_query = AWSV4::canonicalize_query(uri); 
    const std::vector<std::string> headers{"host: lambda.eu-west-1.amazonaws.com",
            "Content-type: application/x-amz-json-1.0",
            "x-amz-date: "+ amz_date};
    
    const auto canonical_headers_map = AWSV4::canonicalize_headers(headers);
    if (canonical_headers_map.empty()) {
        std::cerr << "headers malformed" << std::endl;
        std::exit(1);
    }
    const auto headers_string = AWSV4::map_headers_string(canonical_headers_map);
    const auto signed_headers = AWSV4::map_signed_headers(canonical_headers_map);

    const std::string payload{"{}"};
    auto sha256_payload = AWSV4::sha256_base16(payload); 
    
    const auto canonical_request = AWSV4::canonicalize_request(AWSV4::POST,
                                                               canonical_uri,
                                                               canonical_query,
                                                               headers_string,
                                                               signed_headers,
                                                               payload);
    

    auto hashed_canonical_request = AWSV4::sha256_base16(canonical_request); 

    auto credential_scope = AWSV4::credential_scope(request_date,region,service);
    auto string_to_sign = AWSV4::string_to_sign(AWSV4::STRING_TO_SIGN_ALGO,
                                                request_date,
                                                credential_scope,
                                                hashed_canonical_request);


    const std::string secret(std::getenv("AWS_SECRET_ACCESS_KEY"));
    auto signature = AWSV4::calculate_signature(request_date, 
                                                secret,
                                                region,
                                                service,
                                                string_to_sign);
    
    
    auto access_key = std::string(std::getenv("AWS_ACCESS_KEY_ID"));
    auto algorithm = std::string("AWS4-HMAC-SHA256");
    auto authorization_header = algorithm + " Credential=" + access_key + "/"+credential_scope + ", SignedHeaders=" + signed_headers + ", Signature=" + signature;    
    auto payloady = cpr::Body{"{}"};
   
    auto url = cpr::Url{base_uri} ;
    auto header = cpr::Header{{"host", "lambda.eu-west-1.amazonaws.com"}, {"Content-type", "application/x-amz-json-1.0"},{"x-amz-date", amz_date}, {"Authorization", authorization_header}};
    auto response = cpr::Post(url, header, payloady);
    std::cout << response.text;

    return 0;
}

int main(int argc, char** argv) {
	print_final();
}
