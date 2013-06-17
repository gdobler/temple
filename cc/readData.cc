#include "temple.h"

tfData::tfData(tfInput input) {

  // -------- utilities
  fitsfile *fptr;
  char card[FLEN_CARD];
  int status=0, npix=0, anynul;
  float * dummap;
  string infile;


  // -------- set the number of bands
  nband = input.dnames.size();
  maps.resize(nband);


  // -------- get the number of pixels from first data map
  infile = input.dpath + input.dnames[0];

  if (fits_open_file(&fptr, infile.c_str(), READONLY, &status)) {
    fits_report_error(stderr, status);
    exit(status);
  }
  if (fits_read_key(fptr, TLONG, "NAXIS1", &npix, card, &status)) {
    fits_report_error(stderr, status);
    exit(status);
  }
  if (fits_close_file(fptr, &status)) {
    fits_report_error(stderr, status);
    exit(status);
  }


  // -------- set Nside, size maps, and read in data vectors
  nside  = sqrt(npix/12);
  dummap = new float [npix];

  cout << "READDATA: Reading data from:\n";
  cout << "READDATA:   " << input.dpath << endl;

  for (int iband=0; iband<nband; iband++) {
    maps[iband].resize(npix);

    infile = input.dpath + input.dnames[iband];

    cout << "READDATA:     " << input.dnames[iband] << endl;

    if (fits_open_file(&fptr, infile.c_str(), READONLY, &status)) {
      fits_report_error(stderr, status);
      exit(status);
    }
    if (fits_read_img(fptr, TTYPE, 1, npix, 0, dummap, &anynul, &status)) {
      fits_report_error(stderr, status);
      exit(status);
    }
    if (fits_close_file(fptr,&status)) {
      fits_report_error(stderr,status);
      exit(status);
    }

    for (int ipix=0;ipix<npix;ipix++)
      maps[iband][ipix] = dummap[ipix];
  }


  // -------- clean up dynamic arrays
  delete dummap;

}
