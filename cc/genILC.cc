#include "temple.h"

vector<float> genILC(tfData data, tfMask mask, int refband) {

  // -------- utilities
  int npix=mask.map.size(), nband=data.nband, iband, jband, ipix;
  float sum=0.0;

  vector<float> ilc(npix,0.0), ccvec(nband,0.0), zeta(nband-1,0.0);

  vector<vector<float> > ccmat(nband, vector<float> (nband, 0.0)), 
    Pmat(nband, vector<float> (npix, 1.0)), 
    ccinv;


  // -------- fill the P matrix
  int itr=0;
  for (iband=0;iband<nband;++iband) {
    if (iband==refband) continue;
    for (ipix=0;ipix<npix;++ipix)
      Pmat[itr][ipix] = data.maps[iband][ipix] - data.maps[refband][ipix];
    ++itr;
  }


  // -------- make the cross correlation matrix
  for (iband=0;iband<nband;iband++) {
    for (jband=0;jband<nband;jband++,sum=0.0) {
      for (int i=0;i<(int)mask.ind.size();i++)
	sum += Pmat[iband][mask.ind[i]]*Pmat[jband][mask.ind[i]];

      ccmat[iband][jband] = sum;
    }
  }


  // -------- make the cross correlation vector with the reference band
  for (iband=0;iband<nband;iband++,sum=0.0) {
    for (int i=0;i<(int)mask.ind.size();i++)
      sum -= Pmat[iband][mask.ind[i]]*data.maps[refband][mask.ind[i]];

    ccvec[iband] = sum;
  }


  // -------- invert the cc matrix and multiply with the cc vector
  matrixInvert(ccmat,ccinv);

  for (iband=0;iband<nband;iband++,sum=0.0) {
    for (jband=0;jband<nband;jband++)
      sum += ccinv[iband][jband]*ccvec[jband];

    zeta[iband] = sum;
  }

  int i,j;
  for (i=0;i<nband;++i) cout << ccvec[i] << "  " << endl;
  for (i=0;i<nband;++i) {
    cout << endl;
    for (j=0;j<nband;++j)
      cout << ccinv[i][j] << "\t";
  }
  cout << endl;

  for (int i=0;i<nband;i++) cout << "zeta[" << i << "] = " << zeta[i] << endl;
  // -------- create the ilc
  for (ipix=0;ipix<npix;ipix++) ilc[ipix] = data.maps[refband][ipix];

  for (iband=0;iband<nband-1;iband++) {
    for (ipix=0;ipix<npix;ipix++)
      ilc[ipix] += zeta[iband]*(Pmat[iband][ipix]-data.maps[iband][ipix]);
  }

  for (ipix=0;ipix<npix;ipix++) ilc[ipix] = zeta[nband-1]*Pmat[nband-1][ipix];
  
  return(ilc);
}
