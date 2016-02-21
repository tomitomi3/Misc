//This routine is used to sort a subpopulation by fitness
// Here the subpopulaton is Kids + Parents (family)
void sort();

void sort()

{
	int i, j, temp;
	double dbest;

	for (i = 0; i < (kids + family); i++) list[i] = i;

	if (MINIMIZE)
		for (i = 0; i < (kids + family - 1); i++)
		{
			dbest = newpop[list[i]].obj;
			for (j = i + 1; j < (kids + family); j++)
			{
				if (newpop[list[j]].obj < dbest)
				{
					dbest = newpop[list[j]].obj;
					temp = list[j];
					list[j] = list[i];
					list[i] = temp;
				}
			}
		}
	else
		for (i = 0; i < (kids + family - 1); i++)
		{
			dbest = newpop[list[i]].obj;
			for (j = i + 1; j < (kids + family); j++)
			{
				if (newpop[list[j]].obj > dbest)
				{
					dbest = newpop[list[j]].obj;
					temp = list[j];
					list[j] = list[i];
					list[i] = temp;
				}
			}
		}
}

