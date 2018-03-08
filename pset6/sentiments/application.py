from flask import Flask, redirect, render_template, request, url_for

import helpers
from analyzer import Analyzer
import os
import sys

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/search")
def search():

    # validate screen_name
    screen_name = request.args.get("screen_name", "")
    if not screen_name:
        return redirect(url_for("index"))

    # get screen_name's tweets
    tweets = helpers.get_user_timeline(screen_name)

    # absolute paths to lists
    positives = os.path.join(sys.path[0], "positive-words.txt")
    negatives = os.path.join(sys.path[0], "negative-words.txt")

    # instantiate analyzer
    analyzer = Analyzer(positives, negatives)

    # queries Twitter's API for user's most recent 100 tweets
    tweets = helpers.get_user_timeline(screen_name, 100)

    # if screen_name doesn't exist, return error
    if tweets == None:
        sys.exit("User is private or doesn't exist")

    # if screen_name exist, analyze each tweet and output it
    positive, negative, neutral = 0, 0, 0
    for tweet in tweets:
        # analyze word
        score = analyzer.analyze(tweet)
        if score > 0.0:
            positive += 1
        elif score < 0.0:
            negative += 1
        else:
            neutral += 1

    # generate chart
    chart = helpers.chart(positive, negative, neutral)

    # render results
    return render_template("search.html", chart=chart, screen_name=screen_name)
