// Space time
#include <TMB.hpp>
template<class Type>
Type objective_function<Type>::operator() ()
{
	  DATA_VECTOR( Y_t );
	  // Parameters
	  PARAMETER( a );
	  PARAMETER( lnsig_S );
	  PARAMETER( lnsig_y );
	  PARAMETER_VECTOR( u );

	  Type sig_S = exp(lnsig_S);
	  Type sig_y = exp(lnsig_y);

  	Type jnll = 0;
		int nt = Y_t.size();

  	for( int i=1; i<nt; i++){
			Type m = a*u[i-1] ;    //linear model
			jnll -= dnorm(u(i),m,sig_S,true);
		}
  	for( int i=0; i<nt; i++){
			jnll -= dnorm(Y_t(i),u(i),sig_y,true);
		}

	// reports
	ADREPORT(a)
	ADREPORT(lnsig_S)
	ADREPORT(lnsig_y)

  return jnll;

}
