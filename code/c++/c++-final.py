from numpy import std,mean

print "C++-1"
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
print "Qwt"
print "Des: ",  std(p1)
print "Prom: ",  mean(p1)

print "wxMathPlot"
print "Des: ",  std(p2)
print "Prom: ",  mean(p2)

print "C++-10"

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

print "Qwt"
print "Des: ",  std(p1)
print "Prom: ",  mean(p1)

print "wxMathPlot"
print "Des: ",  std(p2)
print "Prom: ",  mean(p2)

print "C++-100"
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

print "Qwt"
print "Des: ",  std(p1)
print "Prom: ",  mean(p1)

print "wxMathPlot"
print "Des: ",  std(p2)
print "Prom: ",  mean(p2)
