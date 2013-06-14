#include "temple.h"

tfMask::tfMask(tfInput input, tfData data) {

  // -------- intialize the mask
  int npix = 12*data.nside*data.nside;
  map.resize(npix);

  // -------- in case of no mask name, set mask to ones
  if (input.mname.size()==0) {
    ind.resize(npix);

    for (int ipix=0;ipix<npix;ipix++) {
      map[ipix] = 1;
      ind[ipix] = ipix;
    }
    return;
  }

  // -------- utilities
  fitsfile *fptr;
  int status=0, anynul, dumint;
  int * dummap;
  string infile;

  dummap = new int [npix];

  // -------- read in mask map
  cout << "READMASK: Reading map from:\n";
  cout << "READMASK:   " << input.mpath << endl;
  cout << "READMASK:     " << input.mname << endl;

  infile = input.mpath + input.mname;

  if (fits_open_file(&fptr, infile.c_str(), READONLY, &status)) {
    fits_report_error(stderr, status);
    exit(status);
  }
  if (fits_read_img(fptr, TINT, 1, npix, 0, dummap, &anynul, &status)) {
    fits_report_error(stderr, status);
    exit(status);
  }
  if (fits_close_file(fptr,&status)) {
    fits_report_error(stderr,status);
    exit(status);
  }

  for (int ipix=0;ipix<npix;ipix++) {
    dumint    = dummap[ipix];
    map[ipix] = dumint;

    if (dumint) ind.push_back(ipix);
  }

  // -------- clean up
  delete dummap;

}
