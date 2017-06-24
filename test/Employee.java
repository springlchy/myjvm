package test;

class Employee
{
	private int baseSalary;
	Employee(int baseSalary)
	{
		this.baseSalary = baseSalary;
	}

	public int getSalary()
	{
		return this.baseSalary;
	}
}