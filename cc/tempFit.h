#ifndef __TEMPFIT_H_INCLUDED__
#define __TEMPFIT_H_INCLUDED__

// -------- necessary includes
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include "fitsio.h"


// -------- namespaces
using namespace std;


// -------- input class
class tfInput {

 public:
  int nband, ntemp;
  string path, infile;
  string dpath, tpath, mpath; // paths for data, templates, and mask
  string mname; // mask file name
  vector<string> dnames, tnames; // data and template file names

  tfInput(string, string);
};


// -------- data class
class tfData {

 public:
  int nside, nband;
  vector<vector<float> > maps;

  tfData(tfInput);
};


// -------- mask class
class tfMask {

 public:
  vector<int> map;

  tfMask(tfInput, tfData);
};


// -------- template class
class tfTmpl {

 public:
  int nside, ntmpl;
  vector<vector<float> > maps;

  tfTmpl(tfInput);
};


// -------- function declarations
void matrixMultiply(vector<vector<float> >, vector<vector<float> >, 
		    vector<vector<float> > &);


#endif
