#!/usr/bin/env python
import matplotlib.pyplot as p
from pylab import *
l=[1,2,3,4,5,6,7,8,9,10]
p1=[
86.816555467,
99.998593350,
100.00829766,
100.00278958,
100.00259883,
100.00221734,
100.00247962,
98.172334027,
99.999499324,
100.00538855
]

p2=[
40.741115967,
41.569051557,
34.554454499,
36.780515772,
46.214905552,
45.428628771,
45.302677503,
45.227462877,
45.535870252,
44.638595133
]

plot1 = p.plot(l,p1,label='PyQwt')
plot2 = p.plot(l,p2,label='Matplotlib')
title('PyQwt vs Matplotlib (10msec)')
legend((plot1,plot2),('PyQwt','Matplotlib'),loc='center right')
grid(True)
p.axis([0,10,30,105],0.01)
xlabel('Set of data')
ylabel('FPS')
p.show()
