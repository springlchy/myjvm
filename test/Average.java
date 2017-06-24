package test;

public class Average{
	public static void main(String[] args) {
		double avg;
		int n = 100;
		int sum = 0;

		for (int i=1; i<=n; i++) {
			sum += i;
		}

		avg = (double)(sum)/n;
	}
}