#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<fftw3.h>
#define PI 3.14159265

int main() {
// define initial variables and plans
	int i;
	int bin = 8;
	double *in;
	double *in2;
	int N = 2048; // samplerate
	int Nc = (N/2) + 1;
	double nu; // frequency
	float A_hamm = 2.4863230329; //hamming normalisation constant
	float A_hann = 2.627911687; // hanning normalisation constant 
	// int Norm = -2/N;
	FILE *file_i;
	FILE *file_o;

	fftw_complex *out;
	fftw_plan plan_backward;
	fftw_plan plan_forward;
	
for(nu = bin - 3; nu < bin + 3; nu += 0.1)
{
// sets up 'in' array to hold generated input signal

	in = fftw_malloc(sizeof(double)*N); //input signal

	for(i = 0; i < N; i++)
	{
		in[i] = sin(2*PI*i*nu/N); // generates data following 2pi/N i omega 
		// hanning = (0.5 - 0.5*cos(2*PI*i/(N-1))) * 
		// hamming = (0.53836 - 0.46164*cos(2*PI*i/(N-1))) * 
		
	}
// prints first and last ten values of 'in' to terminal
	printf("\n Input Data: \n \n");

	for (i = 0; i < N; i++)
	{
		if (i < 10 || i >= N - 10)
		{
			printf(" %3d %12f\n", i, in[i]);
		}

		if (i == 10)
		{
				printf("... ............\n");	
		}			
	}
// prints 'in' to 'input.txt' for plotting

	file_i = fopen("input.txt", "w+");
	
	for(i = 0; i < N; i++)
	{
		fprintf(file_i, "%d %f \n", i, in[i]);
	}

	fclose(file_i);
// generates 'out' array to hold fourier transformed data

	out = fftw_malloc(sizeof(fftw_complex)*Nc);
// defines and runs fftw3 plan

	plan_forward = fftw_plan_dft_r2c_1d(N, in, out, FFTW_ESTIMATE);

	fftw_execute(plan_forward);
// prints first and last ten values of 'out' to terminal

	 printf("\n Output Coefficients: \n \n");

	for (i = 0; i < Nc; i++)
	{
		if (i < 10 || i >= Nc - 10)
		{
			printf("%3d %.1f + %12fi \n", i, out[i][0], out[i][1]);
		}
		
		if (i == 10)
		{
			printf("... ............\n");
		}
	} 
// prints 'out' to 'output.txt' for plotting 
	char buf[0x100];
	snprintf(buf, sizeof(buf), "output_%.2f_bin%d.txt", nu, bin);

	file_o = fopen(buf, "w+");
	
	for(i = bin; i <= bin; i++)
	{
		fprintf(file_o, "%.2f %f \n", nu, A_hann * fabs(out[i][1] * out[i][1])); // fabs(out^2) yields spectrum
	}

	fclose(file_o);
// reconstructs 'in' from 'out' to 'in2'

	in2 = fftw_malloc(sizeof(double)*N);

	plan_backward = fftw_plan_dft_c2r_1d(N, out, in2, FFTW_ESTIMATE);

	fftw_execute(plan_backward);
// prints first and last ten values of 'in2' to terminal (checks work)

	printf("\n Reconstructed Input: \n \n");

	for(i=0; i<N; i++)
	{
		if (i < 10 || i >= N - 10)
		{
			printf("%3d %12f\n", i, in2[i]/(double) (N) );
		}

		if (i == 10)
		{
		printf("... ............\n");
		}
	}
// clears plans and arrays

	fftw_destroy_plan(plan_forward);
	fftw_destroy_plan(plan_backward);

	fftw_free(in);
	fftw_free(in2);
	fftw_free(out);
}

}

