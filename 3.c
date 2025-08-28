#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#define BMAX 256


int main(int argc, char *argv[])

{
	int n = 2;
	int i, j;
	char buf[BMAX], *p, star[n][BMAX];
	double m[n], c[n][3], v[n][3];
	
	double G, me, ms;
    double Fx, Fy, Fz;
    double ae_x, ae_y, ae_z;
    double as_x, as_y, as_z;
    double dx, dy, dz, r, F;
    double ve_x, ve_y, ve_z;
    double vs_x, vs_y, vs_z ;
    double ps_x, ps_y, ps_z ;
    double pe_x, pe_y, pe_z ;
    double dt = 86400.0;
    long t;



  //file open
  FILE *file, *fp;
  fp = fopen("output.dat", "w");

	// parameter

	// read data
	//error
	if ( (file = fopen("stars.dat","r")) == NULL ) {
		fprintf(stderr, "File open error.\n");
		return 1;
	}
	//real
	fgets(buf, BMAX, file); //unnecessary line
	for(i=0; i<2; i++){
		fgets(buf, BMAX, file);
		p = strtok(buf, " ");
		strcpy(star[i], p);

		p = strtok(NULL, " ");
		m[i] = atof(p);

		for(j=0; j<3; j++){
			p = strtok(NULL, " ");
			c[i][j] = atof(p);
		}
		for(j=0; j<3; j++){
			p = strtok(NULL, " ");
			v[i][j] = atof(p);
		}
	}
	fclose(file);

    // file open
    if (fp == NULL) {
        perror("ファイルオープン失敗");
        return 1;
    }

    // parameters
    G  = 6.6743e-11;  // m^3 / kg / s^2
    me = m[1];    // mass, 地球 ,kg
    ms = m[0];    // mass, 地球 ,kg
    pe_x = c[1][0];
    pe_y = c[1][1];
    pe_z = c[1][2];
    ps_x = c[0][0];
    ps_y = c[0][1];
    ps_z = c[0][2];
    ve_x = v[1][0];       // velocity, 地球 ,m/s
    ve_y = v[1][1];       // velocity, 地球 ,m/s
    ve_z = v[1][2];       // velocity, 地球 ,m/s
    vs_x = v[0][0];       // velocity, 地球 ,m/s
    vs_y = v[0][1];       // velocity, 地球 ,m/s
    vs_z = v[0][2];       // velocity, 地球 ,m/s

    
    for (t=86400;t<=31536000;t=t+86400){
        
         // distance
         dx = pe_x-ps_x;     dy = pe_y-ps_y;    dz = pe_z-ps_z;
         r = sqrt(dx*dx + dy*dy + dz*dz);

         // force magnitude
         F = G * me * ms / (r * r);

        // force components
         Fx = F * dx / r;    Fy = F * dy / r;    Fz = F * dz / r;
        

         // accelerations
        as_x =  Fx / ms;    as_y =  Fy / ms;    as_z =  Fz / ms;
        ae_x = -Fx / me;    ae_y = -Fy / me;    ae_z = -Fz / me;
   
        //output
        fprintf(fp,"t = %ld\n",t/86400);
        fprintf(fp, "%-8s %10.3e %10.3e %10.3e\n", "Sun",   ps_x, ps_y, ps_z);
        fprintf(fp, "%-8s %10.3e %10.3e %10.3e\n", "Earth", pe_x, pe_y, pe_z);
        
        //change position
        pe_x = pe_x + dt*ve_x;
        pe_y = pe_y + dt*ve_y;
        pe_z = pe_z + dt*ve_z;
        
        ps_x = ps_x + dt*vs_x;
        ps_y = ps_y + dt*vs_y;
        ps_z = ps_z + dt*vs_z;
        
        //change velocity
        ve_x = ve_x + dt*ae_x; //of the Sun
        ve_y = ve_y + dt*ae_y;
        ve_z = ve_z + dt*ae_z;
        
        vs_x = vs_x + dt*as_x; //of the Earth
        vs_y = vs_y + dt*as_y;
        vs_z = vs_z + dt*as_z;
        
        

        if (r<=DBL_EPSILON){
            fprintf(stderr, "Error: r is too small (r = %e)\n", r);
            return 1;
            
        }
    }

    
    fclose(fp);
    return 0;
}

