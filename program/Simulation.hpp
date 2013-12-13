//  [ Lennard-Jones potential: V(r) = V0 * (r/sigma)^-12 - (r/sigma)^-6 ]
// -------------------------------------------
//  sigma   -> where potential is 0
//  epsilon  -> the minimum of the potential
//  m     -> 1       (mass)
//  x,y,z -> (x,y,z) / sigma
//  t     -> t * sqrt(eps/(m*sigma^2))
//  rho   -> rho * sigma^3
//  v     -> v * sqrt(m/epsilon)   (speed)
//  F     -> F * sigma/epsilon
//  E     -> E / epsilon
//  T     -> T * k_B/epsilon
//  V0    -> 4 
// --------------------------------------------

class Simulation
{
public:
	Simulation(partikelArray);
	~Simulation();
	void SimulationStep();
	static double potential_1r2(double r2);
	static double potential(double r);
	static double potentialD_1r2(double r2);
	static double potential_w(double r);


private:
	long x;
	long r_c;    // cut-off distance
	long r_m;    // range where potential is minimum
	double epsilon, sigma;
		
		
	
};