# -*- coding: utf-8 -*-
import serial
from flask import Flask, url_for, render_template, abort, redirect, g, jsonify

ser = serial.Serial('/dev/tty.SLAB_USBtoUART')
ser.baudrate = 230400

app = Flask(__name__)

@app.route('/')
def index():
	return render_template('index.html')

@app.route('/api/status')
def api():
	ser.write('<')
	st = ser.readline().replace('\00','').replace('\n','').replace('\r','').split('@')
	result = {}
	for i in range(len(st)):
		result[str(i)] = st[i]

	return jsonify(result)
	# return jsonify(result)



if __name__ == '__main__':
	# app.run(host = '0.0.0.0')
	app.run(debug="true")
