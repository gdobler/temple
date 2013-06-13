#include "tempFit.h"

tfTmpl::tfTmpl(tfInput input) {

  // -------- utilities
  fitsfile *fptr;
  char card[FLEN_CARD];
  int status=0, npix=0, anynul;
  float * dummap;
  string infile;


  // -------- set the number of bands
  ntmpl = input.tnames.size();
  maps.resize(ntmpl);


  // -------- get the number of pixels from first template map
  infile = input.tpath + input.tnames[0];

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


  // -------- set Nside, size maps, and read in template vectors
  nside  = sqrt(npix/12);
  dummap = new float [npix];

  cout << "READTEMPLATES: Reading templates from:\n";
  cout << "READTEMPLATES:   " << input.tpath << endl;

  for (int itmpl=0; itmpl<ntmpl; itmpl++) {
    maps[itmpl].resize(npix);

    infile = input.tpath + input.tnames[itmpl];

    cout << "READTEMPLATES:     " << input.tnames[itmpl] << endl;

    if (fits_open_file(&fptr, infile.c_str(), READONLY, &status)) {
      fits_report_error(stderr, status);
      exit(status);
    }
    if (fits_read_img(fptr, TFLOAT, 1, npix, 0, dummap, &anynul, &status)) {
      fits_report_error(stderr, status);
      exit(status);
    }
    if (fits_close_file(fptr,&status)) {
      fits_report_error(stderr,status);
      exit(status);
    }

    for (int ipix=0;ipix<npix;ipix++)
      maps[itmpl][ipix] = dummap[ipix];
  }


  // -------- clean up dynamic arrays
  delete dummap;

}
