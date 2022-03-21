#ifndef __MODULE_DITHERING__
#define __MODULE_DITHERING__

#include <string>

enum class dithering_type { none,
                            floyd_steinberg,
                            methode_1, // votre nom de methode ici
                            methode_2  // votre nom de methode ici
                          };


//  _ _ X o o
//  o o o o o
//  o o o o o
const size_t matrix_width=5;
const size_t matrix_height=3;

typedef
struct
{
 size_t divisor;
 size_t weights[matrix_height][matrix_width]; // ajuster au besoin
} diffusion_matrix;

const diffusion_matrix floyd_steinberg_matrix =
 {
  16,
  {{0,0,0,7,0},
   {0,3,5,1,0},
   {0,0,0,0,0}}
 };

// vos matrices ici

void quantize_and_dither(const std::string & input_filename,
                         const std::string & output_filename,
                         const diffusion_matrix & matrix);

#endif
    // __MODULE_DITHERING__
