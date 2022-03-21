#ifndef __MODULE_OPTIONS__
#define __MODULE_OPTIONS__

#include <string>
#include <list>
#include <boost/program_options.hpp> // exceptions also

#include <dithering.hpp>

class options
 {
  public:

      bool verbose;
      bool help;
      bool version;

      bool compress;
      bool histogram;

      std::string input;
      std::string output;

      dithering_type dithering;

      static void show_help();
      static void show_version();

  options()
   : verbose(false),
     help(false),
     version(false),
     dithering(dithering_type::floyd_steinberg)
  {}

  options(int, const char * const[]);

  ~options()=default;
 };

size_t first_of(const std::list<bool> & l);

#endif
// __MODULE_OPTIONS__
