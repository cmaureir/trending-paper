#!/usr/bin/env python

if False:
    import sip
    sip.settracemask(0x3f)

import random
import sys
import time

from PyQt4 import Qt
import PyQt4.Qwt5 as Qwt
from PyQt4.Qwt5.anynumpy import *




class DataPlot(Qwt.QwtPlot):

    def __init__(self, *args):
        Qwt.QwtPlot.__init__(self, *args)

        self.setCanvasBackground(Qt.Qt.white)
        self.alignScales()

        # Initialize data
        self.x = arange(0.0, 100.1, 0.5)
        self.y = zeros(len(self.x), Float)
        self.z = zeros(len(self.x), Float)

        self.setTitle("PyQwt Example")
        self.insertLegend(Qwt.QwtLegend(), Qwt.QwtPlot.BottomLegend);

        self.curveR = Qwt.QwtPlotCurve("Random Data")
        self.curveR.attach(self)

        self.curveR.setPen(Qt.QPen(Qt.Qt.red))

        mY = Qwt.QwtPlotMarker()
        mY.setLabelAlignment(Qt.Qt.AlignRight | Qt.Qt.AlignTop)
        mY.setLineStyle(Qwt.QwtPlotMarker.HLine)
        mY.setYValue(0.0)
        mY.attach(self)

        self.setAxisTitle(Qwt.QwtPlot.xBottom, "Time (seconds)")
        self.setAxisTitle(Qwt.QwtPlot.yLeft, "Values")
    
        self.startTimer(1)
        self.phase = 0.0
        self.tstart = time.time()
        self.counter = 0

    # __init__()

    def alignScales(self):
        self.canvas().setFrameStyle(Qt.QFrame.Box | Qt.QFrame.Plain)
        self.canvas().setLineWidth(1)
        for i in range(Qwt.QwtPlot.axisCnt):
            scaleWidget = self.axisWidget(i)
            if scaleWidget:
                scaleWidget.setMargin(0)
            scaleDraw = self.axisScaleDraw(i)
            if scaleDraw:
                scaleDraw.enableComponent(
                    Qwt.QwtAbstractScaleDraw.Backbone, False)

    # alignScales()
    
    def timerEvent(self, e):
        self.counter += 1
        if self.phase > pi - 0.0001:
            self.phase = 0.0

        # y moves from left to right:
        # shift y array right and assign new value y[0]
        self.y = concatenate((self.y[:1], self.y[:-1]), 1)
        self.y[0] = sin(self.phase) * (-1.0 + 2.0*random.random())
		
        # z moves from right to left:
        # Shift z array left and assign new value to z[n-1].
        self.z = concatenate((self.z[1:], self.z[:1]), 1)
        self.z[-1] = 0.8 - (2.0 * self.phase/pi) + 0.4*random.random()

        self.curveR.setData(self.x, self.y)

        self.replot()
        if self.counter == 100:
            print "FPS: ", 100/(time.time()-self.tstart)
            self.counter = 0
            self.tstart = time.time()
        self.phase += pi*0.02

    # timerEvent()

# class DataPlot

def make():
    demo = DataPlot()
    demo.resize(500, 300)
    demo.show()
    return demo

# make()

def main(args): 
    app = Qt.QApplication(args)
    demo = make()
    sys.exit(app.exec_())

# main()

# Admire
if __name__ == '__main__':
    main(sys.argv)
