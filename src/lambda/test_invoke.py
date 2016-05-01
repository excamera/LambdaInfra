from sign_invoke import invokeLambda
import json
import os
(output, ret_code)=invokeLambda(os.environ.get('LAMBDA_NAME'))
output = json.loads(output)
print "Output : %s" % output
if output['output'] == "Hello World" and ret_code == 200:
	print "Invocation Success"
else:
	print "Invocation Error" 
