"""
    Flask app that plays music.  Super annoying, hopefully.
"""
import os
import winsound

from flask import Flask, render_template

# Not ideal, but since it's just being used across a home network not concerned at the moment.
app = Flask(__name__, static_url_path='/static')

@app.route('/')
def load_home():
    print os.curdir
    return render_template('index.html')

@app.route('/play')
def play_track():
    winsound.PlaySound('D:\code\tap-player\test.wmv', winsound.SND_FILENAME)
    return render_template('play.html')

if __name__ == "__main__":
    app.run(host='0.0.0.0')
