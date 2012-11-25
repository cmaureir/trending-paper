#!/usr/bin/env python                                           
import matplotlib.pyplot as p                                   
from pylab import *                                             
l=[1,2,3,4,5,6,7,8,9,10]                                        
p1=[                                                            
37682,        
40913,                                                        
57068,                                                        
47087,                                                        
44946,                                                        
86246,                                                        
50721,                                                        
51871,                                                        
51621,                                                        
51010                                                        
]                                                               
p2=[                                                            
16182,                                                       
21844,                                                       
19081,                                                       
16508,                                                       
14460,                                                       
13079,                                                       
11816,                                                       
10896,                                                       
10075,                                                       
11954                                                       
]                                                               
                                                                
plot1 = p.plot(l,p1,label='Qwt')                                
plot2 = p.plot(l,p2,label='wxMathPlot')                         
title('Qwt vs wxMathPlot (100msec)')                             
legend((plot1,plot2),('Qwt','wxMathPlot'),loc='upper right')   
grid(True)                                                      
p.axis([0,10,9000,87000],0.01)                                 
xlabel('Set of data')                                           
ylabel('FPS')                                                   
p.show()                                                        
