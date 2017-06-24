package test;

class Parent
{
	public int x1;
	protected int y1;
	private int z1;

	public void setZ1(int z1)
	{
		this.z1 = z1;
	}
	public int getZ1()
	{
		return this.z1;
	}

	protected int addXY()
	{
		return this.x1 + this.y1;
	}
}