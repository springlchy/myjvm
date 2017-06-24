package test;

public class Fibonacci{
	private int[] fa;
	private int maxSize;
	private int position;

	public Fibonacci(int maxSize)
	{
		this.maxSize = maxSize;
		this.fa = new int[maxSize];
		this.fa[0] = this.fa[1] = 1;
		this.position = 1;
	}

	private int getFibN(int n)
	{
		if (n >= this.maxSize) {
			System.out.println("n is to big, max n should be: " + this.maxSize);
			return -1;
		}

		if (n > this.position) {
			for (int i=position+1; i<=n; i++) {
				this.fa[i] = this.fa[i-2] + this.fa[i-1];
			}

			this.position = n;	
		}

		return this.fa[n];
	}

	public static void main(String[] args)
	{
		Fibonacci fib = new Fibonacci(100);
		int a = fib.getFibN(5);
		int b = fib.getFibN(10);

		System.out.println("a=" + a + ", b=" + b);
	}
}