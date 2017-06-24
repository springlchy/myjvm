package test;

class Child extends Parent
{
	private int x2 = 4;

	public int doSomething()
	{
		int xy = this.addXY(); // invoke protected method of parent class

		return xy + super.getZ1() + this.x2;
	}
}
