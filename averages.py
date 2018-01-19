#!/usr/bin/python
import plotly
from plotly.graph_objs import Bar, Layout

f1 = open("processresults","r")
f2 = open("threadresults","r")

processresults = []
threadresults = []
pavg = 0
tavg = 0
c = 0

for line in f1:
    #pavg += float(line[36:44])
    #print line.split()[2]
    pavg += float(line.split()[2])
    c += 1

for line in f2:
    #tavg += float(line[36:44])
    tavg += float(line.split()[2])

pavg /= c;
tavg /= c;

plotly.offline.plot({
    "data": [Bar(x=['Averages'], y=[pavg], name="Processes Average"), Bar(x=['Averages'], y=[tavg], name="Threads Average")],
    "layout": Layout(title="Process & Thread Averages")
}, filename="averages.html")

f1.close()
f2.close()
