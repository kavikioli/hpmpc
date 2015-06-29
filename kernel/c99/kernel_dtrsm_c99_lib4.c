/**************************************************************************************************
*                                                                                                 *
* This file is part of HPMPC.                                                                     *
*                                                                                                 *
* HPMPC -- Library for High-Performance implementation of solvers for MPC.                        *
* Copyright (C) 2014-2015 by Technical University of Denmark. All rights reserved.                *
*                                                                                                 *
* HPMPC is free software; you can redistribute it and/or                                          *
* modify it under the terms of the GNU Lesser General Public                                      *
* License as published by the Free Software Foundation; either                                    *
* version 2.1 of the License, or (at your option) any later version.                              *
*                                                                                                 *
* HPMPC is distributed in the hope that it will be useful,                                        *
* but WITHOUT ANY WARRANTY; without even the implied warranty of                                  *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                                            *
* See the GNU Lesser General Public License for more details.                                     *
*                                                                                                 *
* You should have received a copy of the GNU Lesser General Public                                *
* License along with HPMPC; if not, write to the Free Software                                    *
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA                  *
*                                                                                                 *
* Author: Gianluca Frison, giaf (at) dtu.dk                                                       *
*                                                                                                 *
**************************************************************************************************/

#include "../../include/block_size.h"



void kernel_dgemm_dtrsm_nt_4x4_vs_lib4(int km, int kn, int tri, int kadd, int ksub, double *Ap, double *Bp, double *Am, double *Bm, double *C, double *D, double *fact, int alg)
	{

	const int bs = 4;
	const int d_ncl = D_NCL;

	int k;

	double
		a_0, a_1, a_2, a_3,
		b_0, b_1, b_2, b_3,
		c_00=0, c_01=0, c_02=0, c_03=0,
		c_10=0, c_11=0, c_12=0, c_13=0,
		c_20=0, c_21=0, c_22=0, c_23=0,
		c_30=0, c_31=0, c_32=0, c_33=0;

	k = 0;

	if(kadd>0)
		{

		if(tri==1)
			{

			// initial triangle

			if(kadd>=4)
				{

				// k=0
				a_0 = Ap[0+bs*0];
					
				b_0 = Bp[0+bs*0];
				b_1 = Bp[1+bs*0];
				b_2 = Bp[2+bs*0];
				b_3 = Bp[3+bs*0];
					
				c_00 += a_0 * b_0;

				c_01 += a_0 * b_1;

				c_02 += a_0 * b_2;

				c_03 += a_0 * b_3;


				// k=1
				a_0 = Ap[0+bs*1];
				a_1 = Ap[1+bs*1];
					
				b_0 = Bp[0+bs*1];
				b_1 = Bp[1+bs*1];
				b_2 = Bp[2+bs*1];
				b_3 = Bp[3+bs*1];
					
				c_00 += a_0 * b_0;
				c_10 += a_1 * b_0;

				c_01 += a_0 * b_1;
				c_11 += a_1 * b_1;

				c_02 += a_0 * b_2;
				c_12 += a_1 * b_2;

				c_03 += a_0 * b_3;
				c_13 += a_1 * b_3;


				// k=2
				a_0 = Ap[0+bs*2];
				a_1 = Ap[1+bs*2];
				a_2 = Ap[2+bs*2];
					
				b_0 = Bp[0+bs*2];
				b_1 = Bp[1+bs*2];
				b_2 = Bp[2+bs*2];
				b_3 = Bp[3+bs*2];
					
				c_00 += a_0 * b_0;
				c_10 += a_1 * b_0;
				c_20 += a_2 * b_0;

				c_01 += a_0 * b_1;
				c_11 += a_1 * b_1;
				c_21 += a_2 * b_1;

				c_02 += a_0 * b_2;
				c_12 += a_1 * b_2;
				c_22 += a_2 * b_2;

				c_03 += a_0 * b_3;
				c_13 += a_1 * b_3;
				c_23 += a_2 * b_3;


				// k=3
				a_0 = Ap[0+bs*3];
				a_1 = Ap[1+bs*3];
				a_2 = Ap[2+bs*3];
				a_3 = Ap[3+bs*3];
					
				b_0 = Bp[0+bs*3];
				b_1 = Bp[1+bs*3];
				b_2 = Bp[2+bs*3];
				b_3 = Bp[3+bs*3];
					
				c_00 += a_0 * b_0;
				c_10 += a_1 * b_0;
				c_20 += a_2 * b_0;
				c_30 += a_3 * b_0;

				c_01 += a_0 * b_1;
				c_11 += a_1 * b_1;
				c_21 += a_2 * b_1;
				c_31 += a_3 * b_1;

				c_02 += a_0 * b_2;
				c_12 += a_1 * b_2;
				c_22 += a_2 * b_2;
				c_32 += a_3 * b_2;

				c_03 += a_0 * b_3;
				c_13 += a_1 * b_3;
				c_23 += a_2 * b_3;
				c_33 += a_3 * b_3;


				Ap += 16;
				Bp += 16;
				k += 4;
			
				}
			else
				{

				// k=0
				a_0 = Ap[0+bs*0];
					
				b_0 = Bp[0+bs*0];
				b_1 = Bp[1+bs*0];
				b_2 = Bp[2+bs*0];
				b_3 = Bp[3+bs*0];
					
				c_00 += a_0 * b_0;

				c_01 += a_0 * b_1;

				c_02 += a_0 * b_2;

				c_03 += a_0 * b_3;

				k += 1;

				if(kadd>1)
					{

					// k=1
					a_0 = Ap[0+bs*1];
					a_1 = Ap[1+bs*1];
						
					b_0 = Bp[0+bs*1];
					b_1 = Bp[1+bs*1];
					b_2 = Bp[2+bs*1];
					b_3 = Bp[3+bs*1];
						
					c_00 += a_0 * b_0;
					c_10 += a_1 * b_0;

					c_01 += a_0 * b_1;
					c_11 += a_1 * b_1;

					c_02 += a_0 * b_2;
					c_12 += a_1 * b_2;

					c_03 += a_0 * b_3;
					c_13 += a_1 * b_3;

					k += 1;

					if(kadd>2)
						{

						// k=2
						a_0 = Ap[0+bs*2];
						a_1 = Ap[1+bs*2];
						a_2 = Ap[2+bs*2];
							
						b_0 = Bp[0+bs*2];
						b_1 = Bp[1+bs*2];
						b_2 = Bp[2+bs*2];
						b_3 = Bp[3+bs*2];
							
						c_00 += a_0 * b_0;
						c_10 += a_1 * b_0;
						c_20 += a_2 * b_0;

						c_01 += a_0 * b_1;
						c_11 += a_1 * b_1;
						c_21 += a_2 * b_1;

						c_02 += a_0 * b_2;
						c_12 += a_1 * b_2;
						c_22 += a_2 * b_2;

						c_03 += a_0 * b_3;
						c_13 += a_1 * b_3;
						c_23 += a_2 * b_3;

						k += 1;

						}

					}

				}

			}

			
		for(; k<kadd-3; k+=4)
			{
			
			a_0 = Ap[0+bs*0];
			a_1 = Ap[1+bs*0];
			a_2 = Ap[2+bs*0];
			a_3 = Ap[3+bs*0];
			
			b_0 = Bp[0+bs*0];
			b_1 = Bp[1+bs*0];
			b_2 = Bp[2+bs*0];
			b_3 = Bp[3+bs*0];
			
			c_00 += a_0 * b_0;
			c_10 += a_1 * b_0;
			c_20 += a_2 * b_0;
			c_30 += a_3 * b_0;

			c_01 += a_0 * b_1;
			c_11 += a_1 * b_1;
			c_21 += a_2 * b_1;
			c_31 += a_3 * b_1;

			c_02 += a_0 * b_2;
			c_12 += a_1 * b_2;
			c_22 += a_2 * b_2;
			c_32 += a_3 * b_2;

			c_03 += a_0 * b_3;
			c_13 += a_1 * b_3;
			c_23 += a_2 * b_3;
			c_33 += a_3 * b_3;


			a_0 = Ap[0+bs*1];
			a_1 = Ap[1+bs*1];
			a_2 = Ap[2+bs*1];
			a_3 = Ap[3+bs*1];
			
			b_0 = Bp[0+bs*1];
			b_1 = Bp[1+bs*1];
			b_2 = Bp[2+bs*1];
			b_3 = Bp[3+bs*1];
			
			c_00 += a_0 * b_0;
			c_10 += a_1 * b_0;
			c_20 += a_2 * b_0;
			c_30 += a_3 * b_0;

			c_01 += a_0 * b_1;
			c_11 += a_1 * b_1;
			c_21 += a_2 * b_1;
			c_31 += a_3 * b_1;

			c_02 += a_0 * b_2;
			c_12 += a_1 * b_2;
			c_22 += a_2 * b_2;
			c_32 += a_3 * b_2;

			c_03 += a_0 * b_3;
			c_13 += a_1 * b_3;
			c_23 += a_2 * b_3;
			c_33 += a_3 * b_3;


			a_0 = Ap[0+bs*2];
			a_1 = Ap[1+bs*2];
			a_2 = Ap[2+bs*2];
			a_3 = Ap[3+bs*2];
			
			b_0 = Bp[0+bs*2];
			b_1 = Bp[1+bs*2];
			b_2 = Bp[2+bs*2];
			b_3 = Bp[3+bs*2];
			
			c_00 += a_0 * b_0;
			c_10 += a_1 * b_0;
			c_20 += a_2 * b_0;
			c_30 += a_3 * b_0;

			c_01 += a_0 * b_1;
			c_11 += a_1 * b_1;
			c_21 += a_2 * b_1;
			c_31 += a_3 * b_1;

			c_02 += a_0 * b_2;
			c_12 += a_1 * b_2;
			c_22 += a_2 * b_2;
			c_32 += a_3 * b_2;

			c_03 += a_0 * b_3;
			c_13 += a_1 * b_3;
			c_23 += a_2 * b_3;
			c_33 += a_3 * b_3;


			a_0 = Ap[0+bs*3];
			a_1 = Ap[1+bs*3];
			a_2 = Ap[2+bs*3];
			a_3 = Ap[3+bs*3];
			
			b_0 = Bp[0+bs*3];
			b_1 = Bp[1+bs*3];
			b_2 = Bp[2+bs*3];
			b_3 = Bp[3+bs*3];
			
			c_00 += a_0 * b_0;
			c_10 += a_1 * b_0;
			c_20 += a_2 * b_0;
			c_30 += a_3 * b_0;

			c_01 += a_0 * b_1;
			c_11 += a_1 * b_1;
			c_21 += a_2 * b_1;
			c_31 += a_3 * b_1;

			c_02 += a_0 * b_2;
			c_12 += a_1 * b_2;
			c_22 += a_2 * b_2;
			c_32 += a_3 * b_2;

			c_03 += a_0 * b_3;
			c_13 += a_1 * b_3;
			c_23 += a_2 * b_3;
			c_33 += a_3 * b_3;
			
			
			Ap += 16;
			Bp += 16;

			}
		for(; k<kadd; k++)
			{
			
			a_0 = Ap[0+bs*0];
			a_1 = Ap[1+bs*0];
			a_2 = Ap[2+bs*0];
			a_3 = Ap[3+bs*0];
			
			b_0 = Bp[0+bs*0];
			b_1 = Bp[1+bs*0];
			b_2 = Bp[2+bs*0];
			b_3 = Bp[3+bs*0];
			
			c_00 += a_0 * b_0;
			c_10 += a_1 * b_0;
			c_20 += a_2 * b_0;
			c_30 += a_3 * b_0;

			c_01 += a_0 * b_1;
			c_11 += a_1 * b_1;
			c_21 += a_2 * b_1;
			c_31 += a_3 * b_1;

			c_02 += a_0 * b_2;
			c_12 += a_1 * b_2;
			c_22 += a_2 * b_2;
			c_32 += a_3 * b_2;

			c_03 += a_0 * b_3;
			c_13 += a_1 * b_3;
			c_23 += a_2 * b_3;
			c_33 += a_3 * b_3;


			Ap += 4;
			Bp += 4;

			}

		}

	for(k=0; k<ksub-3; k+=4)
		{
		
		a_0 = Am[0+bs*0];
		a_1 = Am[1+bs*0];
		a_2 = Am[2+bs*0];
		a_3 = Am[3+bs*0];
		
		b_0 = Bm[0+bs*0];
		b_1 = Bm[1+bs*0];
		b_2 = Bm[2+bs*0];
		b_3 = Bm[3+bs*0];
		
		c_00 -= a_0 * b_0;
		c_10 -= a_1 * b_0;
		c_20 -= a_2 * b_0;
		c_30 -= a_3 * b_0;

		c_01 -= a_0 * b_1;
		c_11 -= a_1 * b_1;
		c_21 -= a_2 * b_1;
		c_31 -= a_3 * b_1;

		c_02 -= a_0 * b_2;
		c_12 -= a_1 * b_2;
		c_22 -= a_2 * b_2;
		c_32 -= a_3 * b_2;

		c_03 -= a_0 * b_3;
		c_13 -= a_1 * b_3;
		c_23 -= a_2 * b_3;
		c_33 -= a_3 * b_3;


		a_0 = Am[0+bs*1];
		a_1 = Am[1+bs*1];
		a_2 = Am[2+bs*1];
		a_3 = Am[3+bs*1];
		
		b_0 = Bm[0+bs*1];
		b_1 = Bm[1+bs*1];
		b_2 = Bm[2+bs*1];
		b_3 = Bm[3+bs*1];
		
		c_00 -= a_0 * b_0;
		c_10 -= a_1 * b_0;
		c_20 -= a_2 * b_0;
		c_30 -= a_3 * b_0;

		c_01 -= a_0 * b_1;
		c_11 -= a_1 * b_1;
		c_21 -= a_2 * b_1;
		c_31 -= a_3 * b_1;

		c_02 -= a_0 * b_2;
		c_12 -= a_1 * b_2;
		c_22 -= a_2 * b_2;
		c_32 -= a_3 * b_2;

		c_03 -= a_0 * b_3;
		c_13 -= a_1 * b_3;
		c_23 -= a_2 * b_3;
		c_33 -= a_3 * b_3;


		a_0 = Am[0+bs*2];
		a_1 = Am[1+bs*2];
		a_2 = Am[2+bs*2];
		a_3 = Am[3+bs*2];
		
		b_0 = Bm[0+bs*2];
		b_1 = Bm[1+bs*2];
		b_2 = Bm[2+bs*2];
		b_3 = Bm[3+bs*2];
		
		c_00 -= a_0 * b_0;
		c_10 -= a_1 * b_0;
		c_20 -= a_2 * b_0;
		c_30 -= a_3 * b_0;

		c_01 -= a_0 * b_1;
		c_11 -= a_1 * b_1;
		c_21 -= a_2 * b_1;
		c_31 -= a_3 * b_1;

		c_02 -= a_0 * b_2;
		c_12 -= a_1 * b_2;
		c_22 -= a_2 * b_2;
		c_32 -= a_3 * b_2;

		c_03 -= a_0 * b_3;
		c_13 -= a_1 * b_3;
		c_23 -= a_2 * b_3;
		c_33 -= a_3 * b_3;


		a_0 = Am[0+bs*3];
		a_1 = Am[1+bs*3];
		a_2 = Am[2+bs*3];
		a_3 = Am[3+bs*3];
		
		b_0 = Bm[0+bs*3];
		b_1 = Bm[1+bs*3];
		b_2 = Bm[2+bs*3];
		b_3 = Bm[3+bs*3];
		
		c_00 -= a_0 * b_0;
		c_10 -= a_1 * b_0;
		c_20 -= a_2 * b_0;
		c_30 -= a_3 * b_0;

		c_01 -= a_0 * b_1;
		c_11 -= a_1 * b_1;
		c_21 -= a_2 * b_1;
		c_31 -= a_3 * b_1;

		c_02 -= a_0 * b_2;
		c_12 -= a_1 * b_2;
		c_22 -= a_2 * b_2;
		c_32 -= a_3 * b_2;

		c_03 -= a_0 * b_3;
		c_13 -= a_1 * b_3;
		c_23 -= a_2 * b_3;
		c_33 -= a_3 * b_3;
		
		
		Am += 16;
		Bm += 16;

		}

	if(alg!=0)
		{
		c_00 += C[0+bs*0];
		c_10 += C[1+bs*0];
		c_20 += C[2+bs*0];
		c_30 += C[3+bs*0];

		c_01 += C[0+bs*1];
		c_11 += C[1+bs*1];
		c_21 += C[2+bs*1];
		c_31 += C[3+bs*1];

		c_02 += C[0+bs*2];
		c_12 += C[1+bs*2];
		c_22 += C[2+bs*2];
		c_32 += C[3+bs*2];

		c_03 += C[0+bs*3];
		c_13 += C[1+bs*3];
		c_23 += C[2+bs*3];
		c_33 += C[3+bs*3];
		}
	
	// dtrsm
	double
		a_00, a_10, a_20, a_30, a_11, a_21, a_31, a_22, a_32, a_33;
	
	a_00 = fact[0];
	c_00 *= a_00;
	c_10 *= a_00;
	c_20 *= a_00;
	c_30 *= a_00;
	D[0+bs*0] = c_00;
	D[1+bs*0] = c_10;
	D[2+bs*0] = c_20;
	if(km>=4)
		D[3+bs*0] = c_30;

	a_10 = fact[1];
	a_11 = fact[2];
	c_01 -= c_00*a_10;
	c_11 -= c_10*a_10;
	c_21 -= c_20*a_10;
	c_31 -= c_30*a_10;
	c_01 *= a_11;
	c_11 *= a_11;
	c_21 *= a_11;
	c_31 *= a_11;
	D[0+bs*1] = c_01;
	D[1+bs*1] = c_11;
	D[2+bs*1] = c_21;
	if(km>=4)
		D[3+bs*1] = c_31;

	a_20 = fact[3];
	a_21 = fact[4];
	a_22 = fact[5];
	c_02 -= c_00*a_20;
	c_12 -= c_10*a_20;
	c_22 -= c_20*a_20;
	c_32 -= c_30*a_20;
	c_02 -= c_01*a_21;
	c_12 -= c_11*a_21;
	c_22 -= c_21*a_21;
	c_32 -= c_31*a_21;
	c_02 *= a_22;
	c_12 *= a_22;
	c_22 *= a_22;
	c_32 *= a_22;
	D[0+bs*2] = c_02;
	D[1+bs*2] = c_12;
	D[2+bs*2] = c_22;
	if(km>=4)
		D[3+bs*2] = c_32;

	if(kn==3)
		return;

	a_30 = fact[6];
	a_31 = fact[7];
	a_32 = fact[8];
	a_33 = fact[9];
	c_03 -= c_00*a_30;
	c_13 -= c_10*a_30;
	c_23 -= c_20*a_30;
	c_33 -= c_30*a_30;
	c_03 -= c_01*a_31;
	c_13 -= c_11*a_31;
	c_23 -= c_21*a_31;
	c_33 -= c_31*a_31;
	c_03 -= c_02*a_32;
	c_13 -= c_12*a_32;
	c_23 -= c_22*a_32;
	c_33 -= c_32*a_32;
	c_03 *= a_33;
	c_13 *= a_33;
	c_23 *= a_33;
	c_33 *= a_33;
	D[0+bs*3] = c_03;
	D[1+bs*3] = c_13;
	D[2+bs*3] = c_23;
	if(km>=4)
		D[3+bs*3] = c_33;

	}
	
	
	
void kernel_dgemm_dtrsm_nt_4x2_vs_lib4(int km, int kn, int tri, int kadd, int ksub, double *Ap, double *Bp, double *Am, double *Bm, double *C, double *D, double *fact, int alg)
	{

	const int bs = 4;
	const int d_ncl = D_NCL;

	int k;

	double
		a_0, a_1, a_2, a_3,
		b_0, b_1,
		c_00=0, c_01=0,
		c_10=0, c_11=0,
		c_20=0, c_21=0,
		c_30=0, c_31=0;
	
	k = 0;

	if(kadd>0)
		{

		if(tri==1)
			{

			// initial triangle

			if(kadd>=4)
				{

				// k=0
				a_0 = Ap[0+bs*0];
					
				b_0 = Bp[0+bs*0];
				b_1 = Bp[1+bs*0];
					
				c_00 += a_0 * b_0;

				c_01 += a_0 * b_1;


				// k=1
				a_0 = Ap[0+bs*1];
				a_1 = Ap[1+bs*1];
					
				b_0 = Bp[0+bs*1];
				b_1 = Bp[1+bs*1];
					
				c_00 += a_0 * b_0;
				c_10 += a_1 * b_0;

				c_01 += a_0 * b_1;
				c_11 += a_1 * b_1;


				// k=2
				a_0 = Ap[0+bs*2];
				a_1 = Ap[1+bs*2];
				a_2 = Ap[2+bs*2];
					
				b_0 = Bp[0+bs*2];
				b_1 = Bp[1+bs*2];
					
				c_00 += a_0 * b_0;
				c_10 += a_1 * b_0;
				c_20 += a_2 * b_0;

				c_01 += a_0 * b_1;
				c_11 += a_1 * b_1;
				c_21 += a_2 * b_1;


				// k=3
				a_0 = Ap[0+bs*3];
				a_1 = Ap[1+bs*3];
				a_2 = Ap[2+bs*3];
				a_3 = Ap[3+bs*3];
					
				b_0 = Bp[0+bs*3];
				b_1 = Bp[1+bs*3];
					
				c_00 += a_0 * b_0;
				c_10 += a_1 * b_0;
				c_20 += a_2 * b_0;
				c_30 += a_3 * b_0;

				c_01 += a_0 * b_1;
				c_11 += a_1 * b_1;
				c_21 += a_2 * b_1;
				c_31 += a_3 * b_1;


				Ap += 16;
				Bp += 16;
				k += 4;

				}
			else
				{

				// k=0
				a_0 = Ap[0+bs*0];
					
				b_0 = Bp[0+bs*0];
				b_1 = Bp[1+bs*0];
					
				c_00 += a_0 * b_0;

				c_01 += a_0 * b_1;

				k += 1;

				if(kadd>1)
					{

					// k=1
					a_0 = Ap[0+bs*1];
					a_1 = Ap[1+bs*1];
						
					b_0 = Bp[0+bs*1];
					b_1 = Bp[1+bs*1];
						
					c_00 += a_0 * b_0;
					c_10 += a_1 * b_0;

					c_01 += a_0 * b_1;
					c_11 += a_1 * b_1;

					k += 1;

					if(kadd>2)
						{

						// k=2
						a_0 = Ap[0+bs*2];
						a_1 = Ap[1+bs*2];
						a_2 = Ap[2+bs*2];
							
						b_0 = Bp[0+bs*2];
						b_1 = Bp[1+bs*2];
							
						c_00 += a_0 * b_0;
						c_10 += a_1 * b_0;
						c_20 += a_2 * b_0;

						c_01 += a_0 * b_1;
						c_11 += a_1 * b_1;
						c_21 += a_2 * b_1;

						k += 1;

						}

					}

				}

			}
		
		for(; k<kadd-3; k+=4)
			{
			
			a_0 = Ap[0+bs*0];
			a_1 = Ap[1+bs*0];
			a_2 = Ap[2+bs*0];
			a_3 = Ap[3+bs*0];
			
			b_0 = Bp[0+bs*0];
			b_1 = Bp[1+bs*0];
			
			c_00 += a_0 * b_0;
			c_10 += a_1 * b_0;
			c_20 += a_2 * b_0;
			c_30 += a_3 * b_0;

			c_01 += a_0 * b_1;
			c_11 += a_1 * b_1;
			c_21 += a_2 * b_1;
			c_31 += a_3 * b_1;


			a_0 = Ap[0+bs*1];
			a_1 = Ap[1+bs*1];
			a_2 = Ap[2+bs*1];
			a_3 = Ap[3+bs*1];
			
			b_0 = Bp[0+bs*1];
			b_1 = Bp[1+bs*1];
			
			c_00 += a_0 * b_0;
			c_10 += a_1 * b_0;
			c_20 += a_2 * b_0;
			c_30 += a_3 * b_0;

			c_01 += a_0 * b_1;
			c_11 += a_1 * b_1;
			c_21 += a_2 * b_1;
			c_31 += a_3 * b_1;


			a_0 = Ap[0+bs*2];
			a_1 = Ap[1+bs*2];
			a_2 = Ap[2+bs*2];
			a_3 = Ap[3+bs*2];
			
			b_0 = Bp[0+bs*2];
			b_1 = Bp[1+bs*2];
			
			c_00 += a_0 * b_0;
			c_10 += a_1 * b_0;
			c_20 += a_2 * b_0;
			c_30 += a_3 * b_0;

			c_01 += a_0 * b_1;
			c_11 += a_1 * b_1;
			c_21 += a_2 * b_1;
			c_31 += a_3 * b_1;


			a_0 = Ap[0+bs*3];
			a_1 = Ap[1+bs*3];
			a_2 = Ap[2+bs*3];
			a_3 = Ap[3+bs*3];
			
			b_0 = Bp[0+bs*3];
			b_1 = Bp[1+bs*3];
			
			c_00 += a_0 * b_0;
			c_10 += a_1 * b_0;
			c_20 += a_2 * b_0;
			c_30 += a_3 * b_0;

			c_01 += a_0 * b_1;
			c_11 += a_1 * b_1;
			c_21 += a_2 * b_1;
			c_31 += a_3 * b_1;
			
			
			Ap += 16;
			Bp += 16;

			}
		for(; k<kadd; k++)
			{
			
			a_0 = Ap[0+bs*0];
			a_1 = Ap[1+bs*0];
			a_2 = Ap[2+bs*0];
			a_3 = Ap[3+bs*0];
			
			b_0 = Bp[0+bs*0];
			b_1 = Bp[1+bs*0];
			
			c_00 += a_0 * b_0;
			c_10 += a_1 * b_0;
			c_20 += a_2 * b_0;
			c_30 += a_3 * b_0;

			c_01 += a_0 * b_1;
			c_11 += a_1 * b_1;
			c_21 += a_2 * b_1;
			c_31 += a_3 * b_1;


			Ap += 4;
			Bp += 4;

			}

		}

	for(k=0; k<ksub-3; k+=4)
		{
		
		a_0 = Am[0+bs*0];
		a_1 = Am[1+bs*0];
		a_2 = Am[2+bs*0];
		a_3 = Am[3+bs*0];
		
		b_0 = Bm[0+bs*0];
		b_1 = Bm[1+bs*0];
		
		c_00 -= a_0 * b_0;
		c_10 -= a_1 * b_0;
		c_20 -= a_2 * b_0;
		c_30 -= a_3 * b_0;

		c_01 -= a_0 * b_1;
		c_11 -= a_1 * b_1;
		c_21 -= a_2 * b_1;
		c_31 -= a_3 * b_1;


		a_0 = Am[0+bs*1];
		a_1 = Am[1+bs*1];
		a_2 = Am[2+bs*1];
		a_3 = Am[3+bs*1];
		
		b_0 = Bm[0+bs*1];
		b_1 = Bm[1+bs*1];
		
		c_00 -= a_0 * b_0;
		c_10 -= a_1 * b_0;
		c_20 -= a_2 * b_0;
		c_30 -= a_3 * b_0;

		c_01 -= a_0 * b_1;
		c_11 -= a_1 * b_1;
		c_21 -= a_2 * b_1;
		c_31 -= a_3 * b_1;


		a_0 = Am[0+bs*2];
		a_1 = Am[1+bs*2];
		a_2 = Am[2+bs*2];
		a_3 = Am[3+bs*2];
		
		b_0 = Bm[0+bs*2];
		b_1 = Bm[1+bs*2];
		
		c_00 -= a_0 * b_0;
		c_10 -= a_1 * b_0;
		c_20 -= a_2 * b_0;
		c_30 -= a_3 * b_0;

		c_01 -= a_0 * b_1;
		c_11 -= a_1 * b_1;
		c_21 -= a_2 * b_1;
		c_31 -= a_3 * b_1;


		a_0 = Am[0+bs*3];
		a_1 = Am[1+bs*3];
		a_2 = Am[2+bs*3];
		a_3 = Am[3+bs*3];
		
		b_0 = Bm[0+bs*3];
		b_1 = Bm[1+bs*3];
		
		c_00 -= a_0 * b_0;
		c_10 -= a_1 * b_0;
		c_20 -= a_2 * b_0;
		c_30 -= a_3 * b_0;

		c_01 -= a_0 * b_1;
		c_11 -= a_1 * b_1;
		c_21 -= a_2 * b_1;
		c_31 -= a_3 * b_1;
		
		
		Am += 16;
		Bm += 16;

		}

	if(alg!=0)
		{
		c_00 += C[0+bs*0];
		c_10 += C[1+bs*0];
		c_20 += C[2+bs*0];
		c_30 += C[3+bs*0];

		c_01 += C[0+bs*1];
		c_11 += C[1+bs*1];
		c_21 += C[2+bs*1];
		c_31 += C[3+bs*1];
		}
	
	// dtrsm
	double
		a_00, a_10, a_11;
	
	a_00 = fact[0];
	c_00 *= a_00;
	c_10 *= a_00;
	c_20 *= a_00;
	c_30 *= a_00;
	D[0+bs*0] = c_00;
	D[1+bs*0] = c_10;
	D[2+bs*0] = c_20;
	if(km>=4)
		D[3+bs*0] = c_30;

	if(kn==1)
		return;

	a_10 = fact[1];
	a_11 = fact[2];
	c_01 -= c_00*a_10;
	c_11 -= c_10*a_10;
	c_21 -= c_20*a_10;
	c_31 -= c_30*a_10;
	c_01 *= a_11;
	c_11 *= a_11;
	c_21 *= a_11;
	c_31 *= a_11;
	D[0+bs*1] = c_01;
	D[1+bs*1] = c_11;
	D[2+bs*1] = c_21;
	if(km>=4)
		D[3+bs*1] = c_31;

	}
	
	
	
void kernel_dgemm_dtrsm_nt_2x4_vs_lib4(int km, int kn, int tri, int kadd, int ksub, double *Ap, double *Bp, double *Am, double *Bm, double *C, double *D, double *fact, int alg)
	{

	const int bs = 4;
	const int d_ncl = D_NCL;

	int k;

	double
		a_0, a_1,
		b_0, b_1, b_2, b_3,
		c_00=0, c_01=0, c_02=0, c_03=0,
		c_10=0, c_11=0, c_12=0, c_13=0;
	
	k = 0;

	if(kadd>0)
		{

		if(tri==1)
			{

			// initial triangle

			if(kadd>=2)
				{

				// k=0
				a_0 = Ap[0+bs*0];
					
				b_0 = Bp[0+bs*0];
				b_1 = Bp[1+bs*0];
				b_2 = Bp[2+bs*0];
				b_3 = Bp[3+bs*0];
					
				c_00 += a_0 * b_0;

				c_01 += a_0 * b_1;

				c_02 += a_0 * b_2;

				c_03 += a_0 * b_3;


				// k=1
				a_0 = Ap[0+bs*1];
				a_1 = Ap[1+bs*1];
					
				b_0 = Bp[0+bs*1];
				b_1 = Bp[1+bs*1];
				b_2 = Bp[2+bs*1];
				b_3 = Bp[3+bs*1];
					
				c_00 += a_0 * b_0;
				c_10 += a_1 * b_0;

				c_01 += a_0 * b_1;
				c_11 += a_1 * b_1;

				c_02 += a_0 * b_2;
				c_12 += a_1 * b_2;

				c_03 += a_0 * b_3;
				c_13 += a_1 * b_3;


				Ap += 8;
				Bp += 8;
				k += 2;
			
				}
			else
				{

				// k=0
				a_0 = Ap[0+bs*0];
					
				b_0 = Bp[0+bs*0];
				b_1 = Bp[1+bs*0];
				b_2 = Bp[2+bs*0];
				b_3 = Bp[3+bs*0];
					
				c_00 += a_0 * b_0;

				c_01 += a_0 * b_1;

				c_02 += a_0 * b_2;

				c_03 += a_0 * b_3;

				k += 1;

				}

			}
			
		for(; k<kadd-3; k+=4)
			{
			
			a_0 = Ap[0+bs*0];
			a_1 = Ap[1+bs*0];
			
			b_0 = Bp[0+bs*0];
			b_1 = Bp[1+bs*0];
			b_2 = Bp[2+bs*0];
			b_3 = Bp[3+bs*0];
			
			c_00 += a_0 * b_0;
			c_10 += a_1 * b_0;

			c_01 += a_0 * b_1;
			c_11 += a_1 * b_1;

			c_02 += a_0 * b_2;
			c_12 += a_1 * b_2;

			c_03 += a_0 * b_3;
			c_13 += a_1 * b_3;


			a_0 = Ap[0+bs*1];
			a_1 = Ap[1+bs*1];
			
			b_0 = Bp[0+bs*1];
			b_1 = Bp[1+bs*1];
			b_2 = Bp[2+bs*1];
			b_3 = Bp[3+bs*1];
			
			c_00 += a_0 * b_0;
			c_10 += a_1 * b_0;

			c_01 += a_0 * b_1;
			c_11 += a_1 * b_1;

			c_02 += a_0 * b_2;
			c_12 += a_1 * b_2;

			c_03 += a_0 * b_3;
			c_13 += a_1 * b_3;


			a_0 = Ap[0+bs*2];
			a_1 = Ap[1+bs*2];
			
			b_0 = Bp[0+bs*2];
			b_1 = Bp[1+bs*2];
			b_2 = Bp[2+bs*2];
			b_3 = Bp[3+bs*2];
			
			c_00 += a_0 * b_0;
			c_10 += a_1 * b_0;

			c_01 += a_0 * b_1;
			c_11 += a_1 * b_1;

			c_02 += a_0 * b_2;
			c_12 += a_1 * b_2;

			c_03 += a_0 * b_3;
			c_13 += a_1 * b_3;


			a_0 = Ap[0+bs*3];
			a_1 = Ap[1+bs*3];
			
			b_0 = Bp[0+bs*3];
			b_1 = Bp[1+bs*3];
			b_2 = Bp[2+bs*3];
			b_3 = Bp[3+bs*3];
			
			c_00 += a_0 * b_0;
			c_10 += a_1 * b_0;

			c_01 += a_0 * b_1;
			c_11 += a_1 * b_1;

			c_02 += a_0 * b_2;
			c_12 += a_1 * b_2;

			c_03 += a_0 * b_3;
			c_13 += a_1 * b_3;
			
			
			Ap += 16;
			Bp += 16;

			}
		for(; k<kadd; k++)
			{
			
			a_0 = Ap[0+bs*0];
			a_1 = Ap[1+bs*0];
			
			b_0 = Bp[0+bs*0];
			b_1 = Bp[1+bs*0];
			b_2 = Bp[2+bs*0];
			b_3 = Bp[3+bs*0];
			
			c_00 += a_0 * b_0;
			c_10 += a_1 * b_0;

			c_01 += a_0 * b_1;
			c_11 += a_1 * b_1;

			c_02 += a_0 * b_2;
			c_12 += a_1 * b_2;

			c_03 += a_0 * b_3;
			c_13 += a_1 * b_3;


			Ap += 4;
			Bp += 4;

			}

		}

	for(k=0; k<ksub-3; k+=4)
		{
		
		a_0 = Am[0+bs*0];
		a_1 = Am[1+bs*0];
		
		b_0 = Bm[0+bs*0];
		b_1 = Bm[1+bs*0];
		b_2 = Bm[2+bs*0];
		b_3 = Bm[3+bs*0];
		
		c_00 -= a_0 * b_0;
		c_10 -= a_1 * b_0;

		c_01 -= a_0 * b_1;
		c_11 -= a_1 * b_1;

		c_02 -= a_0 * b_2;
		c_12 -= a_1 * b_2;

		c_03 -= a_0 * b_3;
		c_13 -= a_1 * b_3;


		a_0 = Am[0+bs*1];
		a_1 = Am[1+bs*1];
		
		b_0 = Bm[0+bs*1];
		b_1 = Bm[1+bs*1];
		b_2 = Bm[2+bs*1];
		b_3 = Bm[3+bs*1];
		
		c_00 -= a_0 * b_0;
		c_10 -= a_1 * b_0;

		c_01 -= a_0 * b_1;
		c_11 -= a_1 * b_1;

		c_02 -= a_0 * b_2;
		c_12 -= a_1 * b_2;

		c_03 -= a_0 * b_3;
		c_13 -= a_1 * b_3;


		a_0 = Am[0+bs*2];
		a_1 = Am[1+bs*2];
		
		b_0 = Bm[0+bs*2];
		b_1 = Bm[1+bs*2];
		b_2 = Bm[2+bs*2];
		b_3 = Bm[3+bs*2];
		
		c_00 -= a_0 * b_0;
		c_10 -= a_1 * b_0;

		c_01 -= a_0 * b_1;
		c_11 -= a_1 * b_1;

		c_02 -= a_0 * b_2;
		c_12 -= a_1 * b_2;

		c_03 -= a_0 * b_3;
		c_13 -= a_1 * b_3;


		a_0 = Am[0+bs*3];
		a_1 = Am[1+bs*3];
		
		b_0 = Bm[0+bs*3];
		b_1 = Bm[1+bs*3];
		b_2 = Bm[2+bs*3];
		b_3 = Bm[3+bs*3];
		
		c_00 -= a_0 * b_0;
		c_10 -= a_1 * b_0;

		c_01 -= a_0 * b_1;
		c_11 -= a_1 * b_1;

		c_02 -= a_0 * b_2;
		c_12 -= a_1 * b_2;

		c_03 -= a_0 * b_3;
		c_13 -= a_1 * b_3;
		
		
		Am += 16;
		Bm += 16;

		}

	if(alg!=0)
		{
		c_00 += C[0+bs*0];
		c_10 += C[1+bs*0];

		c_01 += C[0+bs*1];
		c_11 += C[1+bs*1];

		c_02 += C[0+bs*2];
		c_12 += C[1+bs*2];

		c_03 += C[0+bs*3];
		c_13 += C[1+bs*3];
		}
	
	// dtrsm
	double
		a_00, a_10, a_20, a_30, a_11, a_21, a_31, a_22, a_32, a_33;
	
	a_00 = fact[0];
	c_00 *= a_00;
	c_10 *= a_00;
	D[0+bs*0] = c_00;
	if(km>=4)
		D[1+bs*0] = c_10;

	a_10 = fact[1];
	a_11 = fact[2];
	c_01 -= c_00*a_10;
	c_11 -= c_10*a_10;
	c_01 *= a_11;
	c_11 *= a_11;
	D[0+bs*1] = c_01;
	if(km>=4)
		D[1+bs*1] = c_11;

	a_20 = fact[3];
	a_21 = fact[4];
	a_22 = fact[5];
	c_02 -= c_00*a_20;
	c_12 -= c_10*a_20;
	c_02 -= c_01*a_21;
	c_12 -= c_11*a_21;
	c_02 *= a_22;
	c_12 *= a_22;
	D[0+bs*2] = c_02;
	if(km>=4)
		D[1+bs*2] = c_12;

	if(kn==3)
		return;

	a_30 = fact[6];
	a_31 = fact[7];
	a_32 = fact[8];
	a_33 = fact[9];
	c_03 -= c_00*a_30;
	c_13 -= c_10*a_30;
	c_03 -= c_01*a_31;
	c_13 -= c_11*a_31;
	c_03 -= c_02*a_32;
	c_13 -= c_12*a_32;
	c_03 *= a_33;
	c_13 *= a_33;
	D[0+bs*3] = c_03;
	if(km>=4)
		D[1+bs*3] = c_13;

	}
	
	
	
void kernel_dgemm_dtrsm_nt_2x2_vs_lib4(int km, int kn, int tri, int kadd, int ksub, double *Ap, double *Bp, double *Am, double *Bm, double *C, double *D, double *fact, int alg)
	{

	const int bs = 4;
	const int d_ncl = D_NCL;

	int k;

	double
		a_0, a_1,
		b_0, b_1,
		c_00=0, c_01=0,
		c_10=0, c_11=0;
	
	k = 0;

	if(kadd>0)
		{

		if(tri==1)
			{

			// initial triangle

			if(kadd>=2)
				{

				// k=0
				a_0 = Ap[0+bs*0];
					
				b_0 = Bp[0+bs*0];
				b_1 = Bp[1+bs*0];
					
				c_00 += a_0 * b_0;

				c_01 += a_0 * b_1;


				// k=1
				a_0 = Ap[0+bs*1];
				a_1 = Ap[1+bs*1];
					
				b_0 = Bp[0+bs*1];
				b_1 = Bp[1+bs*1];
					
				c_00 += a_0 * b_0;
				c_10 += a_1 * b_0;

				c_01 += a_0 * b_1;
				c_11 += a_1 * b_1;


				Ap += 8;
				Bp += 8;
				k += 2;

				}
			else
				{

				// k=0
				a_0 = Ap[0+bs*0];
					
				b_0 = Bp[0+bs*0];
				b_1 = Bp[1+bs*0];
					
				c_00 += a_0 * b_0;

				c_01 += a_0 * b_1;

				k += 1;


				}

			}
			
		for(; k<kadd-3; k+=4)
			{
			
			a_0 = Ap[0+bs*0];
			a_1 = Ap[1+bs*0];
			
			b_0 = Bp[0+bs*0];
			b_1 = Bp[1+bs*0];
			
			c_00 += a_0 * b_0;
			c_10 += a_1 * b_0;

			c_01 += a_0 * b_1;
			c_11 += a_1 * b_1;


			a_0 = Ap[0+bs*1];
			a_1 = Ap[1+bs*1];
			
			b_0 = Bp[0+bs*1];
			b_1 = Bp[1+bs*1];
			
			c_00 += a_0 * b_0;
			c_10 += a_1 * b_0;

			c_01 += a_0 * b_1;
			c_11 += a_1 * b_1;


			a_0 = Ap[0+bs*2];
			a_1 = Ap[1+bs*2];
			
			b_0 = Bp[0+bs*2];
			b_1 = Bp[1+bs*2];
			
			c_00 += a_0 * b_0;
			c_10 += a_1 * b_0;

			c_01 += a_0 * b_1;
			c_11 += a_1 * b_1;


			a_0 = Ap[0+bs*3];
			a_1 = Ap[1+bs*3];
			
			b_0 = Bp[0+bs*3];
			b_1 = Bp[1+bs*3];
			
			c_00 += a_0 * b_0;
			c_10 += a_1 * b_0;

			c_01 += a_0 * b_1;
			c_11 += a_1 * b_1;
			
			
			Ap += 16;
			Bp += 16;

			}
		for(; k<kadd; k++)
			{
			
			a_0 = Ap[0+bs*0];
			a_1 = Ap[1+bs*0];
			
			b_0 = Bp[0+bs*0];
			b_1 = Bp[1+bs*0];
			
			c_00 += a_0 * b_0;
			c_10 += a_1 * b_0;

			c_01 += a_0 * b_1;
			c_11 += a_1 * b_1;


			Ap += 4;
			Bp += 4;

			}

		}

	for(k=0; k<ksub-3; k+=4)
		{
		
		a_0 = Am[0+bs*0];
		a_1 = Am[1+bs*0];
		
		b_0 = Bm[0+bs*0];
		b_1 = Bm[1+bs*0];
		
		c_00 -= a_0 * b_0;
		c_10 -= a_1 * b_0;

		c_01 -= a_0 * b_1;
		c_11 -= a_1 * b_1;


		a_0 = Am[0+bs*1];
		a_1 = Am[1+bs*1];
		
		b_0 = Bm[0+bs*1];
		b_1 = Bm[1+bs*1];
		
		c_00 -= a_0 * b_0;
		c_10 -= a_1 * b_0;

		c_01 -= a_0 * b_1;
		c_11 -= a_1 * b_1;


		a_0 = Am[0+bs*2];
		a_1 = Am[1+bs*2];
		
		b_0 = Bm[0+bs*2];
		b_1 = Bm[1+bs*2];
		
		c_00 -= a_0 * b_0;
		c_10 -= a_1 * b_0;

		c_01 -= a_0 * b_1;
		c_11 -= a_1 * b_1;


		a_0 = Am[0+bs*3];
		a_1 = Am[1+bs*3];
		
		b_0 = Bm[0+bs*3];
		b_1 = Bm[1+bs*3];
		
		c_00 -= a_0 * b_0;
		c_10 -= a_1 * b_0;

		c_01 -= a_0 * b_1;
		c_11 -= a_1 * b_1;
		
		
		Am += 16;
		Bm += 16;

		}

	if(alg!=0)
		{
		c_00 += C[0+bs*0];
		c_10 += C[1+bs*0];

		c_01 += C[0+bs*1];
		c_11 += C[1+bs*1];
		}
	
	// dtrsm
	double
		a_00, a_10, a_11;
	
	a_00 = fact[0];
	c_00 *= a_00;
	c_10 *= a_00;
	D[0+bs*0] = c_00;
	if(km>=2)
		D[1+bs*0] = c_10;

	if(kn==1)
		return;

	a_10 = fact[1];
	a_11 = fact[2];
	c_01 -= c_00*a_10;
	c_11 -= c_10*a_10;
	c_01 *= a_11;
	c_11 *= a_11;
	D[0+bs*1] = c_01;
	if(km>=2)
		D[1+bs*1] = c_11;

	}
	
	
	

#if 0
// A is upper triangular
void kernel_dtrmm_dtrsm_nt_4x4_lib4(int kadd, int ksub, double *A, double *B, double *C, double *D, double *fact, int alg)
	{

	const int bs = 4;
	const int d_ncl = D_NCL;

//	d_print_mat(4, kadd, A, 4);
//	d_print_mat(4, kadd, B, 4);

	int k;

	double
		a_0, a_1, a_2, a_3,
		b_0, b_1, b_2, b_3,
		c_00=0, c_01=0, c_02=0, c_03=0,
		c_10=0, c_11=0, c_12=0, c_13=0,
		c_20=0, c_21=0, c_22=0, c_23=0,
		c_30=0, c_31=0, c_32=0, c_33=0;
	
	// initialize loop counter
	k = 0;

	if(kadd>=4)
		{

		// initial triangle

		// k=0
		a_0 = A[0+bs*0];
			
		b_0 = B[0+bs*0];
		b_1 = B[1+bs*0];
		b_2 = B[2+bs*0];
		b_3 = B[3+bs*0];
			
		c_00 += a_0 * b_0;

		c_01 += a_0 * b_1;

		c_02 += a_0 * b_2;

		c_03 += a_0 * b_3;


		// k=1
		a_0 = A[0+bs*1];
		a_1 = A[1+bs*1];
			
		b_0 = B[0+bs*1];
		b_1 = B[1+bs*1];
		b_2 = B[2+bs*1];
		b_3 = B[3+bs*1];
			
		c_00 += a_0 * b_0;
		c_10 += a_1 * b_0;

		c_01 += a_0 * b_1;
		c_11 += a_1 * b_1;

		c_02 += a_0 * b_2;
		c_12 += a_1 * b_2;

		c_03 += a_0 * b_3;
		c_13 += a_1 * b_3;


		// k=2
		a_0 = A[0+bs*2];
		a_1 = A[1+bs*2];
		a_2 = A[2+bs*2];
			
		b_0 = B[0+bs*2];
		b_1 = B[1+bs*2];
		b_2 = B[2+bs*2];
		b_3 = B[3+bs*2];
			
		c_00 += a_0 * b_0;
		c_10 += a_1 * b_0;
		c_20 += a_2 * b_0;

		c_01 += a_0 * b_1;
		c_11 += a_1 * b_1;
		c_21 += a_2 * b_1;

		c_02 += a_0 * b_2;
		c_12 += a_1 * b_2;
		c_22 += a_2 * b_2;

		c_03 += a_0 * b_3;
		c_13 += a_1 * b_3;
		c_23 += a_2 * b_3;


		// k=3
		a_0 = A[0+bs*3];
		a_1 = A[1+bs*3];
		a_2 = A[2+bs*3];
		a_3 = A[3+bs*3];
			
		b_0 = B[0+bs*3];
		b_1 = B[1+bs*3];
		b_2 = B[2+bs*3];
		b_3 = B[3+bs*3];
			
		c_00 += a_0 * b_0;
		c_10 += a_1 * b_0;
		c_20 += a_2 * b_0;
		c_30 += a_3 * b_0;

		c_01 += a_0 * b_1;
		c_11 += a_1 * b_1;
		c_21 += a_2 * b_1;
		c_31 += a_3 * b_1;

		c_02 += a_0 * b_2;
		c_12 += a_1 * b_2;
		c_22 += a_2 * b_2;
		c_32 += a_3 * b_2;

		c_03 += a_0 * b_3;
		c_13 += a_1 * b_3;
		c_23 += a_2 * b_3;
		c_33 += a_3 * b_3;


		A += 16;
		B += 16;
		k = 4;
			

		for(; k<kadd-3; k+=4)
			{
			
			a_0 = A[0+bs*0];
			a_1 = A[1+bs*0];
			a_2 = A[2+bs*0];
			a_3 = A[3+bs*0];
			
			b_0 = B[0+bs*0];
			b_1 = B[1+bs*0];
			b_2 = B[2+bs*0];
			b_3 = B[3+bs*0];
			
			c_00 += a_0 * b_0;
			c_10 += a_1 * b_0;
			c_20 += a_2 * b_0;
			c_30 += a_3 * b_0;

			c_01 += a_0 * b_1;
			c_11 += a_1 * b_1;
			c_21 += a_2 * b_1;
			c_31 += a_3 * b_1;

			c_02 += a_0 * b_2;
			c_12 += a_1 * b_2;
			c_22 += a_2 * b_2;
			c_32 += a_3 * b_2;

			c_03 += a_0 * b_3;
			c_13 += a_1 * b_3;
			c_23 += a_2 * b_3;
			c_33 += a_3 * b_3;


			a_0 = A[0+bs*1];
			a_1 = A[1+bs*1];
			a_2 = A[2+bs*1];
			a_3 = A[3+bs*1];
			
			b_0 = B[0+bs*1];
			b_1 = B[1+bs*1];
			b_2 = B[2+bs*1];
			b_3 = B[3+bs*1];
			
			c_00 += a_0 * b_0;
			c_10 += a_1 * b_0;
			c_20 += a_2 * b_0;
			c_30 += a_3 * b_0;

			c_01 += a_0 * b_1;
			c_11 += a_1 * b_1;
			c_21 += a_2 * b_1;
			c_31 += a_3 * b_1;

			c_02 += a_0 * b_2;
			c_12 += a_1 * b_2;
			c_22 += a_2 * b_2;
			c_32 += a_3 * b_2;

			c_03 += a_0 * b_3;
			c_13 += a_1 * b_3;
			c_23 += a_2 * b_3;
			c_33 += a_3 * b_3;


			a_0 = A[0+bs*2];
			a_1 = A[1+bs*2];
			a_2 = A[2+bs*2];
			a_3 = A[3+bs*2];
			
			b_0 = B[0+bs*2];
			b_1 = B[1+bs*2];
			b_2 = B[2+bs*2];
			b_3 = B[3+bs*2];
			
			c_00 += a_0 * b_0;
			c_10 += a_1 * b_0;
			c_20 += a_2 * b_0;
			c_30 += a_3 * b_0;

			c_01 += a_0 * b_1;
			c_11 += a_1 * b_1;
			c_21 += a_2 * b_1;
			c_31 += a_3 * b_1;

			c_02 += a_0 * b_2;
			c_12 += a_1 * b_2;
			c_22 += a_2 * b_2;
			c_32 += a_3 * b_2;

			c_03 += a_0 * b_3;
			c_13 += a_1 * b_3;
			c_23 += a_2 * b_3;
			c_33 += a_3 * b_3;


			a_0 = A[0+bs*3];
			a_1 = A[1+bs*3];
			a_2 = A[2+bs*3];
			a_3 = A[3+bs*3];
			
			b_0 = B[0+bs*3];
			b_1 = B[1+bs*3];
			b_2 = B[2+bs*3];
			b_3 = B[3+bs*3];
			
			c_00 += a_0 * b_0;
			c_10 += a_1 * b_0;
			c_20 += a_2 * b_0;
			c_30 += a_3 * b_0;

			c_01 += a_0 * b_1;
			c_11 += a_1 * b_1;
			c_21 += a_2 * b_1;
			c_31 += a_3 * b_1;

			c_02 += a_0 * b_2;
			c_12 += a_1 * b_2;
			c_22 += a_2 * b_2;
			c_32 += a_3 * b_2;

			c_03 += a_0 * b_3;
			c_13 += a_1 * b_3;
			c_23 += a_2 * b_3;
			c_33 += a_3 * b_3;
			
			
			A += 16;
			B += 16;

			}
		for(; k<kadd; k++)
			{
			
			a_0 = A[0+bs*0];
			a_1 = A[1+bs*0];
			a_2 = A[2+bs*0];
			a_3 = A[3+bs*0];
			
			b_0 = B[0+bs*0];
			b_1 = B[1+bs*0];
			b_2 = B[2+bs*0];
			b_3 = B[3+bs*0];
			
			c_00 += a_0 * b_0;
			c_10 += a_1 * b_0;
			c_20 += a_2 * b_0;
			c_30 += a_3 * b_0;

			c_01 += a_0 * b_1;
			c_11 += a_1 * b_1;
			c_21 += a_2 * b_1;
			c_31 += a_3 * b_1;

			c_02 += a_0 * b_2;
			c_12 += a_1 * b_2;
			c_22 += a_2 * b_2;
			c_32 += a_3 * b_2;

			c_03 += a_0 * b_3;
			c_13 += a_1 * b_3;
			c_23 += a_2 * b_3;
			c_33 += a_3 * b_3;


			A += 4;
			B += 4;

			}
		}
	else if(kadd>0)
		{

		// k = 0
		a_0 = A[0+bs*0];
			
		b_0 = B[0+bs*0];
		b_1 = B[1+bs*0];
		b_2 = B[2+bs*0];
		b_3 = B[3+bs*0];
			
		c_00 += a_0 * b_0;

		c_01 += a_0 * b_1;

		c_02 += a_0 * b_2;

		c_03 += a_0 * b_3;

		A += 4;
		B += 4;
		k += 1;

		if(kadd>1)
			{

			// k = 1
			a_0 = A[0+bs*0];
			a_1 = A[1+bs*0];
				
			b_0 = B[0+bs*0];
			b_1 = B[1+bs*0];
			b_2 = B[2+bs*0];
			b_3 = B[3+bs*0];
				
			c_00 += a_0 * b_0;
			c_10 += a_1 * b_0;

			c_01 += a_0 * b_1;
			c_11 += a_1 * b_1;

			c_02 += a_0 * b_2;
			c_12 += a_1 * b_2;

			c_03 += a_0 * b_3;
			c_13 += a_1 * b_3;

			A += 4;
			B += 4;
			k += 1;

			if(kadd>2)
				{

				// k = 2
				a_0 = A[0+bs*0];
				a_1 = A[1+bs*0];
				a_2 = A[2+bs*0];
					
				b_0 = B[0+bs*0];
				b_1 = B[1+bs*0];
				b_2 = B[2+bs*0];
				b_3 = B[3+bs*0];
					
				c_00 += a_0 * b_0;
				c_10 += a_1 * b_0;
				c_20 += a_2 * b_0;

				c_01 += a_0 * b_1;
				c_11 += a_1 * b_1;
				c_21 += a_2 * b_1;

				c_02 += a_0 * b_2;
				c_12 += a_1 * b_2;
				c_22 += a_2 * b_2;

				c_03 += a_0 * b_3;
				c_13 += a_1 * b_3;
				c_23 += a_2 * b_3;

				A += 4;
				B += 4;
				k += 1;

				}

			}

		}

	if(ksub>0)
		{
		if(kadd>0)
			{
			A += bs*((d_ncl-kadd%d_ncl)%d_ncl);
			B += bs*((d_ncl-kadd%d_ncl)%d_ncl);
			}
		}

	for(k=0; k<ksub-3; k+=4)
		{
		
		a_0 = A[0+bs*0];
		a_1 = A[1+bs*0];
		a_2 = A[2+bs*0];
		a_3 = A[3+bs*0];
		
		b_0 = B[0+bs*0];
		b_1 = B[1+bs*0];
		b_2 = B[2+bs*0];
		b_3 = B[3+bs*0];
		
		c_00 -= a_0 * b_0;
		c_10 -= a_1 * b_0;
		c_20 -= a_2 * b_0;
		c_30 -= a_3 * b_0;

		c_01 -= a_0 * b_1;
		c_11 -= a_1 * b_1;
		c_21 -= a_2 * b_1;
		c_31 -= a_3 * b_1;

		c_02 -= a_0 * b_2;
		c_12 -= a_1 * b_2;
		c_22 -= a_2 * b_2;
		c_32 -= a_3 * b_2;

		c_03 -= a_0 * b_3;
		c_13 -= a_1 * b_3;
		c_23 -= a_2 * b_3;
		c_33 -= a_3 * b_3;


		a_0 = A[0+bs*1];
		a_1 = A[1+bs*1];
		a_2 = A[2+bs*1];
		a_3 = A[3+bs*1];
		
		b_0 = B[0+bs*1];
		b_1 = B[1+bs*1];
		b_2 = B[2+bs*1];
		b_3 = B[3+bs*1];
		
		c_00 -= a_0 * b_0;
		c_10 -= a_1 * b_0;
		c_20 -= a_2 * b_0;
		c_30 -= a_3 * b_0;

		c_01 -= a_0 * b_1;
		c_11 -= a_1 * b_1;
		c_21 -= a_2 * b_1;
		c_31 -= a_3 * b_1;

		c_02 -= a_0 * b_2;
		c_12 -= a_1 * b_2;
		c_22 -= a_2 * b_2;
		c_32 -= a_3 * b_2;

		c_03 -= a_0 * b_3;
		c_13 -= a_1 * b_3;
		c_23 -= a_2 * b_3;
		c_33 -= a_3 * b_3;


		a_0 = A[0+bs*2];
		a_1 = A[1+bs*2];
		a_2 = A[2+bs*2];
		a_3 = A[3+bs*2];
		
		b_0 = B[0+bs*2];
		b_1 = B[1+bs*2];
		b_2 = B[2+bs*2];
		b_3 = B[3+bs*2];
		
		c_00 -= a_0 * b_0;
		c_10 -= a_1 * b_0;
		c_20 -= a_2 * b_0;
		c_30 -= a_3 * b_0;

		c_01 -= a_0 * b_1;
		c_11 -= a_1 * b_1;
		c_21 -= a_2 * b_1;
		c_31 -= a_3 * b_1;

		c_02 -= a_0 * b_2;
		c_12 -= a_1 * b_2;
		c_22 -= a_2 * b_2;
		c_32 -= a_3 * b_2;

		c_03 -= a_0 * b_3;
		c_13 -= a_1 * b_3;
		c_23 -= a_2 * b_3;
		c_33 -= a_3 * b_3;


		a_0 = A[0+bs*3];
		a_1 = A[1+bs*3];
		a_2 = A[2+bs*3];
		a_3 = A[3+bs*3];
		
		b_0 = B[0+bs*3];
		b_1 = B[1+bs*3];
		b_2 = B[2+bs*3];
		b_3 = B[3+bs*3];
		
		c_00 -= a_0 * b_0;
		c_10 -= a_1 * b_0;
		c_20 -= a_2 * b_0;
		c_30 -= a_3 * b_0;

		c_01 -= a_0 * b_1;
		c_11 -= a_1 * b_1;
		c_21 -= a_2 * b_1;
		c_31 -= a_3 * b_1;

		c_02 -= a_0 * b_2;
		c_12 -= a_1 * b_2;
		c_22 -= a_2 * b_2;
		c_32 -= a_3 * b_2;

		c_03 -= a_0 * b_3;
		c_13 -= a_1 * b_3;
		c_23 -= a_2 * b_3;
		c_33 -= a_3 * b_3;
		
		
		A += 16;
		B += 16;

		}

	if(alg!=0)
		{
		c_00 += C[0+bs*0];
		c_10 += C[1+bs*0];
		c_20 += C[2+bs*0];
		c_30 += C[3+bs*0];

		c_01 += C[0+bs*1];
		c_11 += C[1+bs*1];
		c_21 += C[2+bs*1];
		c_31 += C[3+bs*1];

		c_02 += C[0+bs*2];
		c_12 += C[1+bs*2];
		c_22 += C[2+bs*2];
		c_32 += C[3+bs*2];

		c_03 += C[0+bs*3];
		c_13 += C[1+bs*3];
		c_23 += C[2+bs*3];
		c_33 += C[3+bs*3];
		}
	
	// dtrsm
	double
		a_00, a_10, a_20, a_30, a_11, a_21, a_31, a_22, a_32, a_33;
	
	a_00 = fact[0];
	c_00 *= a_00;
	c_10 *= a_00;
	c_20 *= a_00;
	c_30 *= a_00;
	D[0+bs*0] = c_00;
	D[1+bs*0] = c_10;
	D[2+bs*0] = c_20;
	D[3+bs*0] = c_30;

	a_10 = fact[1];
	a_11 = fact[2];
	c_01 -= c_00*a_10;
	c_11 -= c_10*a_10;
	c_21 -= c_20*a_10;
	c_31 -= c_30*a_10;
	c_01 *= a_11;
	c_11 *= a_11;
	c_21 *= a_11;
	c_31 *= a_11;
	D[0+bs*1] = c_01;
	D[1+bs*1] = c_11;
	D[2+bs*1] = c_21;
	D[3+bs*1] = c_31;

	a_20 = fact[3];
	a_21 = fact[4];
	a_22 = fact[5];
	c_02 -= c_00*a_20;
	c_12 -= c_10*a_20;
	c_22 -= c_20*a_20;
	c_32 -= c_30*a_20;
	c_02 -= c_01*a_21;
	c_12 -= c_11*a_21;
	c_22 -= c_21*a_21;
	c_32 -= c_31*a_21;
	c_02 *= a_22;
	c_12 *= a_22;
	c_22 *= a_22;
	c_32 *= a_22;
	D[0+bs*2] = c_02;
	D[1+bs*2] = c_12;
	D[2+bs*2] = c_22;
	D[3+bs*2] = c_32;

	a_30 = fact[6];
	a_31 = fact[7];
	a_32 = fact[8];
	a_33 = fact[9];
	c_03 -= c_00*a_30;
	c_13 -= c_10*a_30;
	c_23 -= c_20*a_30;
	c_33 -= c_30*a_30;
	c_03 -= c_01*a_31;
	c_13 -= c_11*a_31;
	c_23 -= c_21*a_31;
	c_33 -= c_31*a_31;
	c_03 -= c_02*a_32;
	c_13 -= c_12*a_32;
	c_23 -= c_22*a_32;
	c_33 -= c_32*a_32;
	c_03 *= a_33;
	c_13 *= a_33;
	c_23 *= a_33;
	c_33 *= a_33;
	D[0+bs*3] = c_03;
	D[1+bs*3] = c_13;
	D[2+bs*3] = c_23;
	D[3+bs*3] = c_33;

	}
	
	
	
// A is upper triangular
void kernel_dtrmm_dtrsm_nt_4x2_lib4(int kadd, int ksub, double *A, double *B, double *C, double *D, double *fact, int alg)
	{

	const int bs = 4;
	const int d_ncl = D_NCL;

	int k;

	double
		a_0, a_1, a_2, a_3,
		b_0, b_1,
		c_00=0, c_01=0,
		c_10=0, c_11=0,
		c_20=0, c_21=0,
		c_30=0, c_31=0;

	// initialize loop counter
	k = 0;

	if(kadd>=4)
		{

		// initial triangle

		// k=0
		a_0 = A[0+bs*0];
			
		b_0 = B[0+bs*0];
		b_1 = B[1+bs*0];
			
		c_00 += a_0 * b_0;

		c_01 += a_0 * b_1;


		// k=1
		a_0 = A[0+bs*1];
		a_1 = A[1+bs*1];
			
		b_0 = B[0+bs*1];
		b_1 = B[1+bs*1];
			
		c_00 += a_0 * b_0;
		c_10 += a_1 * b_0;

		c_01 += a_0 * b_1;
		c_11 += a_1 * b_1;


		// k=2
		a_0 = A[0+bs*2];
		a_1 = A[1+bs*2];
		a_2 = A[2+bs*2];
			
		b_0 = B[0+bs*2];
		b_1 = B[1+bs*2];
			
		c_00 += a_0 * b_0;
		c_10 += a_1 * b_0;
		c_20 += a_2 * b_0;

		c_01 += a_0 * b_1;
		c_11 += a_1 * b_1;
		c_21 += a_2 * b_1;


		// k=3
		a_0 = A[0+bs*3];
		a_1 = A[1+bs*3];
		a_2 = A[2+bs*3];
		a_3 = A[3+bs*3];
			
		b_0 = B[0+bs*3];
		b_1 = B[1+bs*3];
			
		c_00 += a_0 * b_0;
		c_10 += a_1 * b_0;
		c_20 += a_2 * b_0;
		c_30 += a_3 * b_0;

		c_01 += a_0 * b_1;
		c_11 += a_1 * b_1;
		c_21 += a_2 * b_1;
		c_31 += a_3 * b_1;


		A += 16;
		B += 16;
		k = 4;

			
		for(; k<kadd-3; k+=4)
			{
			
			a_0 = A[0+bs*0];
			a_1 = A[1+bs*0];
			a_2 = A[2+bs*0];
			a_3 = A[3+bs*0];
			
			b_0 = B[0+bs*0];
			b_1 = B[1+bs*0];
			
			c_00 += a_0 * b_0;
			c_10 += a_1 * b_0;
			c_20 += a_2 * b_0;
			c_30 += a_3 * b_0;

			c_01 += a_0 * b_1;
			c_11 += a_1 * b_1;
			c_21 += a_2 * b_1;
			c_31 += a_3 * b_1;


			a_0 = A[0+bs*1];
			a_1 = A[1+bs*1];
			a_2 = A[2+bs*1];
			a_3 = A[3+bs*1];
			
			b_0 = B[0+bs*1];
			b_1 = B[1+bs*1];
			
			c_00 += a_0 * b_0;
			c_10 += a_1 * b_0;
			c_20 += a_2 * b_0;
			c_30 += a_3 * b_0;

			c_01 += a_0 * b_1;
			c_11 += a_1 * b_1;
			c_21 += a_2 * b_1;
			c_31 += a_3 * b_1;


			a_0 = A[0+bs*2];
			a_1 = A[1+bs*2];
			a_2 = A[2+bs*2];
			a_3 = A[3+bs*2];
			
			b_0 = B[0+bs*2];
			b_1 = B[1+bs*2];
			
			c_00 += a_0 * b_0;
			c_10 += a_1 * b_0;
			c_20 += a_2 * b_0;
			c_30 += a_3 * b_0;

			c_01 += a_0 * b_1;
			c_11 += a_1 * b_1;
			c_21 += a_2 * b_1;
			c_31 += a_3 * b_1;


			a_0 = A[0+bs*3];
			a_1 = A[1+bs*3];
			a_2 = A[2+bs*3];
			a_3 = A[3+bs*3];
			
			b_0 = B[0+bs*3];
			b_1 = B[1+bs*3];
			
			c_00 += a_0 * b_0;
			c_10 += a_1 * b_0;
			c_20 += a_2 * b_0;
			c_30 += a_3 * b_0;

			c_01 += a_0 * b_1;
			c_11 += a_1 * b_1;
			c_21 += a_2 * b_1;
			c_31 += a_3 * b_1;
			
			
			A += 16;
			B += 16;

			}
		for(; k<kadd; k++)
			{
			
			a_0 = A[0+bs*0];
			a_1 = A[1+bs*0];
			a_2 = A[2+bs*0];
			a_3 = A[3+bs*0];
			
			b_0 = B[0+bs*0];
			b_1 = B[1+bs*0];
			
			c_00 += a_0 * b_0;
			c_10 += a_1 * b_0;
			c_20 += a_2 * b_0;
			c_30 += a_3 * b_0;

			c_01 += a_0 * b_1;
			c_11 += a_1 * b_1;
			c_21 += a_2 * b_1;
			c_31 += a_3 * b_1;


			A += 4;
			B += 4;

			}
		}
	else if(kadd>0)
		{

		// k = 0
		a_0 = A[0+bs*0];
			
		b_0 = B[0+bs*0];
		b_1 = B[1+bs*0];
			
		c_00 += a_0 * b_0;

		c_01 += a_0 * b_1;

		A += 4;
		B += 4;
		k += 1;

		if(kadd>1)
			{

			// k = 1
			a_0 = A[0+bs*0];
			a_1 = A[1+bs*0];
				
			b_0 = B[0+bs*0];
			b_1 = B[1+bs*0];
				
			c_00 += a_0 * b_0;
			c_10 += a_1 * b_0;

			c_01 += a_0 * b_1;
			c_11 += a_1 * b_1;

			A += 4;
			B += 4;
			k += 1;

			if(kadd>2)
				{

				// k = 2
				a_0 = A[0+bs*0];
				a_1 = A[1+bs*0];
				a_2 = A[2+bs*0];
					
				b_0 = B[0+bs*0];
				b_1 = B[1+bs*0];
					
				c_00 += a_0 * b_0;
				c_10 += a_1 * b_0;
				c_20 += a_2 * b_0;

				c_01 += a_0 * b_1;
				c_11 += a_1 * b_1;
				c_21 += a_2 * b_1;

				A += 4;
				B += 4;
				k += 1;

				}

			}

		}

	if(ksub>0)
		{
		if(kadd>0)
			{
			A += bs*((d_ncl-kadd%d_ncl)%d_ncl);
			B += bs*((d_ncl-kadd%d_ncl)%d_ncl);
			}
		}

	for(k=0; k<ksub-3; k+=4)
		{
		
		a_0 = A[0+bs*0];
		a_1 = A[1+bs*0];
		a_2 = A[2+bs*0];
		a_3 = A[3+bs*0];
		
		b_0 = B[0+bs*0];
		b_1 = B[1+bs*0];
		
		c_00 -= a_0 * b_0;
		c_10 -= a_1 * b_0;
		c_20 -= a_2 * b_0;
		c_30 -= a_3 * b_0;

		c_01 -= a_0 * b_1;
		c_11 -= a_1 * b_1;
		c_21 -= a_2 * b_1;
		c_31 -= a_3 * b_1;


		a_0 = A[0+bs*1];
		a_1 = A[1+bs*1];
		a_2 = A[2+bs*1];
		a_3 = A[3+bs*1];
		
		b_0 = B[0+bs*1];
		b_1 = B[1+bs*1];
		
		c_00 -= a_0 * b_0;
		c_10 -= a_1 * b_0;
		c_20 -= a_2 * b_0;
		c_30 -= a_3 * b_0;

		c_01 -= a_0 * b_1;
		c_11 -= a_1 * b_1;
		c_21 -= a_2 * b_1;
		c_31 -= a_3 * b_1;


		a_0 = A[0+bs*2];
		a_1 = A[1+bs*2];
		a_2 = A[2+bs*2];
		a_3 = A[3+bs*2];
		
		b_0 = B[0+bs*2];
		b_1 = B[1+bs*2];
		
		c_00 -= a_0 * b_0;
		c_10 -= a_1 * b_0;
		c_20 -= a_2 * b_0;
		c_30 -= a_3 * b_0;

		c_01 -= a_0 * b_1;
		c_11 -= a_1 * b_1;
		c_21 -= a_2 * b_1;
		c_31 -= a_3 * b_1;


		a_0 = A[0+bs*3];
		a_1 = A[1+bs*3];
		a_2 = A[2+bs*3];
		a_3 = A[3+bs*3];
		
		b_0 = B[0+bs*3];
		b_1 = B[1+bs*3];
		
		c_00 -= a_0 * b_0;
		c_10 -= a_1 * b_0;
		c_20 -= a_2 * b_0;
		c_30 -= a_3 * b_0;

		c_01 -= a_0 * b_1;
		c_11 -= a_1 * b_1;
		c_21 -= a_2 * b_1;
		c_31 -= a_3 * b_1;
		
		
		A += 16;
		B += 16;

		}

	if(alg!=0)
		{
		c_00 += C[0+bs*0];
		c_10 += C[1+bs*0];
		c_20 += C[2+bs*0];
		c_30 += C[3+bs*0];

		c_01 += C[0+bs*1];
		c_11 += C[1+bs*1];
		c_21 += C[2+bs*1];
		c_31 += C[3+bs*1];
		}
	
	// dtrsm
	double
		a_00, a_10, a_11;
	
	a_00 = fact[0];
	c_00 *= a_00;
	c_10 *= a_00;
	c_20 *= a_00;
	c_30 *= a_00;
	D[0+bs*0] = c_00;
	D[1+bs*0] = c_10;
	D[2+bs*0] = c_20;
	D[3+bs*0] = c_30;

	a_10 = fact[1];
	a_11 = fact[2];
	c_01 -= c_00*a_10;
	c_11 -= c_10*a_10;
	c_21 -= c_20*a_10;
	c_31 -= c_30*a_10;
	c_01 *= a_11;
	c_11 *= a_11;
	c_21 *= a_11;
	c_31 *= a_11;
	D[0+bs*1] = c_01;
	D[1+bs*1] = c_11;
	D[2+bs*1] = c_21;
	D[3+bs*1] = c_31;

	}
	
	
	
// A is upper triangular
void kernel_dtrmm_dtrsm_nt_2x4_lib4(int kadd, int ksub, double *A, double *B, double *C, double *D, double *fact, int alg)
	{

	const int bs = 4;
	const int d_ncl = D_NCL;

	int k;

	double
		a_0, a_1,
		b_0, b_1, b_2, b_3,
		c_00=0, c_01=0, c_02=0, c_03=0,
		c_10=0, c_11=0, c_12=0, c_13=0;
		
	// initialize loop counter
	k = 0;

	if(kadd>=2)
		{

		// initial triangle

		// k=0
		a_0 = A[0+bs*0];
			
		b_0 = B[0+bs*0];
		b_1 = B[1+bs*0];
		b_2 = B[2+bs*0];
		b_3 = B[3+bs*0];
			
		c_00 += a_0 * b_0;

		c_01 += a_0 * b_1;

		c_02 += a_0 * b_2;

		c_03 += a_0 * b_3;


		// k=1
		a_0 = A[0+bs*1];
		a_1 = A[1+bs*1];
			
		b_0 = B[0+bs*1];
		b_1 = B[1+bs*1];
		b_2 = B[2+bs*1];
		b_3 = B[3+bs*1];
			
		c_00 += a_0 * b_0;
		c_10 += a_1 * b_0;

		c_01 += a_0 * b_1;
		c_11 += a_1 * b_1;

		c_02 += a_0 * b_2;
		c_12 += a_1 * b_2;

		c_03 += a_0 * b_3;
		c_13 += a_1 * b_3;


		A += 8;
		B += 8;
		k = 2;
			

		
		for(; k<kadd-3; k+=4)
			{
			
			a_0 = A[0+bs*0];
			a_1 = A[1+bs*0];
			
			b_0 = B[0+bs*0];
			b_1 = B[1+bs*0];
			b_2 = B[2+bs*0];
			b_3 = B[3+bs*0];
			
			c_00 += a_0 * b_0;
			c_10 += a_1 * b_0;

			c_01 += a_0 * b_1;
			c_11 += a_1 * b_1;

			c_02 += a_0 * b_2;
			c_12 += a_1 * b_2;

			c_03 += a_0 * b_3;
			c_13 += a_1 * b_3;


			a_0 = A[0+bs*1];
			a_1 = A[1+bs*1];
			
			b_0 = B[0+bs*1];
			b_1 = B[1+bs*1];
			b_2 = B[2+bs*1];
			b_3 = B[3+bs*1];
			
			c_00 += a_0 * b_0;
			c_10 += a_1 * b_0;

			c_01 += a_0 * b_1;
			c_11 += a_1 * b_1;

			c_02 += a_0 * b_2;
			c_12 += a_1 * b_2;

			c_03 += a_0 * b_3;
			c_13 += a_1 * b_3;


			a_0 = A[0+bs*2];
			a_1 = A[1+bs*2];
			
			b_0 = B[0+bs*2];
			b_1 = B[1+bs*2];
			b_2 = B[2+bs*2];
			b_3 = B[3+bs*2];
			
			c_00 += a_0 * b_0;
			c_10 += a_1 * b_0;

			c_01 += a_0 * b_1;
			c_11 += a_1 * b_1;

			c_02 += a_0 * b_2;
			c_12 += a_1 * b_2;

			c_03 += a_0 * b_3;
			c_13 += a_1 * b_3;


			a_0 = A[0+bs*3];
			a_1 = A[1+bs*3];
			
			b_0 = B[0+bs*3];
			b_1 = B[1+bs*3];
			b_2 = B[2+bs*3];
			b_3 = B[3+bs*3];
			
			c_00 += a_0 * b_0;
			c_10 += a_1 * b_0;

			c_01 += a_0 * b_1;
			c_11 += a_1 * b_1;

			c_02 += a_0 * b_2;
			c_12 += a_1 * b_2;

			c_03 += a_0 * b_3;
			c_13 += a_1 * b_3;
			
			
			A += 16;
			B += 16;

			}
		for(; k<kadd; k++)
			{
			
			a_0 = A[0+bs*0];
			a_1 = A[1+bs*0];
			
			b_0 = B[0+bs*0];
			b_1 = B[1+bs*0];
			b_2 = B[2+bs*0];
			b_3 = B[3+bs*0];
			
			c_00 += a_0 * b_0;
			c_10 += a_1 * b_0;

			c_01 += a_0 * b_1;
			c_11 += a_1 * b_1;

			c_02 += a_0 * b_2;
			c_12 += a_1 * b_2;

			c_03 += a_0 * b_3;
			c_13 += a_1 * b_3;


			A += 4;
			B += 4;

			}
		}
	else if(kadd>0)
		{

		// k = 0
		a_0 = A[0+bs*0];
			
		b_0 = B[0+bs*0];
		b_1 = B[1+bs*0];
		b_2 = B[2+bs*0];
		b_3 = B[3+bs*0];
			
		c_00 += a_0 * b_0;

		c_01 += a_0 * b_1;

		c_02 += a_0 * b_2;

		c_03 += a_0 * b_3;

		A += 4;
		B += 4;
		k += 1;

		}

	if(ksub>0)
		{
		if(kadd>0)
			{
			A += bs*((d_ncl-kadd%d_ncl)%d_ncl);
			B += bs*((d_ncl-kadd%d_ncl)%d_ncl);
			}
		}

	for(k=0; k<ksub-3; k+=4)
		{
		
		a_0 = A[0+bs*0];
		a_1 = A[1+bs*0];
		
		b_0 = B[0+bs*0];
		b_1 = B[1+bs*0];
		b_2 = B[2+bs*0];
		b_3 = B[3+bs*0];
		
		c_00 -= a_0 * b_0;
		c_10 -= a_1 * b_0;

		c_01 -= a_0 * b_1;
		c_11 -= a_1 * b_1;

		c_02 -= a_0 * b_2;
		c_12 -= a_1 * b_2;

		c_03 -= a_0 * b_3;
		c_13 -= a_1 * b_3;


		a_0 = A[0+bs*1];
		a_1 = A[1+bs*1];
		
		b_0 = B[0+bs*1];
		b_1 = B[1+bs*1];
		b_2 = B[2+bs*1];
		b_3 = B[3+bs*1];
		
		c_00 -= a_0 * b_0;
		c_10 -= a_1 * b_0;

		c_01 -= a_0 * b_1;
		c_11 -= a_1 * b_1;

		c_02 -= a_0 * b_2;
		c_12 -= a_1 * b_2;

		c_03 -= a_0 * b_3;
		c_13 -= a_1 * b_3;


		a_0 = A[0+bs*2];
		a_1 = A[1+bs*2];
		
		b_0 = B[0+bs*2];
		b_1 = B[1+bs*2];
		b_2 = B[2+bs*2];
		b_3 = B[3+bs*2];
		
		c_00 -= a_0 * b_0;
		c_10 -= a_1 * b_0;

		c_01 -= a_0 * b_1;
		c_11 -= a_1 * b_1;

		c_02 -= a_0 * b_2;
		c_12 -= a_1 * b_2;

		c_03 -= a_0 * b_3;
		c_13 -= a_1 * b_3;


		a_0 = A[0+bs*3];
		a_1 = A[1+bs*3];
		
		b_0 = B[0+bs*3];
		b_1 = B[1+bs*3];
		b_2 = B[2+bs*3];
		b_3 = B[3+bs*3];
		
		c_00 -= a_0 * b_0;
		c_10 -= a_1 * b_0;

		c_01 -= a_0 * b_1;
		c_11 -= a_1 * b_1;

		c_02 -= a_0 * b_2;
		c_12 -= a_1 * b_2;

		c_03 -= a_0 * b_3;
		c_13 -= a_1 * b_3;
		
		
		A += 16;
		B += 16;

		}

	if(alg!=0)
		{
		c_00 += C[0+bs*0];
		c_10 += C[1+bs*0];

		c_01 += C[0+bs*1];
		c_11 += C[1+bs*1];

		c_02 += C[0+bs*2];
		c_12 += C[1+bs*2];

		c_03 += C[0+bs*3];
		c_13 += C[1+bs*3];
		}
	
	// dtrsm
	double
		a_00, a_10, a_20, a_30, a_11, a_21, a_31, a_22, a_32, a_33;
	
	a_00 = fact[0];
	c_00 *= a_00;
	c_10 *= a_00;
	D[0+bs*0] = c_00;
	D[1+bs*0] = c_10;

	a_10 = fact[1];
	a_11 = fact[2];
	c_01 -= c_00*a_10;
	c_11 -= c_10*a_10;
	c_01 *= a_11;
	c_11 *= a_11;
	D[0+bs*1] = c_01;
	D[1+bs*1] = c_11;

	a_20 = fact[3];
	a_21 = fact[4];
	a_22 = fact[5];
	c_02 -= c_00*a_20;
	c_12 -= c_10*a_20;
	c_02 -= c_01*a_21;
	c_12 -= c_11*a_21;
	c_02 *= a_22;
	c_12 *= a_22;
	D[0+bs*2] = c_02;
	D[1+bs*2] = c_12;

	a_30 = fact[6];
	a_31 = fact[7];
	a_32 = fact[8];
	a_33 = fact[9];
	c_03 -= c_00*a_30;
	c_13 -= c_10*a_30;
	c_03 -= c_01*a_31;
	c_13 -= c_11*a_31;
	c_03 -= c_02*a_32;
	c_13 -= c_12*a_32;
	c_03 *= a_33;
	c_13 *= a_33;
	D[0+bs*3] = c_03;
	D[1+bs*3] = c_13;

	}
	
	
	
// A is upper triangular
void kernel_dtrmm_dtrsm_nt_2x2_lib4(int kadd, int ksub, double *A, double *B, double *C, double *D, double *fact, int alg)
	{

	const int bs = 4;
	const int d_ncl = D_NCL;

	int k;

	double
		a_0, a_1,
		b_0, b_1,
		c_00=0, c_01=0,
		c_10=0, c_11=0;

	// initialize loop counter
	k = 0;

	if(kadd>=2)
		{

		// initial triangle

		// k=0
		a_0 = A[0+bs*0];
			
		b_0 = B[0+bs*0];
		b_1 = B[1+bs*0];
			
		c_00 += a_0 * b_0;

		c_01 += a_0 * b_1;


		// k=1
		a_0 = A[0+bs*1];
		a_1 = A[1+bs*1];
			
		b_0 = B[0+bs*1];
		b_1 = B[1+bs*1];
			
		c_00 += a_0 * b_0;
		c_10 += a_1 * b_0;

		c_01 += a_0 * b_1;
		c_11 += a_1 * b_1;


		A += 8;
		B += 8;
		k = 2;
			

			
		for(; k<kadd-3; k+=4)
			{
			
			a_0 = A[0+bs*0];
			a_1 = A[1+bs*0];
			
			b_0 = B[0+bs*0];
			b_1 = B[1+bs*0];
			
			c_00 += a_0 * b_0;
			c_10 += a_1 * b_0;

			c_01 += a_0 * b_1;
			c_11 += a_1 * b_1;


			a_0 = A[0+bs*1];
			a_1 = A[1+bs*1];
			
			b_0 = B[0+bs*1];
			b_1 = B[1+bs*1];
			
			c_00 += a_0 * b_0;
			c_10 += a_1 * b_0;

			c_01 += a_0 * b_1;
			c_11 += a_1 * b_1;


			a_0 = A[0+bs*2];
			a_1 = A[1+bs*2];
			
			b_0 = B[0+bs*2];
			b_1 = B[1+bs*2];
			
			c_00 += a_0 * b_0;
			c_10 += a_1 * b_0;

			c_01 += a_0 * b_1;
			c_11 += a_1 * b_1;


			a_0 = A[0+bs*3];
			a_1 = A[1+bs*3];
			
			b_0 = B[0+bs*3];
			b_1 = B[1+bs*3];
			
			c_00 += a_0 * b_0;
			c_10 += a_1 * b_0;

			c_01 += a_0 * b_1;
			c_11 += a_1 * b_1;
			
			
			A += 16;
			B += 16;

			}
		for(; k<kadd; k++)
			{
			
			a_0 = A[0+bs*0];
			a_1 = A[1+bs*0];
			
			b_0 = B[0+bs*0];
			b_1 = B[1+bs*0];
			
			c_00 += a_0 * b_0;
			c_10 += a_1 * b_0;

			c_01 += a_0 * b_1;
			c_11 += a_1 * b_1;


			A += 4;
			B += 4;

			}
		}
	else if(kadd>0)
		{

		// k = 0
		a_0 = A[0+bs*0];
			
		b_0 = B[0+bs*0];
		b_1 = B[1+bs*0];
			
		c_00 += a_0 * b_0;

		c_01 += a_0 * b_1;

		A += 4;
		B += 4;
		k += 1;

		}

	if(ksub>0)
		{
		if(kadd>0)
			{
			A += bs*((d_ncl-kadd%d_ncl)%d_ncl);
			B += bs*((d_ncl-kadd%d_ncl)%d_ncl);
			}
		}

	for(k=0; k<ksub-3; k+=4)
		{
		
		a_0 = A[0+bs*0];
		a_1 = A[1+bs*0];
		
		b_0 = B[0+bs*0];
		b_1 = B[1+bs*0];
		
		c_00 -= a_0 * b_0;
		c_10 -= a_1 * b_0;

		c_01 -= a_0 * b_1;
		c_11 -= a_1 * b_1;


		a_0 = A[0+bs*1];
		a_1 = A[1+bs*1];
		
		b_0 = B[0+bs*1];
		b_1 = B[1+bs*1];
		
		c_00 -= a_0 * b_0;
		c_10 -= a_1 * b_0;

		c_01 -= a_0 * b_1;
		c_11 -= a_1 * b_1;


		a_0 = A[0+bs*2];
		a_1 = A[1+bs*2];
		
		b_0 = B[0+bs*2];
		b_1 = B[1+bs*2];
		
		c_00 -= a_0 * b_0;
		c_10 -= a_1 * b_0;

		c_01 -= a_0 * b_1;
		c_11 -= a_1 * b_1;


		a_0 = A[0+bs*3];
		a_1 = A[1+bs*3];
		
		b_0 = B[0+bs*3];
		b_1 = B[1+bs*3];
		
		c_00 -= a_0 * b_0;
		c_10 -= a_1 * b_0;

		c_01 -= a_0 * b_1;
		c_11 -= a_1 * b_1;
		
		
		A += 16;
		B += 16;

		}

	if(alg!=0)
		{
		c_00 += C[0+bs*0];
		c_10 += C[1+bs*0];

		c_01 += C[0+bs*1];
		c_11 += C[1+bs*1];
		}
	
	// dtrsm
	double
		a_00, a_10, a_11;
	
	a_00 = fact[0];
	c_00 *= a_00;
	c_10 *= a_00;
	D[0+bs*0] = c_00;
	D[1+bs*0] = c_10;

	a_10 = fact[1];
	a_11 = fact[2];
	c_01 -= c_00*a_10;
	c_11 -= c_10*a_10;
	c_01 *= a_11;
	c_11 *= a_11;
	D[0+bs*1] = c_01;
	D[1+bs*1] = c_11;

	}
#endif
	
	
	


