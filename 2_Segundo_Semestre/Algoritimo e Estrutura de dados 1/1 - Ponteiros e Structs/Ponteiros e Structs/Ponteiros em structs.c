#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
typedef struct{
    float raio, area, volume, diametro;
}esfera;

void atualizar_esfera (esfera *e, float a){
    float pi = 3.14;
    e->raio = a;
    e->area = 4.0 * pi * pow(a, 2.0);
    e->volume = (4.0/3.0) * pi * pow(a, 3.0);
    e->diametro = 2.0 * a;
}

int main (void){
    float raio;
    esfera e;

    scanf("%f", &raio);
    atualizar_esfera(&e, raio);

    printf("raio: %.1f \narea: %.1f \nvolume: %.1f \ndiametro: %.1f", e.raio, e.area, e.volume, e.diametro);
}
*/
typedef struct{
    float real, img, mod;
}complexo;

void atualizar_complexo(complexo *a, float real, float img){
    a->img = img;
    if (img>0){
        a->mod = sqrt(+img) + real;
    }else{
        a->mod = sqrt(-img) + real;
    }
    a->real = real;
}

int main (void){
    float real, img;
    complexo a;

    scanf("%f %f", &real, &img);
    atualizar_complexo(&a, real, img);

    printf("%.1f %.1fi \n%.1f", a.real, a.img, a.mod);
}



