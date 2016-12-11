
//------------------------------------------GENETIC ALGORITHM  -----------------------------------//
//Representation : Binary
//Fitness Funtion : x^3 (x is value of binary)
//Crossover : single point
//Mutation : Bit Flipping
//------------------------------------------------------------------------------------------------//

#include<bits/stdc++.h>
using namespace std;
#define chro_len 5

double convStr(string s){
	
	int pro = 1;
	double ret = 0.00;
	for(int i = s.size() - 1;i >= 0;i--){
		if(s[i] == '1')
			ret += pro;
		pro <<= 1;
	}
	return ret;
}

int main(){
	//freopen("output.txt","w",stdout);
	double mut_prob = 0.2500;
	int tot_gen = 3, pop_sz = 5;
	//generate initial population
	srand ( time(NULL) );	//initialize random seed:
	vector<string> vc;
	string s;
	
	for(int i = 0;i < pop_sz;i++){
		s = "";
		for(int j = 0;j < chro_len;j++){
			
			int random = rand() % 2;
			if(random)	
				s += "1";
			else
				s += "0";
		}
		vc.push_back(s);
	}
	
	cout << "The initially generated population and their corresponding phenotipic value\n\n";
	
	for(int i = 0;i < pop_sz;i++)
		cout << vc[i] << "   --------->    " << convStr(vc[i]) << endl;
	
	while(tot_gen--){
		
		cout << "\n\n";
		//---------------------------------------------------------------------------------------------
		//compute fitness
		cout << "Below are the fitness values:\n\n";
		double fitness[pop_sz + 10], sum = 0,maxxx = 0;
		for(int i = 0;i < pop_sz;i++){
			
			double tt = convStr(vc[i]);
			fitness[i] = tt*tt*tt;
			sum += fitness[i];
			maxxx = max(maxxx,fitness[i]);
			cout << vc[i] << "     ----->  " << fitness[i]<<endl;
		}
		cout << "\n\n";
		//---------------------------------------------------------------------------------------------
		//Selection by fitness proportionate
		double avg = sum / pop_sz;
		int exp[pop_sz + 10];
		cout<<"Expected counts are:\n\n";
		for(int i = 0;i < pop_sz;i++)		//Calculating expected count
			exp[i] = round(fitness[i] / avg), cout << exp[i] << endl;
		
		vector<string> matingP;
		
		while(1){							//inserting in mating pool
			
			bool chk=true;
			for(int i = 0;i < pop_sz;i++){
				if(matingP.size() == pop_sz)	break;//if more
				if(exp[i]){
					matingP.push_back(vc[i]);
					exp[i]--;
					chk = false;
				}
			}
			if(chk || matingP.size() == pop_sz/*if more*/)	break;	
		}
		cout << "Selected chromosomes are(for mating pool):\n\n";
		int mat = matingP.size();
		for(int i = 0;i < mat;i++)
			cout << matingP[i]<<endl;
			
		cout << "\n\n";
		//-----------------------------------------------------------------------------
		//Crossover single point and generating offsprings	
		vector<string> off;
		for(int i = 0;i < mat;i += 2){
			
			if(i == mat - 1)
				off.push_back(matingP[i]);
			
			else{
				string s1,s2;
				int pnt = rand() % chro_len;		//random point
				for(int j = 0; j < chro_len;j++){
					if(j <= pnt)
						s1 += matingP[i][j];
					else
						s1 += matingP[i + 1][j];
				}
				for(int j = 0; j < chro_len;j++){
					if(j <= pnt)
						s2 += matingP[i + 1][j];
					else
						s2 += matingP[i][j];
				}
				off.push_back(s1);
				off.push_back(s2);
			}
		}
		cout << "Generated offsprings:\n\n";
		for(int i = 0; i < off.size();i++)
			cout << off[i]<<endl;
			  
			  
		cout << "\n\n"; 
		//---------------------------------------------------------
		//Mutation
		for(int i = 0; i < off.size();i++){
			
			for(int j = 0;j < chro_len;j++){
				
				double prob = (rand() % 100 + 1) / 100.00;	//random number b/w 0 to 1 for each
				
				if(prob < mut_prob){
				
					if(off[i][j] == '1')	off[i][j] = '0';
					else	off[i][j] = '1';
				}
			}
		}
		cout << "After Mutation:\n\n";
		for(int i = 0; i < off.size();i++){
			int tt = convStr(off[i]);
			cout << off[i]<< " --------> " << tt*tt*tt  << endl;
		}
		if(off.size() < pop_sz){	//if less in offspring
			int ii = off.size();
			while(off.size() < pop_sz)
				off.push_back(vc[ii++]);
		}
		cout << "\n\n-----------------------------------------------------------------------------------------------\n\n";
		//continue
		cout << "Now this is the new population:\n\n";
		for(int i = 0; i < off.size();i++)
			cout << off[i]<<endl, vc[i] = off[i];
		cout << "\n\n\n";
	}
}
 
