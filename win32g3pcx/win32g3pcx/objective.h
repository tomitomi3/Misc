//This routine calculates the objective function
//Code your objective function here

double objective(double x[]);

double  objective(double x[])
{
	int i, j, k;
	double fit, sumSCH;

	fit = 0.0;

#ifdef ellip
	// Ellipsoidal function
	for(j=0;j<MAXV;j++)
		fit+=((j+1)*(x[j]*x[j]));
#endif

#ifdef schwefel
	// Schwefel's function
	for(j=0; j<MAXV; j++)
	{
		for(i=0,sumSCH=0.0; i<j; i++)
			sumSCH += x[i];
		fit += sumSCH * sumSCH;
	}
#endif

#ifdef rosen
	// Rosenbrock's function
	for (j = 0; j < MAXV - 1; j++)
	{
		fit += 100.0*(x[j] * x[j] - x[j + 1])*(x[j] * x[j] - x[j + 1]) + (x[j] - 1.0)*(x[j] - 1.0);
	}
#endif

	return(fit);
}
