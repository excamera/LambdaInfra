import subprocess as sp
import time

def handler(event, context):
        try:
	    start_time = time.time()
	    output = sp.check_output("./helloworld")
	    end_time = time.time()
        except sp.CalledProcessError as e:
            output = e.output
	return {'output':output, 'start_time': start_time, 'end_time' : end_time}
