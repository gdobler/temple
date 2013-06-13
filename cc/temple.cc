#include "tempFit.h"

vector<int> minmax(vector<int> vec) {
  int min=vec[0], max=vec[0];
  vector<int> vals(2);
  for (int i=1;i<(int)vec.size();i++) {
    if (vec[i]>max) {
      max = vec[i];
      continue;
    }
    if (vec[i]<min) {
      min=vec[i];
    }
  }

  vals[0] = min; vals[1]=max;

  return(vals);
}

int main(int argc, char * argv[]) {

  // -------- check for inputs
  if (argc<3 || argc>3) {
    cout << "\nCalling sequence is:\n  ./runFit path infile\n\n";
    return(-1);
  }


  // -------- grab the path and input file
  string path(argv[1]), infile(argv[2]);


  // -------- check if the path is / terminated
  char last[] = {*path.rbegin()};
  char slash[] = "/";
  if (strcmp(last,slash)!=0) path += "/";


  // -------- read the input file
  tfInput input (path, infile);


  // -------- read the data into the data matrix
  tfData data (input);


  // -------- read the templates into the template matrix
  tfTmpl tmpl (input);


  // -------- read the mask file
  tfMask mask (input, data);

  vector<int> mm = minmax(mask.map);
  cout << "mask = " << input.mpath + input.mname << endl;
  cout << "minmax(mask) = " << mm[0] << " " << mm[1] << endl;
  cout << "tmpl.maps[0].size() = " << tmpl.maps[0].size() << endl;
  cout << "tmpl[1][15349] = " << tmpl.maps[1][15349] << endl;




  /*
  int i,j;
  vector<vector<float> > matrixA, matrixB, myprod;

  matrixA.resize(4);
  for (i=0;i<4;i++) matrixA[i].resize(3);

  matrixB.resize(3);
  for (i=0;i<3;i++) matrixB[i].resize(5);


  for (i=0;i<4;i++) {
    for (j=0;j<3;j++) {
      matrixA[i][j] = (float)(i*j+i);
    }
  }
  for (i=0;i<3;i++) {
    for (j=0;j<5;j++) {
      matrixB[i][j] = (float)(i*j+i);
    }
  }

  matrixMultiply(matrixA,matrixB,myprod);

  cout << "MatrixA\n";
  for (i=0;i<4;i++) {
    for (j=0;j<3;j++)
      cout << matrixA[i][j] << "\t";
    cout << endl;
  }

  cout << endl;
  cout << "MatrixB\n";
  for (i=0;i<3;i++) {
    for (j=0;j<5;j++)
      cout << matrixB[i][j] << "\t";
    cout << endl;
  }

  cout << endl;
  cout << "product\n";
  for (i=0;i<4;i++) {
    for (j=0;j<5;j++)
      cout << myprod[i][j] << "\t";
    cout << endl;
  }
  */


  /*
  cout << "Second template is " << input.tnames[1] << endl;
  cout << "Let's read it..." << endl;

  fitsfile *fptr;
  char card[FLEN_CARD];
  int status=0, nkeys=0, ii;

  cout << "open...\n";
  fits_open_file(&fptr, (input.tpath + input.tnames[1]).c_str(), READONLY, 
		 &status);
  fits_get_hdrspace(fptr, &nkeys, NULL, &status);

  cout << "number of keys = " << nkeys << " printing them..." << endl;

  for (ii=1; ii<=nkeys; ii++) {
    fits_read_record(fptr, ii, card, &status);
    cout << card << endl;
  }

  cout << "done printing keys\n";

  int anynul, npix=512*512*12;
  float *pix0;
  pix0 = new float [npix];

  cout << "npix = " << npix << endl;

  cout << "reading image...\n";

  fits_read_img(fptr,TFLOAT,1,1,0,pix0,&anynul,&status);

  cout << "status of read image: " << status << endl;

  cout << "pix0[0] = " << pix0[0] << endl;

  cout << "close...\n";
  fits_close_file(fptr, &status);

  cout << "done...\n";
  */

  return(0);
}
