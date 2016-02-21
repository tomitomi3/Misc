//This routine is used to find the parents to be replaced and replace them by good individuals

void my_family();
void find_parents();
void rep_parents();

void my_family()   //here a random family (1 or 2) of parents is created who would be replaced by good individuals
{
	int i, j, index;
	int swp;
	double u;

	for (i = 0; i < MAXP; i++)
		mom[i] = i;

	for (i = 0; i<family; i++)
	{
		u = randomperc();
		index = (u*(MAXP - i)) + i;
		if (index>(MAXP - 1)) index = MAXP - 1;
		swp = mom[index];
		mom[index] = mom[i];
		mom[i] = swp;
	}
}

void find_parents()   //here the parents to be replaced are added to the temporary subpopulation to assess their goodness against the new solutions formed which will be the basis of whether they should be kept or not 
{
	int i, j, k;
	double u, v;

	my_family();

	for (j = 0; j < family; j++)
	{
		for (i = 0; i < MAXV; i++)
			newpop[kids + j].vari[i] = oldpop[mom[j]].vari[i];

		newpop[kids + j].obj = objective(newpop[kids + j].vari);
	}
}

void rep_parents()   //here the best (1 or 2) individuals replace the family of parents
{
	int i, j;
	for (j = 0; j < family; j++)
	{
		for (i = 0; i < MAXV; i++)
			oldpop[mom[j]].vari[i] = newpop[list[j]].vari[i];

		oldpop[mom[j]].obj = objective(oldpop[mom[j]].vari);
	}
}

