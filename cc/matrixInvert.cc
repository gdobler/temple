#include "temple.h"

void matrixInvert(vector<vector<float> > mat, vector<vector<float> >& inv){

  // -------- check for square matrix
  int nrow=mat.size(), ncol=mat[0].size();

  if (nrow!=ncol) {
    cout << "MATRIXINVERT: matrix is not square and cannot be inverted!!!\n";
    cout << "MATRIXINVERT:   (nrow,ncol) = (" << nrow << "," << ncol << ")\n";
    exit(EXIT_FAILURE);
  }


  // -------- set inverse to appropriate size and initialize as identity
  inv.resize(nrow);
  for (int irow=0;irow<nrow;irow++) {
    inv[irow].resize(ncol,0.0);
    inv[irow][irow] = 1.0;
  }


  // -------- utilities
  int irow,jrow,icol;
  float oolead, r;


  // -------- invert
  for (irow=0;irow<nrow;irow++) {

      oolead = 1.0/mat[irow][irow];

      // divide row by leading value if not 1.0
      if (fabs(oolead-1.0)>1e-5) {
	for(icol=0;icol<ncol;icol++) {
	  mat[irow][icol] *= oolead;
	  inv[irow][icol] *= oolead;
	}
      }

      // set all rows above and below to 0.0
      for(jrow=0;jrow<nrow;jrow++) {
	if ((jrow==irow) || (fabs(mat[jrow][irow])<1e-5))
	  continue; // row is finished

	r = mat[jrow][irow];

	for (icol=0;icol<ncol;icol++) {
	  mat[jrow][icol] -= r*mat[irow][icol];
	  inv[jrow][icol] -= r*inv[irow][icol];
	}
      }

  }

  return;
}
