
### Installation ###
This tool has been tested on Ubuntu 14.04


1.Dependencies boost openssl poco awscli cmake

They can be installed o Ubuntu 14.04 using

./install_dependencies.sh

2.Enviroment Variables:
You have to set the following variables

        "AWS_ACCESS_KEY_ID",
        "AWS_SECRET_ACCESS_KEY",
        "ROLE"   - This is the ARN of the role that the lambda will assume when running.
        "LAMBDA_NAME" - The name of the lambda

They can be set by entering the values in setup_env_var.sh and then running source ./setup_env_var.sh

3.You need to have a adminuser profile in ~/.aws/credentials

4.Navigate to the root of the project and issue the following commands:
```
git submodule update --init --recursive
bash
mkdir build
cd build
cmake .. && make
make lambdainstall
make lambdaupdate
make check
make checkcpp
```
