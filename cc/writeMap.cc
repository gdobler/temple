#include "temple.h"

void writeMap(vector<float> map, string filename) {

  // -------- check file name is not in this directory
  size_t found = filename.find("/");

  if (found==string::npos) {
    cout << "WRITEMAP: ERROR - output must not be in the run directory.\n";
    cout << "WRITEMAP:   exiting with nothing written...\n";
    return;
  }


  // -------- utilities
  int status=0, npix=(int)map.size();
  long naxes[1] = {npix};
  float * dummap;
  fitsfile *fptr;

  dummap = new float [npix];

  for (int ipix=0;ipix<npix;++ipix) dummap[ipix] = map[ipix];


  // -------- open the file for writing
  if (fits_create_file(&fptr, filename.c_str(), &status)) {
    fits_report_error(stderr,status);
    exit(status);
  }

  cout << "WRITEMAP: Writing to file " << filename << endl;


  // -------- write data to fits file
  if (fits_create_img(fptr, TYPE_IMG, 1, naxes, &status)) {
    fits_report_error(stderr,status);
    exit(status);
  }
  if (fits_write_img(fptr, TTYPE, 1, npix, dummap, &status)) {
    fits_report_error(stderr,status);
    exit(status);
  }


  // -------- close file
  if (fits_close_file(fptr,&status)) {
    fits_report_error(stderr,status);
    exit(status);
  }


  // -------- clean up dynamic arrays
  delete dummap;



  return;
}
