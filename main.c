#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#define MAX 10000
#define EPSILON 0.0000000000001

/*******************************************************************************
 * Structure containing the defining triple (a,b,c) for a 3D brick, along with
 * fields for calculated values.
 *******************************************************************************/
struct Brick {
        int a;
        int b;
        int c;
        int a2;
        int b2;
        int c2;

        int ab_diag2;
        int bc_diag2;
        int ac_diag2;

        float ab_diag;
        float bc_diag;
        float ac_diag;

        int body_diag2;
        float body_diag;
};

/*******************************************************************************
 * From the defining triple (a,b,c) compute the values of the other fields
 *******************************************************************************/
void compute_diags(struct Brick *this){
        this->a2 = this->a * this->a;
        this->b2 = this->b * this->b;
        this->c2 = this->c * this->c;
        this->ab_diag2 = this->a2 + this->b2;
        this->bc_diag2 = this->b2 + this->c2;
        this->ac_diag2 = this->a2 + this->c2;
        this->body_diag2 = this->ab_diag2 + this->c2;
        this->ab_diag = (sqrt(this->ab_diag2));
        this->bc_diag = (sqrt(this->bc_diag2));
        this->ac_diag = (sqrt(this->ac_diag2));
}

/*******************************************************************************
 * Check if it is pythagorean.  For each of the diagonals, the value is rounded
 * and re-squared.  If that is different than the re-square after rounding is
 * different from the original square, that indicates that the square root is
 * not an integer.
 *
 * The function has the word "maybe" because you never know if a diagonal is
 * just so close to being an integer that we think it is.
 *******************************************************************************/
int maybe_pythagorean(struct Brick *this){

        if(fabs(round(this->ab_diag) * round(this->ab_diag) - this->ab_diag2) > EPSILON){
                return 0;
        }

        if(fabs(round(this->bc_diag) * round(this->bc_diag) - this->bc_diag2) > EPSILON){
                return 0;
        }

        if(fabs(round(this->ac_diag) * round(this->ac_diag) - this->ac_diag2) > EPSILON){
                return 0;
        }

        if(fabs(round(this->body_diag) * round(this->body_diag) - this->body_diag2) > EPSILON){
                return 0;
        }

        return 1;
}

/*******************************************************************************
 * Main program
 * Check options
 *    --max arg     : Allows to override the hard-coded MAX
 *    --verbose     : Print progress to STDERR
 * Potential pythagorean bricks are printed to STDOUT
 *
 * NOTE: If (a,b,c) all started at 1, then the program would try the brick
 * (1,2,3), (1,3,2), (2,1,3), (3,1,2), (2,3,1) and (3,2,1) as if they were
 * different.
 * starting at b=a and c=b makes sure that we will try all the bricks that are
 * given in ascending order.
 *******************************************************************************/
int main(int argc, char **argv){
        int max = MAX;
        int verbose = 0;
        for(int i = 0; i < argc; ++i){
                if(strcmp(argv[i], "--max") == 0){
                        ++i;
                        max = atoi(argv[i]);
                } else if(strcmp(argv[i], "--verbose") == 0){
                        verbose = 1;
                }
        }
        struct Brick brick;
        for(int a = 1; a < max; a++){
                if(verbose) fprintf(stderr, "Starting brick sequence (%d, x, x)\n", a);
                for(int b = a; b < max; b++){
                        if(verbose) fprintf(stderr, "Starting brick sequence (%d, %d, x)\n", a, b);
                        for(int c = b; c < max; c++){
                                brick.a = a;
                                brick.b = b;
                                brick.c = c;
                                compute_diags(&brick);
                                if(maybe_pythagorean(&brick)){
                                        printf("The brick (%d, %d, %d) might be pythagorean\n", a,b,c);
                                }
                        }
                }
        }
}
