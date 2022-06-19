import random

from time import sleep
from time import time


from flask import Flask
from flask import jsonify

app = Flask(__name__)

saved_time = time()

@app.route('/')
def index():
    global saved_time
    # return 'Web App with Python Flask!'
    a = random.randint(1, 100)
    b = random.randint(0, 2**32 - 1)
    out = {"a": a, "b": b}
    # time operation
    current_time = time()
    delta_time = current_time - saved_time
    sleep(max(0, 0.100 - delta_time))
    saved_time = time()
    return jsonify(out)


if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8080)
