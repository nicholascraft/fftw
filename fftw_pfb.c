#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<fftw3.h>
#include<glob.h>
#define PI 3.14159265

int main() {
// define initial variables and plans

	int i; //index
	int bin = 8;
	int N = 2048; // samplerate
	int Nc = (N/2) + 1; // complex samplerate
	int M; // taps
	int P; // branches

	double *in;
	double *in2;
	double nu; // frequency
	
	// int Norm = -2/N;
	FILE *file_i;
	FILE *file_o;

	fftw_complex *out;
	fftw_plan plan_backward;
	fftw_plan plan_forward;
	
for(nu = bin - 3; nu < bin + 3; nu += 0.1)
{

// generates 'in(n)', sets up 'in' array to hold generated input signal

	in = fftw_malloc(sizeof(double)*N); //input signal

	float A_hamm = 2.4863230329; //hamming normalisation constant
	float A_hann = 2.627911687; // hanning normalisation constant 

	for(i = 0; i < N; i++)
	{
		in[i] = sin(2*PI*i*nu/N); // generates data following 2pi/N i freq 
		 
		
	}

// writes to 'input.txt' for plotting

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

// clears plans and arrays

	fftw_destroy_plan(plan_forward);
	fftw_destroy_plan(plan_backward);

	fftw_free(in);
	fftw_free(in2);
	fftw_free(out);

}

// says it's done

	printf("All done :) \n");


// NOT WORKING ATM, USING CONC.PY compiles text files into one file?

	/* output_txt = glob("output_*.txt", GLOB_NOCHECK);

	FILE *glob = fopen(output_txt, "r");
	FILE *glob2 = fopen("Output_Final.txt", "w+");
	char c;

	while ((c = fgetc(output_txt)) != EOF)
		fputc(c, glob2);

	globfree(); */

}