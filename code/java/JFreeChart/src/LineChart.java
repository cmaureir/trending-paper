import java.awt.Color;
import java.awt.Dimension;
import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.axis.NumberAxis;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.ui.ApplicationFrame;
import org.jfree.ui.RefineryUtilities;
import org.jfree.data.xy.XYDataset;
import org.jfree.data.xy.XYSeries;
import org.jfree.data.xy.XYSeriesCollection;
import org.jfree.chart.plot.XYPlot;
import org.jfree.chart.renderer.xy.XYLineAndShapeRenderer;

import javax.swing.Timer;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

public class LineChart extends ApplicationFrame {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	public LineChart(String title,XYSeries[] xyData) {
		super(title);
		XYDataset data = createDataset(xyData);
		chart = createChart(data,title);
		ChartPanel panel = new ChartPanel(chart);
		panel.setPreferredSize(new Dimension(500,400));
		setContentPane(panel);
		pack();
        	RefineryUtilities.centerFrameOnScreen(this);
        	setVisible(true);		
	}

	static public JFreeChart chart;

	private XYDataset createDataset(XYSeries data[]) {
		XYSeriesCollection collection = new XYSeriesCollection();
		for(XYSeries line:data) {
			collection.addSeries(line);
		}
		return collection;
	}

	private JFreeChart createChart(XYDataset dataset,String title) {
        
        // create the chart...
		final JFreeChart chart = ChartFactory.createXYLineChart(
		title,       // chart title
		"x",                    // domain axis label
		"y",                   // range axis label
		dataset,                   // data
		PlotOrientation.VERTICAL,  // orientation
		true,                      // include legend
		true,                      // tooltips
		false                      // urls
		);
	
		// NOW DO SOME OPTIONAL CUSTOMISATION OF THE CHART...
	//        final StandardLegend legend = (StandardLegend) chart.getLegend();
	//      legend.setDisplaySeriesShapes(true);
	//    legend.setShapeScaleX(1.5);
	//  legend.setShapeScaleY(1.5);
		//legend.setDisplaySeriesLines(true);
	
		chart.setBackgroundPaint(Color.white);
		chart.setAntiAlias( false );
	
		final XYPlot plot = chart.getXYPlot();
		plot.setBackgroundPaint(Color.lightGray);
	//    plot.setAxisOffset(new Spacer(Spacer.ABSOLUTE, 5.0, 5.0, 5.0, 5.0));
		plot.setDomainGridlinePaint(Color.white);
		plot.setRangeGridlinePaint(Color.white);
		
		final XYLineAndShapeRenderer renderer = new XYLineAndShapeRenderer();
		renderer.setSeriesLinesVisible(1, true);
		renderer.setSeriesShapesVisible(1, false);
		renderer.setSeriesLinesVisible(0, true);
		renderer.setSeriesShapesVisible(0, false);
		plot.setRenderer(renderer);
	
		// change the auto tick unit selection to integer units only...
		final NumberAxis rangeAxis = (NumberAxis) plot.getRangeAxis();
		rangeAxis.setStandardTickUnits(NumberAxis.createIntegerTickUnits());
		// OPTIONAL CUSTOMISATION COMPLETED.
		return chart;
    	}

	

	public static void main(String args[]) {

		xy[0] = new XYSeries("a");
		xy[1] = new XYSeries("b");
		xy[2] = new XYSeries("c");

		myChart = new LineChart("Line Chart",xy);
// 		for( int i =0; i  < 10000; i++ ){
// 			try {
// 				Thread.sleep(100);
// 			} catch(Exception e){}
// 			xy[0].add(5.0+i,6.0+i);
// 			xy[1].add(5.0+i,10000-i);
// 			
// 		}
		
		ActionListener taskPerformer = new ActionListener() {
			public void actionPerformed(ActionEvent evt) {
				if( i == 0 ){
					chart.setNotify(false);
					antes = evt.getWhen();
				}
				xy[0].add(0.0+i,0.0+i);
				xy[1].add(0.0+i,10000-i);
				i++;
				j++;
				System.out.println( j );
				if( (evt.getWhen() - antes)  > 250 ){
					chart.setNotify(true);
					chart.setNotify(false);
					antes = evt.getWhen();
					System.out.println("***FPS***");
					j = 0;
				}
				if( i > 1000 ){
					xy[0].remove(0);
					xy[1].remove(0);
				}
			}
		};
		new Timer(10, taskPerformer).start();
	}
	static public int i = 0;
	static public int j = 0;
	static public XYSeries xy[] = new XYSeries[3];
	static long antes = 0;
	static LineChart myChart;
	
}
