#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define WIDTH 800
#define HEIGHT 800
#define MAX_ITER 300

void save_ppm(const char* filename, int* data) {
    FILE* fp = fopen(filename, "wb");
    fprintf(fp, "P6\n%d %d\n255\n", WIDTH, HEIGHT);
    for (int i = 0; i < WIDTH * HEIGHT; i++) {
        unsigned char color = (unsigned char)data[i];
        fwrite(&color, 1, 1, fp);  // R
        fwrite(&color, 1, 1, fp);  // G
        fwrite(&color, 1, 1, fp);  // B
    }
    fclose(fp);
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Usage: %s <real> <imaginary>\n", argv[0]);
        return 1;
    }

    double creal = atof(argv[1]);
    double cimag = atof(argv[2]);

    int* result = (int*)malloc(WIDTH * HEIGHT * sizeof(int));

    #pragma omp parallel for schedule(dynamic)
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            double zx = 1.5 * (x - WIDTH / 2) / (0.5 * WIDTH);
            double zy = (y - HEIGHT / 2) / (0.5 * HEIGHT);
            int i = MAX_ITER;
            while (zx * zx + zy * zy < 4.0 && i > 0) {
                double tmp = zx * zx - zy * zy + creal;
                zy = 2.0 * zx * zy + cimag;
                zx = tmp;
                i--;
            }
            result[y * WIDTH + x] = (int)(255.0 * i / MAX_ITER);
        }
    }

    save_ppm("julia_output.ppm", result);
    free(result);
    return 0;
}
