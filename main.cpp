#include <iostream>
#include <fstream>
#define DIM_PRODUCTO 6
#define DIM_COLOR 3
using namespace std;

void inicializar_estructuras(int producto[], int producto_color[][DIM_COLOR], int contadores[][DIM_COLOR], float promedios[][DIM_COLOR])
{
	for (int i=0;i<DIM_PRODUCTO;i++) {
		producto[i] = 0;
	}
	for (int i=0;i<DIM_PRODUCTO;i++){
        for (int j=0;j<DIM_COLOR;j++){
            producto_color[i][j] = 0;
        }
	}
    for (int i=0;i<DIM_PRODUCTO;i++){
        for (int j=0;j<DIM_COLOR;j++){
            contadores[i][j] = 0;
        }
	}
	for (int i=0;i<DIM_PRODUCTO;i++){
        for (int j=0;j<DIM_COLOR;j++){
           promedios[i][j] = 0;
        }
	}
}

void definir_estructuras(istream &archilec_productos, int producto_color[][DIM_COLOR], int producto[],
						 int contadores[][DIM_COLOR],float promedios[][DIM_COLOR])
{
    int product, color, produccion;
    while (archilec_productos >> product >> color >> produccion)
    {
    	producto_color[product][color] += produccion;
    	contadores[product][color] ++;
    	promedios[product][color] = producto_color[product][color] / contadores[product][color];
        producto[product] += produccion;
    }
}

int maximo(int producto_color[][DIM_COLOR])
{
    int max=0;
    for (int i=0;i<DIM_PRODUCTO;i++){
        for (int j=0;j<DIM_COLOR;j++){
            if (producto_color[i][j]>max){
                max = producto_color[i][j];
            }
        }
    }
    return max;
}

void punto_uno(string nombres[], string colores[], int producto_color[][DIM_COLOR])
{
	int prod, color;
	for (int i=0;i<DIM_PRODUCTO;i++){
		for (int j=0;j<DIM_COLOR;j++){
			if (producto_color[i][j] == maximo(producto_color)){
				prod = i;
				color = j;
			}
		}
	}
	cout<<"1. "<<nombres[prod]<<" en color "<<colores[color]<<" es el producto mas producido con "<<maximo(producto_color)<<" unidades"<<endl;
}

int minimo(int producto[])
{
    int min;
    for (int i=0;i<DIM_PRODUCTO;i++){
        if (producto[i]<min || i==0){
            min = producto[i];
        }
    }
    return min;
}

void punto_dos(string nombres[], int producto[])
{
	int prod;
	for (int i=0;i<DIM_PRODUCTO;i++){
		if (producto[i] == minimo(producto)){
			prod = i;
		}
	}
	cout<<"2. "<<nombres[prod]<<" es el producto que menos se produjo, con "<<minimo(producto)<<" unidades"<<endl;
}

float promedio(float promedios[][DIM_COLOR])
{
    int max=0;
    for (int i=0;i<DIM_PRODUCTO;i++){
        for (int j=0;j<DIM_COLOR;j++){
            if (promedios[i][j]>max){
                max = promedios[i][j];
            }
        }
    }
    return max;
}

void punto_tres(string nombres[], string colores[], float promedios[][DIM_COLOR])
{
	int prod, color;
	for (int i=0;i<DIM_PRODUCTO;i++){
		for (int j=0;j<DIM_COLOR;j++){
			if (promedios[i][j] == promedio(promedios)){
				prod = i;
				color = j;
			}
		}
	}
	cout<<"3. "<<nombres[prod]<<" de color "<<colores[color]<<" tuvo el mayor promedio de unidades por lote, con un promedio de "<<promedio(promedios);
}
int main()
{
	string nombres[DIM_PRODUCTO]; // vector en donde se van a guardar los primeros 6 elementos de archivo nombres
	string colores[DIM_COLOR]; // vector en donde se van a guardar los ultimos 3 elementos de archivo nombres
    int producto_color[DIM_PRODUCTO][DIM_COLOR];// matriz de 6x3 donde se guarda la cantidad producida para la combinaci�n producto-color
    int producto[DIM_PRODUCTO]; // vector de 6 elemenetos donde se guarda la cantidad producida de los productos
    int contadores[DIM_PRODUCTO][DIM_COLOR];// matriz de 6x3 donde se guarda los contadores de la combinacion producto-color para sacar el promedio
	float promedios[DIM_PRODUCTO][DIM_COLOR];// matriz de 6x3 donde se guarda el promedio de produccion por cada porducto-color

    ifstream archilec_nombres;
	archilec_nombres.open("datosG04E15nombres.txt");
	if (!archilec_nombres){
		cout<<"No se pudo abrir el archivo";
		return 1;
	}
	string linea;
	for (int i=0;i<DIM_PRODUCTO;i++)
		if (archilec_nombres >> linea)
			nombres[i] = linea;
	for (int i=0;i<DIM_COLOR;i++)
		if (archilec_nombres >> linea)
			colores[i] = linea;
	archilec_nombres.close();

    ifstream archilec_productos;
	archilec_productos.open("datosG04E15producc.txt");
	if (!archilec_productos){
		cout<<"No se puedo abrir el producto";
		return 1;
        }
	inicializar_estructuras(producto,producto_color,contadores,promedios);
	definir_estructuras(archilec_productos,producto_color,producto,contadores,promedios);
	punto_uno(nombres,colores,producto_color);
    punto_dos(nombres,producto);
    punto_tres(nombres,colores,promedios);

	archilec_productos.close();
	return 0;
}
