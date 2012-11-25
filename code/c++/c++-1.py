#!/usr/bin/env python
import matplotlib.pyplot as p
from pylab import *
l=[1,2,3,4,5,6,7,8,9,10]
p1=[
35459,
38366,
38735,
39916,
43963,
49310,
52407,
49720,
52384,
37456
]

p2=[
40148,
10221,
31930,
26540,
22840,
20070,
17840,
15890,
14390,
13300
]

plot1 = p.plot(l,p1,label='Qwt')
plot2 = p.plot(l,p2,label='wxMathPlot')
title('Qwt vs wxMathPlot (1msec)')
legend((plot1,plot2),('Qwt','wxMathPlot'),loc='center right')
grid(True)
p.axis([0,10,10220,52500],0.01)
xlabel('Set of data')
ylabel('FPS')
p.show()
