package test;

public class TestArray{
	public static void main(String[] args) {
		int[] a= new int[3];

		a[0] = 1;
		a[1] = 2;
		int result = a[0] + a[1];

		float[] f = new float[2];
		f[0] = 1.1f;
		f[1] = 2.3f;
		float rresult = f[0] + f[1];

		long[] l = new long[2];
		l[0] = 123456;
		l[1] = 78901;
		long lresult = l[0] + l[1];

	}
}