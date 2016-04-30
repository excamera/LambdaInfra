import subprocess as sp

def handler(event, context):
        try:
	    output = sp.check_output("./helloworld")
        except sp.CalledProcessError as e:
            output = e.output
	return {'output':output}
