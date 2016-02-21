//This routine initializes the population (choose the variable bounds according to the need)

void initpop();

void initpop()
{
	double x, y, objbest;
	int i, j;

	randomize();  // starts the random number generator

	for (i = 0; i < MAXP; i++)
		oldpop[i].obj = 0.0;

	for (i = 0; i < MAXP; i++)
		for (j = 0; j < MAXV; j++)
		{
			x = randomperc();    // x is a uniform random number in (0,1)
			y = (-10.0) + (5.0*x); // the formula used is y=a+(b-a)*x if y should be a random number in (a,b)
			oldpop[i].vari[j] = y;
		}

	// solutions are evaluated and best id is computed
	oldpop[0].obj = objective(oldpop[0].vari);
	objbest = oldpop[0].obj;
	best = 0;
	for (i = 1; i<MAXP; i++)
	{
		oldpop[i].obj = objective(oldpop[i].vari);
		if (MINIMIZE * objbest > MINIMIZE * oldpop[i].obj)
		{
			objbest = oldpop[i].obj;
			best = i;
		}
	}
}

