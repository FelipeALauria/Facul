#include <stdio.h>
#include <math.h>

// distância mru
double distmu(double v, double t) {
    double result = v * t;
    printf("%.2lf\n", result);
    return result;
}

// velocidade mru
double velomu(double s, double t) {
    double result = s / t;
    printf("%.2lf\n", result);
    return result;
}

// tempo mru
double tempmu(double s, double v) {
    double result = s / v;
    printf("%.2lf\n", result);
    return result;
}

// distância mruv
double distmruv(double vo, double a, double t) {
    double vt = vo * t;
    double att2 = 0.5 * a * t * t;
    double result = vt + att2;
    printf("%.2lf\n", result);
    return result;
}

// velocidade final mruv
double velofin(double vo, double a, double t) {
    double at = a * t;
    double result = vo + at;
    printf("%.2lf\n", result);
    return result;
}

// velocidade inicial mruv
double veloini(double s, double a, double t) {
    double att2 = 0.5 * a * t * t;
    double result = (s - att2) / t;
    printf("%.2lf\n", result);
    return result;
}

// tempo mruv
double temmruv(double s, double vo, double a) {
    double vov2 = vo * vo;
    double v2as = 2.0 * a * s;
    double sqrt_part = sqrt(vov2 + v2as);
    double result = (-vo + sqrt_part) / a;
    printf("%.2lf\n", result);
    return result;
}

// função main
int main() {
    int n, i, b;
    double p1, p2, p3;

    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d", &b);
        if (b == 1) {
            scanf("%lf %lf", &p1, &p2);
            distmu(p1, p2);
        } else if (b == 2) {
            scanf("%lf %lf", &p1, &p2);
            velomu(p1, p2);
        } else if (b == 3) {
            scanf("%lf %lf", &p1, &p2);
            tempmu(p1, p2);
        } else if (b == 4) {
            scanf("%lf %lf %lf", &p1, &p2, &p3);
            distmruv(p1, p2, p3);
        } else if (b == 5) {
            scanf("%lf %lf %lf", &p1, &p2, &p3);
            velofin(p1, p2, p3);
        } else if (b == 6) {
            scanf("%lf %lf %lf", &p1, &p2, &p3);
            veloini(p1, p2, p3);
        } else if (b == 7) {
            scanf("%lf %lf %lf", &p1, &p2, &p3);
            temmruv(p1, p2, p3);
        }
    }

    return 0;
}
