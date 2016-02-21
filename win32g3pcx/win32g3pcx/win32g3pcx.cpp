///********************************************************************************************
// ***                      Parent Centric Recombination using G3 Model                     ***
// ***                                                                                      ***
// ***                      Developed by Prof. K. Deb with his students                     ***
// ***                                                                                      ***
// *** Last Edited : 06.05.2002 
//     Last Edited : 10.07.2004 (nan problem is fixed)
// ***
// *** .....................................................................................***
//
//This is an implementation of PCX operator using G3 model. This is an unconstrained optimization algorithm which is suitable for real parameter optimization. This algorithm is based on the paper "A Computationally Efficient Evolutionary Algorithm for Real-Parameter
//   Optimization"  which can be downloaded from http://www.iitk.ac.in/kangal/pub.htm. For details of the algorithm please refer to the paper. 
//
//A brief help on usage of the code is as follows.
//
//Code your objective function to be optimized in "objective.h"
//"random.h" is the random number generator.
//Population is initialized in "initpop.h". Please change the initialization bounds according to the need. 
//"generate_new.h" contains the main routine of PCX and certain allied functions.
//"popvar.h" is used to calculate population mean and variances (only for study purposes).
//"sort.h" sorts a subpopulation by fitness
//"replace.h" contains routines to replace few parents by some good individuals.
//
//Input parameters have to be defined as below. It is advised that some of them not be changed (from what we have set them) for optimum performance of this algorithm. However others will have to be set according to individual requirement.
//
//Output shall be recorded in two files "1.out" which contains function evaluations versus best fitness (in the population) and "2.out" which contains details of the best solution obtained in each run. 
//
//Further description of functions and routines shall accompany them. 
//
//Please use this program for any purpose freely but make sure to refer to Prof K. Deb as the creater of PCX.*/ 
//
///********************************************************************************************/
///********************************************************************************************/

/*
Kanpur Genetic Algorithms Laboratory（http://www.iitk.ac.in/kangal/codes.shtml）
[G3PCX code in C]をVisualStudioで動作するように移植しました。
*/

// win32g3pcx.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"

#include <cstdio>
#include <cmath>
#include <stdlib.h>
#include <ctype.h>

//------------------------------------------------------------------------------------------- 

//Please try to keep the following parameters fixed at these values
#define EPSILON 1e-40

#define MAXFUN 1000000  //upper bound for number of function evaluations
// in case best fitness does'nt reach the desired value
#define MAXP 100        //population size (best if chosen between 100-150)
#define KIDS 2          //pool size of kids to be formed (use 2,3 or 4)
#define M 1             //M+2 is the number of parents participating in xover (use 1)
#define family 2        //number of parents to be replaced by good individuals(use 1 or 2)
#define sigma_zeta 0.1
#define sigma_eta 0.1   //variances used in PCX (best if fixed at these values)

//--------------------------------------------------------------------------//
//Change the following parameters according to the needs of the problem

#define MAXV 20         //number of variables of the problem
#define MAXRUN 10       //number of runs each with different random initial population
#define LIMIT 1e-20     //accuracy of best solution fitness desired
#define MINIMIZE 1      //set 1 to minimize and -1 to maximize
#define RandParent M+2     //number of parents participating in PCX 


#define rosen // choose the function: ellip, schwefel, rosen

/*functions declaration*/
void arrnd();

/*global variables declaration*/
struct pop{
	double vari[MAXV];
	double obj;
} oldpop[MAXP], newpop[KIDS + 2];


int count;
int arr1[MAXP];
double seed, basic_seed;
int list[KIDS + 2];
int mom[MAXP];
int RUN;
int gen, kids;
double d_not[MAXP];
double mean_d, var_d;
double dis_opt;
int best;

#include "objective.h"    //objective function
#include "random.h"       //random number generator
#include "initpop.h"      //population initialized
#include "generate_new.h" //generates a child from participating parents:PCX 
#include "popvar.h"       //population variance (used only for experiments)
#include "sort.h"         //subpopulation sorted by fitness 
#include "replace.h"      //good kids replace few parents


int _tmain(int argc, _TCHAR* argv[])
{
	int i, j, h;
	double u, v, w;
	double tempfit;
	FILE *fpt1, *fpt2;
	int tag;

	basic_seed = 0.4122;   //arbitrary choice
	kids = KIDS;

	gen = MAXFUN / kids;   //so that max number of function evaluations is fixed at 1 million set above

	fpt2 = fopen("2.out", "w");
	fprintf(fpt2, "             Initial Parameters \n\n");
	fprintf(fpt2, "Population size : %d\n", MAXP);
	fprintf(fpt2, "Number of variables : %d\n", MAXV);
	fprintf(fpt2, "Pool size of kids formed by PCX : %d\n", KIDS);
	fprintf(fpt2, "Number of parents participating in PCX : %d\n", RandParent);
	fprintf(fpt2, "Number of parents to be replaced by good kids : %d\n", family);
	fprintf(fpt2, "Sigma eta : %lf\n", sigma_eta);
	fprintf(fpt2, "Sigma zeta : %lf\n", sigma_zeta);
	fprintf(fpt2, "Best fitness required : %e\n", LIMIT);
	fprintf(fpt2, "Number of runs desired : %d\n\n", MAXRUN);
	fclose(fpt2);

	fpt1 = fopen("1.out", "w"); // func eval versus best fitness
	fpt2 = fopen("2.out", "a"); // best solution details

	for (RUN = 1; RUN <= MAXRUN; RUN++)
	{
		seed = basic_seed + (1.0 - basic_seed)*(double)(RUN - 1) / (double)MAXRUN;
		if (seed > 1.0) printf("\n warning!!! seed number exceeds 1.0");

		initpop();   //population initialized

		tempfit = oldpop[best].obj;
		for (count = 1; ((count <= gen) && (tempfit >= LIMIT)); count++)
		{
			arrnd();           //random array of parents to do PCX is formed
			for (i = 0; i < kids; i++)
			{
				tag = generate_new(i); //generate a child using PCX     
				if (tag == 0) break;
			}
			if (tag == 0) break;

			find_parents();  // form a pool from which a solution is to be 
			//   replaced by the created child

			sort();          // sort the kids+parents by fitness

			rep_parents();   // a chosen parent is replaced by the child

			//finding the best in the population 
			best = 0;
			tempfit = oldpop[0].obj;
			for (i = 1; i < MAXP; i++)
				if (MINIMIZE * oldpop[i].obj < MINIMIZE * tempfit)
				{
					tempfit = oldpop[i].obj;
					best = i;
				}

			// print out results after every 100 generations
			if (((count % 100) == 0) || (tempfit <= LIMIT))
				//fprintf(fpt1, "%d    %e\n", (count*kids), tempfit);
				printf("%d    %e\n", (count*kids), tempfit); //コンソールに出力
		}

		fprintf(fpt1, "\n");
		fprintf(fpt2, "\n             Run Number %d  \n", RUN);
		fprintf(fpt2, "Best solution obtained after %d function evaluations: \n", (count*kids));

		for (i = 0; i < MAXV; i++)
			fprintf(fpt2, "%e, ", oldpop[best].vari[i]);

		fprintf(fpt2, "\n\nFitness of this best solution: %e\n", tempfit);
		fprintf(fpt2, "\n");

	}
	fclose(fpt1);
	fclose(fpt2);
	return 0;
}

//random array of parents generator
void arrnd()
{
	int i, j, index;
	int swp;
	double u;
	int delta;

	for (i = 0; i < MAXP; i++)
		arr1[i] = i;

	swp = arr1[0];
	arr1[0] = arr1[best];  // best is always included as a parent and is the index parent
	// this can be changed for solving a generic problem
	arr1[best] = swp;

	for (i = 1; i<RandParent; i++)  // shuffle the other parents
	{
		u = randomperc();
		index = (u*(MAXP - i)) + i;

		if (index>(MAXP - 1)) index = MAXP - 1;
		swp = arr1[index];
		arr1[index] = arr1[i];
		arr1[i] = swp;
	}
}
