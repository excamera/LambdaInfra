#!/bin/bash

zip -j ${CMAKE_CURRENT_BINARY_DIR}/helloworld.zip ${CMAKE_CURRENT_BINARY_DIR}/helloworld ${CMAKE_SOURCE_DIR}/src/lambda/handler.py
aws lambda update-function-code --function-name ${LAMBDA_NAME} --zip-file fileb://${CMAKE_CURRENT_BINARY_DIR}/helloworld.zip








