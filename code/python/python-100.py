#!/usr/bin/env python
import matplotlib.pyplot as p
from pylab import *
l=[1,2,3,4,5,6,7,8,9,10]
p1=[
9.9994120944,
10.000041008,
10.000063897,
10.000012159,
9.9998958122,
10.000148060,
10.000040055,
9.9999959469,
10.000018835,
9.9999730588
]

p2=[
10.0045360628,
10.0457917423,
10.0222885372,
10.0329885344,
10.0294625793,
10.0304857794,
10.0367023787,
10.0380583322,
10.0293750438,
10.0296566019
]

plot1 = p.plot(l,p1,label='PyQwt')
plot2 = p.plot(l,p2,label='Matplotlib')
title('PyQwt vs Matplotlib (100msec)')
legend((plot1,plot2),('PyQwt','Matplotlib'),loc='lower right')
grid(True)
p.axis([0,10,9.9,10.1],0.01)
xlabel('Set of data')
ylabel('FPS')
p.show()
