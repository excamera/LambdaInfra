#!/bin/bash

zip helloworld.zip ${CMAKE_CURRENT_BINARY_DIR}/helloworld handler.py
# aws s3api create-bucket --bucket lambdazipsbucket
# aws s3 cp helloworld.zip s3://lambdazipsbucket
aws lambda create-function --function-name ${LAMBDA_NAME} --runtime python2.7 --role ${ROLE} --handler handler.handler --zip-file fileb://./helloworld.zip
