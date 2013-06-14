#include "temple.h"

tfInput::tfInput(string path, string infile) {

  cout << "READINPUT: Reading input file " << path+infile << endl;

  // -------- read the input file
  FILE * fin;
  char buffer[100], seg[100];

  // open file
  fin = fopen((path+infile).c_str(),"r");

  // first the data path
  fgets(buffer, 100, fin);
  sscanf(buffer, "%s", seg);
  dpath = seg;

  // now the number of bands
  fgets(buffer, 100, fin);
  sscanf(buffer, "%d", &nband);

  // now the data map paths
  for (int iband=0; iband<nband; iband++) {
    fgets(buffer, 100, fin);
    sscanf(buffer, "%s", seg);
    dnames.push_back(seg);
  }

  // now a blank line
  fgets(buffer, 100, fin);

  // now the template path
  fgets(buffer, 100, fin);
  sscanf(buffer, "%s", seg);
  tpath = seg;

  // now the number of templates
  fgets(buffer, 100, fin);
  sscanf(buffer, "%d", &ntemp);

  // lastly the template file names
  for (int itemp=0; itemp<ntemp; itemp++) {
    fgets(buffer, 100, fin);
    sscanf(buffer, "%s", seg);
    tnames.push_back(seg);
  }

  // check for mask
  if (feof(fin)!=1) {
    fgets(buffer, 100, fin); // blank line
    fgets(buffer, 100, fin);
    sscanf(buffer, "%s", seg);
    mpath = seg;

    fgets(buffer, 100, fin);
    sscanf(buffer, "%s", seg);
    mname = seg;
  }

  // close the file
  fclose(fin);

}
