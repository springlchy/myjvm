package test;

class TestStatic
{
	static int i = 3 ;
	static float f = 10.25f;

	public static void main(String[] args)
	{
		int x = TestStatic.i + HelloStatic.getI();
		float y = TestStatic.f + HelloStatic.getF();
	}
}
