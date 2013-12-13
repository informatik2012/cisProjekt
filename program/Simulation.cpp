#include "Simulation.hpp"

	    // Calculate the potential energy. 
		// This is a Lennard-Jones potential: 
		// Argument: 1/r^2. 
		static double Simulation::potential_1r2(double r2)
		{
			double r6=r2*r2*r2;
			return(4.0*r6*(r6-1.0));
		}
		// Argument: r
		// Note: The min of the potential is at r=1.1225. 
		static double Simulation::potential(double r)
		{  return(potential_1r2(1.0/(r*r)));  }
		
		// Calc 1/|r| * \partial V(|r|) / \partial |r|: 
		// Argument: 1/r^2. 
		static double Simulation::potentialD_1r2(double r2)
		{
			double r6=r2*r2*r2;
			return(48.0*r6*r2*(0.5-r6));
		}
		
		// Calc r+dv/dr = -24*(2*r^-12-r^-6). Argument r. 
		static double Simulation::potential_w(double r)
		{
			double r6=1.0/POW3(SQR(r));  // r^-6   problem problem?! pow3 und sqr?
			return(24*r6*(1-2*r6));
		}

void Simulation::SimulationStep()
{
	for (std::vector<partikel>::iterator i = .begin(); i != .end(); ++i)
	 {
	 	std::vector<position> ParticlesState::getNeightbours(GridPoint position, long r_c)
	 	for (int i = 0; i < 3; ++i)
	 	{
	 		position[i] = position[i+x];  // neue pos
	 	}
	 }
	 return neuesPartikelarray;
};