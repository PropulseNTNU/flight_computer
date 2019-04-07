#include "kalman.h"
#include <BasicLinearAlgebra.h>
using namespace BLA;

//Initiates matrices needed in the kalman filter
Matrix<2,2> A_d;
Matrix<2,1> B_d;
const Matrix<1,2> C_d={1,0};
const Matrix<2,2> E_d={0.01, 0, 0, 0.01};
const Matrix<2,2> Q={90, 0 ,0 , 1000};
const float R=1; //Litt usikker på om R skal være en matrise eller en skalar. trodde egentlig den skulle være en matrise.
const Matrix<2,2> I={1,0,0,1};
Matrix<2,2> P_k_bar={1,0,0.1,0};
Matrix<2,1>x_hat_bar={1250,241};// skal være ganske nøyaktig utifra simuleringene
Matrix<2,1> x_hat;
Matrix<2,1> K_k;
Matrix<2,1> Z;
Matrix<2, 2> P_k;

//physical values
float drag=1;
float mass=21.58;


void kalman(float* estimates, float  altitude, float acceleration, float dt, float reference_v){
  //Updating variables
  //A_d={1,dt,0,1-dt*(drag*reference_v/mass)}; //bruker reference_v fordi vi har linearisert rundt referansepunktet. Usikker på om dette er riktig
  A_d={1,dt,0,1};//Lurer på om dette blir A_d fordi x2_dot er akselrasjon, og det kommer inn i B
  B_d={0,dt};

  //Computing kalman gain------------------------------------------------------
  K_k = P_k_bar*(~C_d)*((C_d*P_k_bar*(~C_d)+R).Inverse());// litt usikker på om K_k skal være matrise eller skalar
 
  //Update estimate with measurement-------------------------------------------
  Z = {altitude, 0};
  x_hat = x_hat_bar + K_k*(altitude -(x_hat_bar(0)));
 
  //updatet estimates----------------------------------------------------------
  estimates[0] = x_hat(0);
  estimates[1] = x_hat(1);
  //Compute  error  covariance  for  updated  estimate-------------------------
  P_k = (I - K_k*C_d)*P_k_bar *(~(I-K_k*C_d)) + K_k*R*(~K_k);
 
  //project ahead--------------------------------------------------------------
  x_hat_bar = A_d * x_hat + B_d * (acceleration);
  P_k_bar = A_d * P_k * (~A_d) + E_d*Q*(~E_d); //Mulig Q skal byttes ut med: E_d * Q * (~E_d); Uten pådrag blir det bare Q;
}
