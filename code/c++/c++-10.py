#!/usr/bin/env python                                         
import matplotlib.pyplot as p                                 
from pylab import *                                           
l=[1,2,3,4,5,6,7,8,9,10]                                      
p1=[                                                          
42161,
41765,
58107,
57685,
44718,
50387,
45031,
45885,
41300,
51263
]                                                             
                                                              
p2=[                                                          
13194,
65956,
45494,
33445,
26658,
22036,
18843,
16413,
14599,
13243
]                                                             
                                                              
plot1 = p.plot(l,p1,label='Qwt')                              
plot2 = p.plot(l,p2,label='wxMathPlot')                       
title('Qwt vs wxMathPlot (10msec)')                            
legend((plot1,plot2),('Qwt','wxMathPlot'),loc='upper right') 
grid(True)                                                    
p.axis([0,10,13190,66000],0.01)                               
xlabel('Set of data')                                         
ylabel('FPS')                                                 
p.show()                                                      
