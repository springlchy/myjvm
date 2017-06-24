package test;

public class TestAArray{
	private int ai;
	public static void main(String[] args) {
		TestAArray[] arrs = new TestAArray[3];
		arrs[0] = new TestAArray();
		arrs[1] = new TestAArray();

		arrs[0].ai = 10;
		arrs[1].ai = 110;

		int result = arrs[0].ai + arrs[1].ai;
	}
}