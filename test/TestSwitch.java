package test;

public class TestSwitch extends Hello{
	static int C_INT=4567;
	static short C_SHORT = 124;
	static long C_LONG = 1234566;
	static float C_FLOAT = 123.456f;

	private float f = 3.68f; 	// 5
	private short si = 15; 		// 6
	private int ii = 1223; 		// 7
	private byte b = -126; 		// 8
	private char c = 'A'; 		// 9
	private long l = 1234567; 	// 10
	private double d = 123456.789; // 12

	private static int xadd(int x, int y) {
		return x + y + 1;
	}
	public static void main(String[] args)
	{
		//Hello obj = new Hello();
		TestSwitch t = new TestSwitch();
		int res1 = t.C_INT + 1;
		short res2 = t.C_SHORT--;
		long res3 = TestSwitch.C_LONG + 4;
		float res4 = TestSwitch.C_FLOAT + 3.5f;
		double res5 = TestSwitch.C_DOUBLE + 2.6;
		int res6 = xadd(7,10);
	}

	// private float fadd()
	// {
	// 	return f + si;
	// }
	private int add()
	{
		return b + ii;
	}

	// private float divide()
	// {
	// 	return this.xf/(float)(this.xl);
	// }
}

