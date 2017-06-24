package test;

class Engineer extends Employee
{
	private int bonus;
	Engineer(int baseSalary, int bonus)
	{
		super(baseSalary);
		this.bonus = bonus;
	}
	public int getSalary()
	{
		return super.getSalary() + this.bonus;
	}
}