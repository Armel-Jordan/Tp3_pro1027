#include "stdafx.h"
#include "Util.h"


Util::Util()
{
}
Util::~Util()
{
}

#define FUNC(x) ((*func)(x))
double Util::trapzd(double* dataAngles, int a, int b, int n)
{
	float x, tnm, sum, del;
	static float s;
	int it, j;
	if (n == 1) {
		return (s = 0.5*(b - a)*(dataAngles[a] + dataAngles[b]));
	}
	return -1;
}

double * Util::nrvector(int nl, int nh)
{
	double *v;

	v = (double *)malloc((unsigned)(nh - nl + 1) * sizeof(double));
	if (!v) nrerror("allocation failure in vector()");
	return v - nl;
}

void Util::free_vector(double * v, int nl, int nh)
{
	free((char*)(v + nl));
}

double** Util::matrix(int nrl, int nrh, int ncl, int nch)
{
	int i;
	double **m;

	m=(double **) malloc((unsigned) (nrh-nrl+1)*sizeof(double*));
	if (!m) nrerror("allocation failure 1 in matrix()");
	m -= nrl;

	for(i=nrl;i<=nrh;i++) {
	m[i]=(double *) malloc((unsigned) (nch-ncl+1)*sizeof(double));
	if (!m[i]) nrerror("allocation failure 2 in matrix()");
	m[i] -= ncl;
	}
	return m;
}

void Util::free_matrix(double ** m, int nrl, int nrh, int ncl, int nch)
{
	int i;
	for (i = nrh; i >= nrl; i--) free((char*)(m[i] + ncl));
	free((char*)(m + nrl));
}

void Util::spline(double x[], double y[], int n, double yp1, double ypn, double y2[])
{
	int i, k;
	double p, qn, sig, un, *u;

	u = nrvector(1, n - 1);
	if (yp1 > 0.99e30)
	y2[1] = u[1] = 0.0;
	else {
	y2[1] = -0.5;
	u[1] = (3.0 / (x[2] - x[1]))*((y[2] - y[1]) / (x[2] - x[1]) - yp1);
	}
	for (i = 2; i <= n - 1; i++) {
	sig = (x[i] - x[i - 1]) / (x[i + 1] - x[i - 1]);
	p = sig*y2[i - 1] + 2.0;
	y2[i] = (sig - 1.0) / p;
	u[i] = (y[i + 1] - y[i]) / (x[i + 1] - x[i]) - (y[i] - y[i - 1]) / (x[i] - x[i - 1]);
	u[i] = (6.0*u[i] / (x[i + 1] - x[i - 1]) - sig*u[i - 1]) / p;
	}
	if (ypn > 0.99e30)
	qn = un = 0.0;
	else {
	qn = 0.5;
	un = (3.0 / (x[n] - x[n - 1]))*(ypn - (y[n] - y[n - 1]) / (x[n] - x[n - 1]));
	}
	y2[n] = (un - qn*u[n - 1]) / (qn*y2[n - 1] + 1.0);
	for (k = n - 1; k >= 1; k--)
	y2[k] = y2[k] * y2[k + 1] + u[k];
	free_vector(u, 1, n - 1);
}

void Util::splint(double xa[], double ya[], double y2a[], int n, double x, double * y)
{
	int klo, khi, k;
	double h, b, a;

	klo = 1;
	khi = n;
	while (khi-klo>1) {
	k = (khi + klo) >> 1;
	if (xa[k] > x)
	khi = k;
	else
	klo = k;
	}
	h = xa[khi] - xa[klo];
	if (h == 0.0) nrerror("Bad xa input to routine splint");
	a = (xa[khi] - x) / h;
	b = (x - xa[klo]) / h;
	*y = a*ya[klo] + b*ya[khi] + ((a*a*a - a)*y2a[klo] + (b*b*b - b)*y2a[khi])*(h*h) / 6.0;
}

void Util::nrerror(char error_text[])
{
	/*Numerical Recipes standard error handler*/
	fprintf(stderr, "Numerical Recipes run-time error...\n");
	fprintf(stderr, "%s\n", error_text);
	fprintf(stderr, "...now exiting to system...\n");
	AfxMessageBox(error_text);
	exit(1);
}
//M�thode svdcmp() pour la factorisation de la matrice des points
static double at, bt, ct;
#define PYTHAG(a,b) ((at=fabs(a)) > (bt=fabs(b)) ? \
(ct=bt/at,at*sqrt(1.0+ct*ct)) : (bt ? (ct=at/bt,bt*sqrt(1.0+ct*ct)): 0.0))

static double maxarg1, maxarg2;
#define MAX(a,b) (maxarg1=(a),maxarg2=(b),(maxarg1) > (maxarg2) ?\
	(maxarg1) : (maxarg2))
#define SIGN(a,b) ((b) >= 0.0 ? fabs(a) : -fabs(a))
void Util::svdcmp(double ** a, int m, int n, double * w, double ** v)
{
	int flag, i, its, j, jj, k, l, nm;
	double c, f, h, s, x, y, z;
	double anorm = 0.0, g = 0.0, scale = 0.0;
	double *rv1;

	if (m < n)  nrerror("SVDCMP: You must augment A with extra zero rows");
	rv1 = nrvector(1, n);
	for (i = 1; i <= n; i++) {
		l = i + 1;
		rv1[i] = scale*g;
		g = s = scale = 0.0;
		if (i <= m) {
			for (k = i; k <= m; k++) scale += fabs(a[k][i]);
			if (scale) {
				for (k = i; k <= m; k++) {
					a[k][i] /= scale;
					s += a[k][i] * a[k][i];
				}
				f = a[i][i];
				g = -SIGN(sqrt(s), f);
				h = f*g - s;
				a[i][i] = f - g;
				if (i != n) {
					for (j = l; j <= n; j++) {
						for (s = 0.0, k = i; k <= m; k++) s += a[k][i] * a[k][j];
						f = s / h;
						for (k = i; k <= m; k++) a[k][j] += f*a[k][i];
					}
				}
				for (k = i; k <= m; k++) a[k][i] *= scale;
			}
		}
		w[i] = scale*g;
		g = s = scale = 0.0;
		if (i <= m && i != n) {
			for (k = l; k <= n; k++) scale += fabs(a[i][k]);
			if (scale) {
				for (k = l; k <= n; k++) {
					a[i][k] /= scale;
					s += a[i][k] * a[i][k];
				}
				f = a[i][l];
				g = -SIGN(sqrt(s), f);
				h = f*g - s;
				a[i][l] = f - g;
				for (k = l; k <= n; k++) rv1[k] = a[i][k] / h;
				if (i != m) {
					for (j = l; j <= m; j++) {
						for (s = 0.0, k = l; k <= n; k++) s += a[j][k] * a[i][k];
						for (k = l; k <= n; k++) a[j][k] += s*rv1[k];
					}
				}
				for (k = l; k <= n; k++) a[i][k] *= scale;
			}
		}
		anorm = MAX(anorm, (fabs(w[i]) + fabs(rv1[i])));
	}
	for (i = n; i >= 1; i--) {
		if (i < n) {
			if (g) {
				for (j = l; j <= n; j++)
					v[j][i] = (a[i][j] / a[i][l]) / g;
				for (j = l; j <= n; j++) {
					for (s = 0.0, k = l; k <= n; k++) s += a[i][k] * v[k][j];
					for (k = l; k <= n; k++) v[k][j] += s*v[k][i];
				}
			}
			for (j = l; j <= n; j++) v[i][j] = v[j][i] = 0.0;
		}
		v[i][i] = 1.0;
		g = rv1[i];
		l = i;
	}
	for (i = n; i >= 1; i--) {
		l = i + 1;
		g = w[i];
		if (i < n)
			for (j = l; j <= n; j++) a[i][j] = 0.0;
		if (g) {
			g = 1.0 / g;
			if (i != n) {
				for (j = l; j <= n; j++) {
					for (s = 0.0, k = l; k <= m; k++) s += a[k][i] * a[k][j];
					f = (s / a[i][i])*g;
					for (k = i; k <= m; k++) a[k][j] += f*a[k][i];
				}
			}
			for (j = i; j <= m; j++) a[j][i] *= g;
		}
		else {
			for (j = i; j <= m; j++) a[j][i] = 0.0;
		}
		++a[i][i];
	}
	for (k = n; k >= 1; k--) {
		for (its = 1; its <= 30; its++) {
			flag = 1;
			for (l = k; l >= 1; l--) {
				nm = l - 1;
				if ((double)(fabs(rv1[l]) + anorm) == anorm) {
					flag = 0;
					break;
				}
				if ((double)(fabs(w[nm]) + anorm) == anorm) break;
			}
			if (flag) {
				c = 0.0;
				s = 1.0;
				for (i = l; i <= k; i++) {
					f = s*rv1[i];
					rv1[i] = c*rv1[i];
					if ((double)(fabs(f) + anorm) == anorm) break;
					g = w[i];
					h = PYTHAG(f, g);
					w[i] = h;
					h = 1.0 / h;
					c = g*h;
					s = (-f*h);
					for (j = 1; j <= m; j++) {
						y = a[j][nm];
						z = a[j][i];
						a[j][nm] = y*c + z*s;
						a[j][i] = z*c - y*s;
					}
				}
			}
			z = w[k];
			if (l == k) {
				if (z < 0.0) {
					w[k] = -z;
					for (j = 1; j <= n; j++) v[j][k] = (-v[j][k]);
				}
				break;
			}
			if (its == 30)  nrerror("No convergence in 30 SVDCMP iterations");
			x = w[l];
			nm = k - 1;
			y = w[nm];
			g = rv1[nm];
			h = rv1[k];
			f = ((y - z)*(y + z) + (g - h)*(g + h)) / (2.0*h*y);
			g = PYTHAG(f, 1.0);
			f = ((x - z)*(x + z) + h*((y / (f + SIGN(g, f))) - h)) / x;
			c = s = 1.0;
			for (j = l; j <= nm; j++) {
				i = j + 1;
				g = rv1[i];
				y = w[i];
				h = s*g;
				g = c*g;
				z = PYTHAG(f, h);
				rv1[j] = z;
				c = f / z;
				s = h / z;
				f = x*c + g*s;
				g = g*c - x*s;
				h = y*s;
				y = y*c;
				for (jj = 1; jj <= n; jj++) {
					x = v[jj][j];
					z = v[jj][i];
					v[jj][j] = x*c + z*s;
					v[jj][i] = z*c - x*s;
				}
				z = PYTHAG(f, h);
				w[j] = z;
				if (z) {
					z = 1.0 / z;
					c = f*z;
					s = h*z;
				}
				f = (c*g) + (s*y);
				x = (c*y) - (s*g);
				for (jj = 1; jj <= m; jj++) {
					y = a[jj][j];
					z = a[jj][i];
					a[jj][j] = y*c + z*s;
					a[jj][i] = z*c - y*s;
				}
			}
			rv1[l] = 0.0;
			rv1[k] = f;
			w[k] = x;
		}
	}
	free_vector(rv1, 1, n);
}
void Util::svbksb(double ** u, double * w, double ** v, int m, int n, double * b, double * x)
{
	int jj, j, i;
	double s, *tmp;

	tmp = nrvector(1, n);
	for (j = 1; j <= n; j++) {
		s = 0.0;
		if (w[j]) {
			for (i = 1; i <= m; i++) s += u[i][j] * b[i];
			s /= w[j];
		}
		tmp[j] = s;
	}
	for (j = 1; j <= n; j++) {
		s = 0.0;
		for (jj = 1; jj <= n; jj++) s += v[j][jj] * tmp[jj];
		x[j] = s;
	}
	free_vector(tmp, 1, n);
}


