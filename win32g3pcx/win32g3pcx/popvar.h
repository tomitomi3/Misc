//This routine is used to calculate the population mean, variance and other statistics..used only for study 


void popvar();

void popvar()
{
	int i, j, k;
	double u, v, w;
	double pop_mean[MAXV];

	for (i = 0; i < MAXV; i++)
		pop_mean[i] = 0.0;

	for (j = 0; j < MAXV; j++)
		for (i = 0; i < MAXP; i++)
			pop_mean[j] += oldpop[i].vari[j] / (double)MAXP;


	for (i = 0; i < MAXP; i++)
	{
		d_not[i] = 0.0;
		for (j = 0; j < MAXV; j++)
			d_not[i] += (oldpop[i].vari[j] - pop_mean[j])*(oldpop[i].vari[j] - pop_mean[j]);

		d_not[i] = sqrt(d_not[i]);
	}


	mean_d = var_d = 0.0;

	for (i = 0; i < MAXP; i++)
		mean_d += d_not[i];


	mean_d /= MAXP;

	dis_opt = 0.0;
	for (i = 0; i < MAXV; i++)
		dis_opt += (pop_mean[i] - 1.0)*(pop_mean[i] - 1.0);

	dis_opt = sqrt(dis_opt);

	for (i = 0; i < MAXP; i++)
		var_d += (d_not[i] - mean_d)*(d_not[i] - mean_d);

	var_d /= (double)MAXP;
	var_d = sqrt(var_d);


}

