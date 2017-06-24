package test;

public class Hello implements IMath{
	static double C_DOUBLE = 12.45;
	public int xi = 789;
	protected long xl = 35;
	public float xf = -235.125f;
	public double db = 32.5;
	private int priv_i = 2;

	public int sum(int x, int y)
	{
		int s = 0;
		for(int i=x;i<=y;i++) {
			s+=i;
		}

		s += sub(x,y);
		return s+xi + this.priv_i;
	}

	private int sub(int x, int y) {
		return x-y;
	}
}

interface IMath {
	public int sum(int x, int y);
}
