import java.awt.Color;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.Calendar;

import javax.swing.JFrame;
import aw.gui.chart.AbstractDataCollector;
import aw.gui.chart.Chart2D;
import aw.gui.chart.ITrace2D;
import aw.gui.chart.RandomDataCollector;
import aw.gui.chart.Trace2DLtd;
import aw.gui.chart.ITrace2D.Trace2DChangeEvent;
import aw.gui.chart.ITrace2D.Trace2DListener;

public class MinimalDynamicChart {
  private MinimalDynamicChart() {
    super();
  }
  private static int counter;
  private static long a,b;
  public static void main(String[]args){
		counter = 0;
		a = Calendar.getInstance().getTimeInMillis();
	    // Create a chart:  
	    Chart2D chart = new Chart2D();
	    // Create an ITrace: 
	    // Note that dynamic charts need limited amount of values!!! 
	    ITrace2D trace = new Trace2DLtd(200); 
	    trace.setColor(Color.RED);
 
    // Add the trace to the chart: 
    chart.addTrace(trace);
    
    // Make it visible:
    // Create a frame. 
    JFrame frame = new JFrame("MinimalDynamicChart");
    // add the chart to the frame: 
    frame.getContentPane().add(chart);
    frame.setSize(400,300);
    // Enable the termination button [cross on the upper right edge]: 
    frame.addWindowListener(
        new WindowAdapter(){
          public void windowClosing(WindowEvent e){
              System.exit(0);
          }
        }
      );
    //frame.show(); 
    frame.setVisible(true);
    // Every 10 milliseconds a new value is collected. 
    AbstractDataCollector collector = new RandomDataCollector(trace,1);
 
    Trace2DListener listener = new Trace2DListener() {
		@Override
		public void traceChanged(Trace2DChangeEvent e) {
			counter ++;
			if (counter == 100){
				b = Calendar.getInstance().getTimeInMillis();
				System.out.println("FPS: "+100.0/((double)(b-a)/1000));
				a = b;
				counter = 0;
			}
		}
	};
    trace.addChangeListener(listener);
    // Start a Thread that adds the values: 
    new Thread(collector).start();
 
    
	
  }
}