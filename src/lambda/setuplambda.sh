#!/bin/bash

zip -j ${CMAKE_CURRENT_BINARY_DIR}/helloworld.zip ${CMAKE_CURRENT_BINARY_DIR}/helloworld ${CMAKE_SOURCE_DIR}/src/lambda/handler.py
aws lambda create-function --function-name ${LAMBDA_NAME} --runtime python2.7 --role ${ROLE} --handler handler.handler --zip-file fileb://${CMAKE_CURRENT_BINARY_DIR}/helloworld.zip
