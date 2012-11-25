/**
 * TimeChart Performance test
 * Here, the test in conduced only by timer events. To Render, to count FPS
 */


import java.awt.Color;
import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.ui.ApplicationFrame;
import org.jfree.ui.RefineryUtilities;
import org.jfree.data.time.Millisecond;
import org.jfree.data.time.Second;
import org.jfree.data.time.TimeSeries;
import org.jfree.data.time.TimeSeriesCollection;
import org.jfree.chart.plot.XYPlot;
import org.jfree.chart.renderer.xy.XYLineAndShapeRenderer;

import javax.swing.Timer;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

public class TimeChart extends ApplicationFrame {


	private static final long serialVersionUID = 1L;

	public TimeChart(final String title, TimeSeries data[]) {
		super(title);
		
        final TimeSeriesCollection dataset = new TimeSeriesCollection(data[0]);
        if (data.length > 1){
        	for( int o = 1; o < data.length; o++){
        		dataset.addSeries(data[o]);
        	}
        }
        chart = ChartFactory.createTimeSeriesChart(
            title,			// Chart Title
            "Time", 		// Domain axis label
            "Property Unit",// Range axis label
            dataset,		// Data
            true,			// include legend
			true,			// tooltips
			false			// urls
        );
        
        // Begin Customization
        chart.setBackgroundPaint(Color.white);
		chart.setAntiAlias( false );

		final XYPlot plot = chart.getXYPlot();
//		plot.setBackgroundPaint(Color.lightGray);
//		plot.setDomainGridlinePaint(Color.white);
//		plot.setRangeGridlinePaint(Color.white);
		final XYLineAndShapeRenderer renderer = new XYLineAndShapeRenderer();
		renderer.setSeriesLinesVisible(4, true);
		renderer.setSeriesShapesVisible(4, false);
		renderer.setSeriesLinesVisible(3, true);
		renderer.setSeriesShapesVisible(3, false);
		renderer.setSeriesLinesVisible(2, true);
		renderer.setSeriesShapesVisible(2, false);
		renderer.setSeriesLinesVisible(1, true);
		renderer.setSeriesShapesVisible(1, false);
		renderer.setSeriesLinesVisible(0, true);
		renderer.setSeriesShapesVisible(0, false);
		plot.setRenderer(renderer);
		// End Customization
		
        final ChartPanel chartPanel = new ChartPanel(chart, true);
        chartPanel.setPreferredSize(new java.awt.Dimension(500, 400));
        setContentPane(chartPanel);
		pack();
        RefineryUtilities.centerFrameOnScreen(this);
        setVisible(true);
	}

	static public JFreeChart chart;

	public static void main(String args[]) {

		xy[0] = new TimeSeries("a", Millisecond.class);
		xy[1] = new TimeSeries("b", Millisecond.class);
		xy[2] = new TimeSeries("c", Millisecond.class);
		xy[3] = new TimeSeries("d", Millisecond.class);
		xy[4] = new TimeSeries("e", Millisecond.class);

		fps = 4;

		myChart = new TimeChart("Line Chart",xy);
		chart.setNotify(false);

		ActionListener inputData = new ActionListener() {
			public void actionPerformed(ActionEvent evt) {
				Second today = new Second();
		        
				xy[0].add(new Millisecond(1+i, today),0.0+i);
				xy[1].add(new Millisecond(1+i, today),10000-i);
				xy[2].add(new Millisecond(1+i, today),5000-i);
				xy[3].add(new Millisecond(1+i, today),2000+i);
				xy[4].add(new Millisecond(1+i, today),7000-i);
				i++;
				j++;
				if( i > 72000 ){
					//xy[0].remove(0);
					//xy[1].remove(0);
					//xy[2].remove(0);
					//xy[3].remove(0);
					//xy[4].remove(0);
				}
			}
		};
		new Timer(100, inputData).start();

		ActionListener fpsCalculation = new ActionListener() {
			public void actionPerformed(ActionEvent evt) {
				System.out.print("Datos Procesados: ");
				System.out.println( j );
				System.out.print("FPS: ");
				System.out.println( k );
				j = 0;
				k = 0;
			}
		};
		new Timer(1000, fpsCalculation).start();

		ActionListener rendering = new ActionListener() {
			public void actionPerformed(ActionEvent evt) {
				chart.setNotify(true);
				chart.setNotify(false);
				k++;
			}
		};
		new Timer(1000/fps, rendering).start();
	}
	static public int i = 0;
	static public int j = 0;
	static public int k = 0;
	static public int fps = 0;
	static public TimeSeries[] xy = new TimeSeries[5];
	static long antes = 0;
	static TimeChart myChart;

}
