//This routine is the implementation of PCX operator and associated functions
//Do not change anything here without understanding the paper

double modu(double index[]); //gives modulus of an input vector
double innerprod(double ind1[], double ind2[]); //gives innerproduct of 2 input vectors
int generate_new(int h); //main routine here

int generate_new(int pass)
{
	int i, j, num, k;
	double Centroid[MAXV];
	double tempvar, tempsum, D_not, dist;
	double tempar1[MAXV];
	double tempar2[MAXV];
	double D[RandParent];
	double d[MAXV];
	double diff[RandParent][MAXV];
	double temp1, temp2, temp3;
	int temp;

	for (i = 0; i < MAXV; i++)
		Centroid[i] = 0.0;

	// centroid is calculated here
	for (i = 0; i < MAXV; i++)
	{
		for (j = 0; j < RandParent; j++)
			Centroid[i] += oldpop[arr1[j]].vari[i];

		Centroid[i] /= RandParent;
	}
	// calculate the distace (d) from centroid to the index parent arr1[0]  
	// also distance (diff) between index and other parents are computed
	for (j = 1; j < RandParent; j++)
	{
		for (i = 0; i < MAXV; i++)
		{
			if (j == 1)
				d[i] = Centroid[i] - oldpop[arr1[0]].vari[i];
			diff[j][i] = oldpop[arr1[j]].vari[i] - oldpop[arr1[0]].vari[i];
		}
		if (modu(diff[j]) < EPSILON)
		{
			printf("RUN=%d, Points are very close to each other. Quitting this run.\n", RUN);
			return (0);
		}
	}
	dist = modu(d); // modu calculates the magnitude of the vector

	if (dist < EPSILON)
	{
		printf("RUN=%d, Points are very close to each other. Quitting this run.\n", RUN);
		return (0);
	}

	// orthogonal directions are computed (see the paper)
	for (i = 1; i < RandParent; i++)
	{
		temp1 = innerprod(diff[i], d);
		temp2 = temp1 / (modu(diff[i])*dist);
		temp3 = 1.0 - pow(temp2, 2.0);
		D[i] = modu(diff[i])*sqrt(temp3);
	}

	D_not = 0;
	for (i = 1; i < RandParent; i++)
		D_not += D[i];

	D_not /= (RandParent - 1); //this is the average of the perpendicular distances from all other parents (minus the index parent) to the index vector

	// Next few steps compute the child, by starting with a random vector
	for (j = 0; j < MAXV; j++)
	{
		tempar1[j] = noise(0.0, (D_not*sigma_eta));
		tempar2[j] = tempar1[j];
	}

	for (j = 0; j < MAXV; j++)
	{
		tempar2[j] = tempar1[j] - ((innerprod(tempar1, d)*d[j]) / pow(dist, 2.0));
	}

	for (j = 0; j < MAXV; j++)
		tempar1[j] = tempar2[j];

	for (k = 0; k < MAXV; k++)
		newpop[pass].vari[k] = oldpop[arr1[0]].vari[k] + tempar1[k];

	tempvar = noise(0.0, (sigma_zeta));

	for (k = 0; k < MAXV; k++)
		newpop[pass].vari[k] += (tempvar*d[k]);

	// the child is included in the newpop and is evaluated
	newpop[pass].obj = objective(newpop[pass].vari);

	return (1);
}

// calculates the magnitude of a vector
double modu(double index[])
{
	int i;
	double sum, modul;

	sum = 0.0;
	for (i = 0; i < MAXV; i++)
		sum += (index[i] * index[i]);

	modul = sqrt(sum);
	return modul;
}

// calculates the inner product of two vectors
double innerprod(double ind1[], double ind2[])
{
	int i;
	double sum;

	sum = 0.0;

	for (i = 0; i < MAXV; i++)
		sum += (ind1[i] * ind2[i]);

	return sum;
}




