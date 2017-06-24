package test;

class TestInheritance
{
	public static void main(String[] args)
	{
		Child someone = new Child();

		someone.setZ1(3); // invoke public method of parent class
		someone.x1 = 1;   // access public field
		someone.y1 = 2;   // access protected field

		int result = someone.doSomething();
	}	
}