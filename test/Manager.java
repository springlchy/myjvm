package test;

class Manager extends Employee
{
	private int bonus;
	Manager(int baseSalary, int bonus)
	{
		super(baseSalary);
		this.bonus = bonus;
	}

	public int getSalary()
	{
		return 2 * super.getSalary() + bonus;
	}
}