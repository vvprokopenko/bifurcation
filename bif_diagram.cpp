#include <iostream>
#include <omp.h>

using namespace std;

double system_func(double u0, double r)
{
	return r*u0*(1 - u0);
}

int main()
{
	int t_stabilize = 900;
	int t_print = 1000;
	double rmin = 0;
	double rmax = 4;
	double r;
	double u0;
	int N = 1024;
	double coef = (rmax - rmin)/N;
	int i;
	double t;
	double u;
	#pragma omp parallel for
	for (i = 1; i <= N; i++)
	{
		r = rmin + coef*i;
		u0 = 0.1;
		u = u0;
		for (t = 1; t <= t_stabilize; t++)
		{
			u = system_func(u0, r);
			u0 = u;
		}
		for (t = t_stabilize + 1; t <= t_print; t++)
		{
			u = system_func(u0, r);
			cout << r << ' ' << u << endl;
			u0 = u;
		}
	}
	cout << clock()/1000000.0;
}