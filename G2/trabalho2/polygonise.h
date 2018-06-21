typedef struct {
   double x,y,z;
} XYZ;

typedef struct {
   XYZ p[3];
} TRIANGLE;

typedef struct {
   XYZ p[8];
   double val[8];
} GRIDCELL;

int Polygonise(GRIDCELL grid,double isolevel,TRIANGLE *triangles);