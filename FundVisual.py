import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.ticker
import numpy as np

capital = {'MSK':[],'SPB':[]}
crisis = {'MSK':[],'SPB':[]}
dates = []

file1 = open("F:Data.txt", "r")
for line in (file1):
    a = [i for i in line.split(' ')]
    if str(a[1]) not in capital:
        capital[str(a[1])] = []
    capital[str(a[1])] += [float(a[2])]
    if str(a[1]) not in crisis:
        crisis[str(a[1])] = []
    crisis[str(a[1])] += [float(a[3])]
    if a[0] not in dates:
        dates.append(a[0])

dates.pop()

fig = plt.figure()
ax1 = fig.add_subplot(111)
for i in capital:
    ax1.plot(capital[i])

ax1.set_xlabel('Date')
ax1.set_ylabel('Capital')
ax1.legend([city for city in capital],loc = 'center right')
ax1.set_title('Vizualization')
plt.xticks(np.arange(len(dates)),dates)
ax1.grid(True)

fig = plt.figure()
ax2 = fig.add_subplot(111)
for i in crisis:
    ax2.plot(crisis[i])

ax2.set_xlabel('Date')
ax2.set_ylabel('Crisis')
ax2.legend([city for city in crisis],loc = 'center right')
ax2.set_title('Vizualization')
plt.xticks(np.arange(len(dates)),dates)
ax2.grid(True)

plt.show()


#df = pd.DataFrame('Date','City','Capital','Crisis')
