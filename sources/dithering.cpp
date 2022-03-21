#include <algorithm> // min,max
#include <bitmap.hpp>
#include <dithering.hpp>


namespace { // anonymous namespace =

 // discrétisation assez crue à 6 bits bien croquants
 //
 // normalement on aurait un "vrai" algorithme
 // de discrétisation, mais ce n'est pas le but
 // ici
 //
 rgb24 quantize(const rgb24 & pixel)
  {
   return rgb24( pixel.r & 0b11000000,
                 pixel.g & 0b11000000,
                 pixel.b & 0b11000000);
  }


 uint8_t clip8(int x) { return std::max(0,std::min(255,x)); }

} // anonymous namespace



void quantize_and_dither(const std::string & input_filename,
                         const std::string & output_filename,
                         const diffusion_matrix & matrix)
 {
  // lance une exception si ça ne marche pas
  bitmap<rgb24> image(input_filename);

  size_t w=image.width();
  size_t h=image.height();
  size_t div=matrix.divisor; // de la matrice de diffusion

  for (size_t y=0;y<h;y++)
   for (size_t x=0;x<w;x++)
    {
     rgb24 p=image.pixel(x,y); // pixel original
     rgb24 q=quantize(p); // pixel discrétisé

     image.pixel(x,y)=q; // ce pixel

     // dispersons l'erreur

     // VOTRE CODE ICI
     int erreurRouge = p.r - q.r;
     int erreurVert = p.g - q.g;
     int erreurBleu = p.b - q.b;

     //printf("%d : %d : %d\n",erreurRouge,erreurVert,erreurBleu);

     for(size_t i = 0;i<5;i++){
       for (size_t j = 0; j < 3; j++) {
         size_t indexX = x-2+i;
         size_t indexY = y+j;

         if (indexX<w && indexX>=0) {
           if(indexY<h && indexY>=0) {
             //printf("rentre!!!\n");
             int poids = matrix.weights[j][i];
             int r = image.pixel(indexX,indexY).r + erreurRouge * poids/div;
             int g = image.pixel(indexX,indexY).g + erreurVert * poids/div;
             int b = image.pixel(indexX,indexY).b + erreurBleu * poids/div;

             //printf("%d,%d -> %d\n",i,j,facteur);

             if (r<=255) {
               if (r>=0) {
                 image.pixel(indexX,indexY).r = r;
               } else {
                 image.pixel(indexX,indexY).r = 0;
               }
             } else {
               image.pixel(indexX,indexY).r = 255;
             }

             if (b<=255) {
               if (b>=0) {
                 image.pixel(indexX,indexY).b = b;
               } else {
                 image.pixel(indexX,indexY).b = 0;
               }
             } else {
               image.pixel(indexX,indexY).b = 255;
             }

             if (g<=255) {
               if (g>=0) {
                 image.pixel(indexX,indexY).g = g;
               } else {
                 image.pixel(indexX,indexY).g = 0;
               }
             } else {
               image.pixel(indexX,indexY).g = 255;
             }

           } else {
             printf("y depasse\n");
           }
         } else {
           printf("x depasse\n");
         }



       } // fin for j
     } // fin for i


    }
    printf("fin\n");
  image.save(output_filename);
 }
