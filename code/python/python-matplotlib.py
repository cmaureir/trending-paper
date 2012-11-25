import os
import pprint
import random
import sys
import wx
import time

import matplotlib
matplotlib.use('WXAgg')
from matplotlib.figure import Figure
from matplotlib.backends.backend_wxagg import \
    FigureCanvasWxAgg as FigCanvas, \
    NavigationToolbar2WxAgg as NavigationToolbar
import numpy as np
import pylab


class DataGen(object):
    """ A silly class that generates pseudo-random data for
        display in the plot.
    """
    def __init__(self, init=50):
        self.data = self.init = init
        
    def next(self):
        self._recalc_data()
        return self.data
    
    def _recalc_data(self):
        delta = random.uniform(-0.5, 0.5)
#        r = random.random()
        self.data += delta		
#        if r > 0.9:
#            self.data += delta * 15
#        elif r > 0.8: 
#            delta += (0.5 if self.init > self.data else -0.5)
#            self.data += delta
#        else:
#            self.data += delta


class GraphFrame(wx.Frame):
    title = 'matplotlib example'
    
    def __init__(self):
        wx.Frame.__init__(self, None, -1, self.title, [200,200], [300,300]) 
        self.datagen = DataGen()
        self.data = [self.datagen.next()]
        
        self.create_main_panel()
        self.redraw_timer = wx.Timer(self)
        self.Bind(wx.EVT_TIMER, self.on_redraw_timer, self.redraw_timer)
        self.tstart = time.time()
        self.redraw_timer.Start(1)
        self.counter = 0

    def create_main_panel(self):
        self.panel = wx.Panel(self)

        self.init_plot()
        self.canvas = FigCanvas(self.panel, -1, self.fig)

        
        self.cb_xlab = wx.CheckBox(self.panel, -1, 
            "Show X labels",
            style=wx.ALIGN_RIGHT)
        self.Bind(wx.EVT_CHECKBOX, self.on_cb_xlab, self.cb_xlab)        
        self.cb_xlab.SetValue(True)
        
    def init_plot(self):
        self.dpi = 100
        self.fig = Figure((3.0, 3.0), dpi=self.dpi)

        self.axes = self.fig.add_subplot(111)
        self.axes.set_axis_bgcolor('black')
        self.axes.set_title('random data', size=12)
        
        pylab.setp(self.axes.get_xticklabels(), fontsize=8)
        pylab.setp(self.axes.get_yticklabels(), fontsize=8)

        # plot the data as a line series, and save the reference 
        # to the plotted line series
        #
        self.plot_data = self.axes.plot(
            self.data, 
            linewidth=1,
            color=(1, 1, 0),
            )[0]

    def draw_plot(self):
        xmax = len(self.data) if len(self.data) > 50 else 50
        xmin = xmax - 50
        ymin = round(min(self.data), 0) - 1
        ymax = round(max(self.data), 0) + 1

        self.axes.set_xbound(lower=xmin, upper=xmax)
        self.axes.set_ybound(lower=ymin, upper=ymax)
        
        pylab.setp(self.axes.get_xticklabels(), 
            visible=self.cb_xlab.IsChecked())
        
        self.plot_data.set_xdata(np.arange(len(self.data)))
        self.plot_data.set_ydata(np.array(self.data))
        
        self.canvas.draw()

 
    def on_cb_xlab(self, event):
        self.draw_plot()
    
    def on_redraw_timer(self, event):
        self.data.append(self.datagen.next())
        self.draw_plot()
        self.counter += 1
        if self.counter == 100:
             print 'FPS:' , 100/(time.time()-self.tstart)
             self.tstart = time.time()
             self.counter = 0
    
if __name__ == '__main__':
    app = wx.PySimpleApp()
    app.frame = GraphFrame()
    app.frame.Show()
    app.MainLoop()

