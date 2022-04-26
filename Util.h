#pragma once
class Util
{
public:
	Util();
	~Util();

	double *nrvector(int nl, int nh);
	void free_vector(double* v, int nl, int nh);
	void spline(double x[], double y[], int n, double yp1, double ypn, double y2[]);
	void splint(double xa[], double ya[], double y2a[], int n, double x, double* y);
	void nrerror(char error_text[]);
	double **matrix(int nrl, int nrh, int ncl, int nch);
	void free_matrix(double** m, int nrl, int nrh, int ncl, int nch);
	void svbksb(double** u, double* w, double** v, int m, int n, double* b, double* x);
	void svdcmp(double** a, int m, int n, double* w, double** v);
	double trapzd(double* dataAngles, int a, int b, int n);
};

