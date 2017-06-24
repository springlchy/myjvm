package test;

class TestPoly
{
	private int getSalary(Employee e)
	{
		return e.getSalary();
	}

	public static void main(String[] args)
	{
		TestPoly obj = new TestPoly();
		Employee emp = new Employee(100);
		Employee eng = new Engineer(150, 50);
		Employee mgr = new Manager(100, 100);

		int salary1 = obj.getSalary(emp);
		int salary2 = obj.getSalary(eng);
		int salary3 = obj.getSalary(mgr);

		int result = salary1;
		result = salary2;
		result = salary3;
	}
}