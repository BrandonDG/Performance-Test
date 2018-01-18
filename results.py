#!/usr/bin/python
import plotly
from plotly.graph_objs import Scatter, Layout

f1 = open("processresults","r")
f2 = open("threadresults","r")

processresults = []
threadresults = []
componentnumbers = []
c = 0

for line in f1:
    processresults.append(float(line[36:44]))
    c += 1
    componentnumbers.append(c)

for line in f2:
    threadresults.append(float(line[36:44]));

plotly.offline.plot({
    "data": [Scatter(x=componentnumbers, y=processresults, name="Processes"), Scatter(x=componentnumbers, y=threadresults, name="Threads")],
    "layout": Layout(title="Processes vs. Threads", xaxis=dict(title='Component Number'), yaxis=dict(title="Run Time"))
}, filename="results.html")

f1.close()
f2.close()
