#include "intersection.h"
#include "math.h"
#include <stdlib.h>
#include <stdio.h>

double *circle_intersect(double x1,double y1,double r1,double x2,double y2,double r2){
    double d,a,x_first,y_first,x_second,y_second,theta_first,theta_second;
    
    d = sqrt(pow(x2-x1,2) + pow(y2-y1,2));

    a = (pow(r1,2) - pow(r2,2) + pow(d,2))/(2*d);

    double P2x = x1 + a*(x2-x1)/d;
    double P2y = y1 + a*(y2-y1)/d;
    
    double h = sqrt(pow(r1,2) -pow(a,2));

    x_first = P2x + h*(y2-y1)/d;
    y_first = P2y - h*(x2-x1)/d;
    
    x_second = P2x - h*(y2-y1)/d;
    y_second = P2y + h*(x2-x1)/d;

    double *coords = malloc(sizeof(double) * 6);

    theta_first = acos(x_first/r1);

    if(theta_first < 0){
        theta_first = 2*M_PI + theta_first;
    }

    theta_second = acos(x_second/r1);


    if(theta_second < 0){
        theta_second = 2*M_PI + theta_second;
    }

    coords[0] = x_first;
    coords[1] = y_first;
    coords[2] = x_second;
    coords[3] = y_second;
    coords[4] = theta_first;
    coords[5] = theta_second;

    printf("circle %f %f %f %f %f %f\n",coords[0],coords[1],coords[2],coords[3],coords[4],coords[5]);

    return coords;
}


double *old_circle_intersect(double x1,double y1,double r1,double x2,double y2,double r2){
    double d,K,x_first,y_first,x_second,y_second,theta_first,theta_second;
    
    d = sqrt(pow(x2-x1,2) + pow(y2-y1,2));
    
    K = 0.25*sqrt((pow(r1+r2,2)-pow(d,2))*(pow(d,2)-pow(r1-r2,2)));

    printf("K is %f\n",K);
    
    x_first = 0.5*(x1+x2) + 0.5*(x2-x1)*(pow(r1,2)-pow(r2,2))/pow(d,2) + 2*(y2-y1)*K/pow(d,2);
    y_first = 0.5*(y2+y1) + 0.5*(y2-y1)*(pow(r1,2)-pow(r2,2))/pow(d,2) + -2*(x2-x1)*K/pow(d,2);
    
    x_second = 0.5*(x1+x2) + 0.5*(x2-x1)*(pow(r1,2)-pow(r2,2))/pow(d,2) - 2*(y2-y1)*K/pow(d,2);
    y_second = 0.5*(y2+y1) + 0.5*(y2-y1)*(pow(r1,2)-pow(r2,2))/pow(d,2) - -2*(x2-x1)*K/pow(d,2);

    double *coords = malloc(sizeof(double) * 6);

    theta_first = atan(y_first/x_first);

    if(theta_first < 0){
        theta_first = 2*M_PI + theta_first;
    }

    theta_second = atan(y_second/x_second);

    if(theta_second < 0){
        theta_second = 2*M_PI + theta_second;
    }

    coords[0] = x_first;
    coords[1] = y_first;
    coords[2] = x_second;
    coords[3] = y_second;
    coords[4] = theta_first;
    coords[5] = theta_second;

    printf("circle %f %f %f %f %f %f\n",coords[0],coords[1],coords[2],coords[3],coords[4],coords[5]);

    return coords;
}

double *line_intersect(double x1,double y1,double x2,double y2,double xc,double yc,double r){
    double x_first,y_first,x_second,y_second;

    double dx = x2-x1;
    double dy = y2-y1;
    double dr = sqrt(pow(dx,2) + pow(dy,2));

    double D = (x1-xc)*(y2-yc) - (x2-xc)*(y1-yc);

    double disc = pow(r*dr,2) - pow(D,2);
    double sgn = 1;
    if(dy < 0){
        sgn = -1;
    }

    x_first = ((D*dy + sgn*dx*sqrt(pow(r*dr,2) - pow(D,2)))/pow(dr,2));
    y_first = ((-D*dx + fabs(dy)*sqrt(pow(r*dr,2) - pow(D,2)))/pow(dr,2));

    x_second = ((D*dy - sgn*dx*sqrt(pow(r*dr,2) - pow(D,2)))/pow(dr,2));
    y_second = ((-D*dx - fabs(dy)*sqrt(pow(r*dr,2) - pow(D,2)))/pow(dr,2));


    x_first =x_first + xc;
    x_second =x_second + xc;

    y_first =y_first + yc;
    y_second =y_second + yc;

    double* coords = malloc(sizeof(double) * 6);

    double r_first = sqrt(pow(x_first,2) + pow(y_first,2));
    double r_second =sqrt(pow(x_second,2) + pow(y_second,2));

    coords[0] = x_first;
    coords[1] = y_first;
    coords[2] = x_second;
    coords[3] = y_second;
    coords[4] = r_first;
    coords[5] = r_second;

    return coords;
}

double *old_line_intersect(double m,double theta,double x2,double y2,double r2){
    double x_first,y_first,x_second,y_second;
    
    x_first = ((2*x2 + 2*y2*m) + sqrt(pow((2*x2 + 2*y2*m),2) - 4*(1 + pow(m,2))*(pow(x2,2) + pow(y2,2) - pow(r2,2))))/(2*(1 + pow(m,2)));
    x_second = ((2*x2 + 2*y2*m) - sqrt(pow((2*x2 + 2*y2*m),2) - 4*(1 + pow(m,2))*(pow(x2,2) + pow(y2,2) - pow(r2,2))))/(2*(1 + pow(m,2)));
    
    y_first = x_first*m;
    y_second = x_second*m;

    double* coords = malloc(sizeof(double) * 6);

    double r_first = sqrt(pow(x_first,2) + pow(y_first,2));
    double r_second =sqrt(pow(x_second,2) + pow(y_second,2));

    coords[0] = x_first;
    coords[1] = y_first;
    coords[2] = x_second;
    coords[3] = y_second;
    coords[4] = r_first;
    coords[5] = r_second;

    return coords;
}