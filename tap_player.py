"""
    Flask app that plays music.  Super annoying, hopefully.
"""
import os
from flask import Flask, render_template
import pygame
import time
import random

# Not ideal, but since it's just being used across a home network not concerned at the moment.
app = Flask(__name__, static_url_path='/static')

@app.route('/')
def load_home():
    print os.curdir
    return render_template('index.html')

@app.route('/play')
def play_track():
    tracks = os.listdir('media/')
    track = 'media/' + random.choice(tracks)
    print track
    pygame.mixer.init()
    pygame.mixer.music.load(track)
    pygame.mixer.music.play()
    return render_template('play.html')

if __name__ == "__main__":
    app.run(host='0.0.0.0')
