#include <iostream>
#include <list>

#include <options.hpp>
#include <pixel.hpp>
#include <bitmap.hpp>

#include <dithering.hpp>

////////////////////////////////////////
int main(int argc, char * argv[])
 {
  // des trucs peuvent lancer
  // des exceptions (mauvais
  // paramètres, etc.)
  try
   {
    options opt(argc,argv);

    switch (first_of({ opt.help,
                       opt.version,
                       opt.dithering==dithering_type::floyd_steinberg,
                       opt.dithering==dithering_type::methode_1, // changer le nom ici
                       opt.dithering==dithering_type::methode_2, // changer le nom ici
                      }))
     {
      case 0: options::show_help(); break;
      case 1: options::show_version(); break;

      case 2: quantize_and_dither(opt.input, opt.output,floyd_steinberg_matrix); break;
      //case 3: quantize_and_dither(opt.input, opt.output,votre_matrice 1 ici); break;
      //case 4: quantize_and_dither(opt.input, opt.output,votre_matrice 2 ici); break;
     }
   }

  catch (boost::program_options::error & this_exception)
   {
    std::cerr << this_exception.what() << std::endl;
    return 1;
   }
  return 0;
 }
