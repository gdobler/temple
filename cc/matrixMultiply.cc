#include "temple.h"

void matrixMultiply(vector<vector<float> > matA, vector<vector<float> > matB, 
		    vector<vector<float> >& prod) {

  // -------- get the sizes of the matrices
  int nrowA=matA.size(), ncolA=matA[0].size();
  int nrowB=matB.size(), ncolB=matB[0].size();


  // -------- make sure dimensions are compatible
  if (ncolA!=nrowB) {
    cout << "MATRIXMULTIPLY: Matrics have incompatible dimensions!!!" << endl;
    cout << "MATRIXMULTIPLY:   dimen matA = " << nrowA << "x" << ncolA << endl;
    cout << "MATRIXMULTIPLY:   dimen matB = " << nrowB << "x" << ncolB << endl;
    exit(EXIT_FAILURE);
  }


  // -------- set product to appropriate size
  prod.resize(nrowA);
  for (int irow=0;irow<nrowA;irow++) prod[irow].resize(ncolB,0.0);


  // -------- perform the matrix multiplication
  for (int i=0;i<nrowA;i++)
    for (int j=0;j<ncolB;j++)
      for (int k=0;k<ncolA;k++)
	prod[i][j] += matA[i][k]*matB[k][j];

  return;
}
