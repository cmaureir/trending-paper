#!/usr/bin/env python
import matplotlib.pyplot as p
from pylab import *
l=[1,2,3,4,5,6,7,8,9,10]
p1=[
229.19430979,
320.69903346,
309.99869180,
487.46943368,
944.23347936,
948.85812726,
945.17822777,
923.96744099,
906.27301170,
954.63513003
]

p2=[
43.1734931906,
43.2684075729,
34.6533593311,
42.9461372217,
43.5742734278,
42.5249083206,
46.2881758726,
43.2957239746,
42.5026597704,
42.4139279104
]

plot1 = p.plot(l,p1,label='PyQwt')
plot2 = p.plot(l,p2,label='Matplotlib')
title('PyQwt vs Matplotlib (1msec)')
legend((plot1,plot2),('PyQwt','Matplotlib'),loc='center right')
grid(True)
p.axis([0,10,30,1000],0.01)
xlabel('Set of data')
ylabel('FPS')
p.show()
