import serial
import time
from bottle import run, route, template, response

ser = serial.Serial('/dev/ttyS3', 9600, timeout=0.1)
time.sleep(2)

@route('/api/<name>')
def index(name):
    ser.write(str.encode(name + ';'))
    #ser.close()

    response.headers['Access-Control-Allow-Origin'] = '*'
    return template('<b>Hello {{name}}</b>!', name=name)

run(host='localhost', port=8080)