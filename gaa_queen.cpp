
//------------------------------------------8 QUEEN PROBLEM SIMULATED THROUGH GENETIC ALGORITHM-----------------------------------//


#include<bits/stdc++.h>
using namespace std;

#define PB push_back
#define MP make_pair

#define epsilon 2			//EPSILON value
#define pop_size 200		//POPULATION size

//calculating fitness function 1/(q(p) + Epsilon)
double fitness_calc(vector<int> a){
	
	double tot = 0;
	for(int i=0;i<8;i++)
		for(int j=i + 1;j<8;j++){
			
			if( abs(i + 1 - a[i]) == abs(j + 1 - a[j]) || i + 1 + a[i] == j + 1 + a[j] )
				tot++;
		}
	return 1.00 / (tot + epsilon);
}

int main(){
	freopen("output.txt","w",stdout);
	//----------generating initial population
	vector< pair< double, vector<int> > > popln;	//will store chromosomes and corresponding fitness values as pairs
	vector<int> temp;
	int tot_generation = 200;
	for(int i=1;i<=8;i++)		temp.PB(i);
	
	for(int i=0;i<pop_size;i++){
		
		random_shuffle( temp.begin(), temp.end() );	//using built in random generator
		popln.PB( MP(fitness_calc(temp) , temp));
	}
	cout<<"Initial population generated\n";
	for(int i=0;i<pop_size;i++) { for(int j = 0;j < 8;j++)	cout<<popln[i].second[j]<<" ";	cout<<endl; }	cout<<"\n\n\n";
	//----------------------------------------------------------------------------------------------------------------------------------------//
	
	while(tot_generation--){
		
		//----------SELECTION OF PARENTS THROUGH TOURNAMENT
		vector< vector<int> > selected;
	
		for(int i=1;i<=5;i++){		//tournament->best 2 out of random 5 and this repeated 5 times
			
			int bst = -1, scndbst = -1, bst_index = 0, scndbst_index = 0;
			
			for(int j=1;j<=5;j++){
				
				int random = rand() % pop_size;
				double fitns = popln[random].first;
				
				if( fitns > bst){
					scndbst = bst;
					bst = fitns;
					scndbst_index = bst_index;
					bst_index = random;
				}
				else if (fitns > scndbst){
					scndbst = fitns;
					scndbst_index = random;
				}
			}
			
			selected.PB(popln[bst_index].second);
			selected.PB(popln[scndbst_index].second);
		}
		cout<<"\n\nSelected Parents for crossover\n";
		for(int i=0;i<10;i++) { for(int j = 0;j < 8;j++)	cout<<selected[i][j]<<" ";	cout<<endl; }	cout<<"\n\n\n";
		//----------------------------------------------------------------------------------------------------------------------------------------//
		
		//----------APPLYING ORDER CROSSOVER
		int randm1, randm2;
		vector< vector<int> > offspring;
		vector<int> chld1, chld2;
		chld1.resize(8);
		chld2.resize(8);
		srand ( time(NULL) );	//initialize random seed:
		for(int i = 0;i < 10;i += 2){
			
			randm1 = rand() % 8;
			randm2 = rand() % 8;	//two random points for ORDER CORSSOVER
			if(randm1 > randm2)	swap(randm1, randm2);

			//1st child
			int chek[10] = {0};
			for(int j = randm1;j <= randm2;j++){
				chld1[j] = selected[i][j];
				chek[ selected[i][j] ] = 1;
			}
			int j = (randm2 + 1) % 8;
			int ptr = j;
			while(j != randm1){
				while(chek[selected[i + 1][ptr]] != 0)
					ptr = (ptr + 1) % 8;
				chld1[j] = selected[i + 1][ptr];
				j = (j + 1) % 8;
				ptr = (ptr + 1) % 8;
			}
			
			//2nd child
			memset(chek, 0 , sizeof(chek)); 
			for(int j = randm1;j <= randm2;j++){
				chld2[j] = selected[i + 1][j];
				chek[ selected[i + 1][j] ] = 1;
			}
			j = (randm2 + 1) % 8;
			ptr = j;
			while(j != randm1){
				while(chek[selected[i][ptr]] != 0)
					ptr = (ptr + 1) % 8;
				chld2[j] = selected[i][ptr];
				j = (j + 1) % 8;
				ptr = (ptr + 1) % 8;
			}
			offspring.PB(chld1);
			offspring.PB(chld2);
		}
		cout<<"Offspring generated after Order Crossover\n";
		for(int i=0;i<10;i++) { for(int j = 0;j < 8;j++)	cout<<offspring[i][j]<<" ";	cout<<endl; }	cout<<"\n\n\n";
		//----------------------------------------------------------------------------------------------------------------------------------------//
		
		//----------SWAP MUTATION
		double mut_prob = 0.800;	//mutation probablity
		for(int i = 0;i < 10;i++){
			
			double rnd = (rand() % 100) / 100.00;
			if(rnd > mut_prob){
				
				randm1 = rand() % 8;
				randm2 = rand() % 8;	//two random points
				swap( offspring[i][randm1], offspring[i][randm2] ); 
			}
		}
		cout<<"After Swap mutation\n";
		for(int i=0;i<10;i++) { for(int j = 0;j < 8;j++)	cout<<offspring[i][j]<<" ";	cout<<endl; }	cout<<"\n\n\n";
		//----------------------------------------------------------------------------------------------------------------------------------------//
		
		//----------SURVIVAL SELECTION  - REPLACING 10 WORST
		for(int i = 0;i < 10;i++)
			popln.PB(MP(fitness_calc(offspring[i]) , offspring[i]));		//insert new generated offsprings in poplulation
		
		sort(popln.begin(), popln.end());
		reverse(popln.begin(), popln.end());
		
		cout << "best and worst fitness values of this generation\n";
		printf("%.6lf %.6lf",popln[0].first, popln[pop_size - 1].first);
		//THIS GENERATION ENDS
		cout<<"\n\n\n\n-----NEW GENERATION------------------------------------------------------------------------------------------------------\n\n\n";
	}
	
}


