package test;

class TestString
{
	
	private static void write(int i)
	{
		IOUtil.writeString("hello: " + i);
	}
	public static void main(String[] args)
	{
		write(100);
	}
}