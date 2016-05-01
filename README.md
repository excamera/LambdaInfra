
### Installation ###
To use CMake you'll need to download it (http://www.cmake.org/cmake/resources/software.html) or install it via:
```bash
(Linux) : sudo apt-get install cmake
(OS X)  : brew install cmake
```


Enviroment Variables:

You have to set the following variables

        "AWS_ACCESS_KEY_ID",
        "AWS_SECRET_ACCESS_KEY",
        "ROLE"   - This is the ARN of the role that the lambda will assume when running.
        "LAMBDA_NAME" - The name of the lambda

You need to have a adminuser profile in ~/.aws/credentials

Navigate to the root of the project and issue the following commands:
```bash
mkdir build
cd build
cmake .. && make
make lambdainstall
make lambdaupdate
make check
```
