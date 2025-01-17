struct Producto
{
    char nombre[50];
    int cantidad;
    float precio;
};

struct Factura
{
    char nombre[50];
    int cedula;
    int cantidadProductos;
    float total;
    struct Producto productos[5];
};

int findFacturaByCedula();
void createFactura();
void readFacturas();
void editFactura(int cedula);
void deleteFactura(int cedula);
void leerCadena(char *cadena, int tam);
void Save(struct Factura *factura);
void imprimirFacturas(struct Factura factura);
void imprimirDetalleFactura(struct Factura factura);




