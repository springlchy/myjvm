package test;

public class Point{
	private double x;
	private double y;

	public Point(double x, double y)
	{
		this.x = x;
		this.y = y;
	}

	private double distance(Point p)
	{
		double dx = p.x - this.x;
		double dy = p.y - this.y;

		return dx*dx + dy *dy;
	}

	public static void main(String[] args)
	{
		Point p1 = new Point(0,0);
		Point p2 = new Point(3.0, 4.0);

		double dist = p1.distance(p2);
	}
}