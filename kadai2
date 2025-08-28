#include <stdio.h>
#include <math.h>
#include <float.h>

int main(int argc, char *argv[])
{
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

    // file open
    FILE *fp = fopen("output.dat", "w");
    if (fp == NULL) {
        perror("ファイルオープン失敗");
        return 1;
    }

    // parameters
    G  = 6.6743e-11;  // m^3 / kg / s^2
    me = 5.972e24;    // mass, 地球 ,kg
    ms = 1.989e30;    // mass, 地球 ,kg
    pe_x = 1.496e11;
    pe_y = 0;
    pe_z = 0;
    ps_x = 0;
    ps_y = 0;
    ps_z = 0;
    ve_x = 0.0;       // velocity, 地球 ,m/s
    ve_y = 29870;     // velocity, 地球 ,m/s
    ve_z = 0.0;       // velocity, 地球 ,m/s
    vs_x = 0.0;       // velocity, 地球 ,m/s
    vs_y = 0.0;       // velocity, 地球 ,m/s
    vs_z = 0.0;       // velocity, 地球 ,m/s


    
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
