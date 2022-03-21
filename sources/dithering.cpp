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
     int indexX = 0;
     int indexY = 0;

     int erreurRouge = p.r - q.r;
     int erreurVert = p.g - q.g;
     int erreurBleu = p.b - q.b;

     for(int i=0;i<matrix_width;i++) {
       for(int j=0;j<matrix_height;i++) {

         if ((i<=2)&&(j==0)) {
           printf("blc\n");
         } else {
           if((((x+i-2<0)||x+i-2>w-1)) && (((y+j<0)||(y+j>h-1)))){
             printf("blc2 \n");
           } else {
             indexX = x+2-i;
             indexY = y+j;
             printf("x = %d : x+2-i = %d -> ",x,indexX);
             printf("y = %d : y+j = %d\n",y,indexY);
             int r = image.pixel(indexX,indexY).r + ((matrix.weights[i][j]/div)*erreurRouge);
             int g = image.pixel(indexX,indexY).g + ((matrix.weights[i][j]/div)*erreurVert);
             int b = image.pixel(indexX,indexY).b += ((matrix.weights[i][j]/div)*erreurBleu);
             if (r>255){
               image.pixel(indexX,indexY).r = 255;
             } else if (r<0){
               image.pixel(indexX,indexY).r = 0;
             } else {
               image.pixel(indexX,indexY).r = r;
             }

             if (g>255){
               image.pixel(indexX,indexY).g = 255;
             } else if (g<0){
               image.pixel(indexX,indexY).g = 0;
             } else {
               image.pixel(indexX,indexY).g = g;
             }

             if (b>255){
               image.pixel(indexX,indexY).b = 255;
             } else if (b<0){
               image.pixel(indexX,indexY).b = 0;
             } else {
               image.pixel(indexX,indexY).b = b;
             }
           }
         }
       }
     }
    }

  image.save(output_filename);
 }
