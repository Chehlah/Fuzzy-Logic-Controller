/*
	Topic : Fuzzy logic control (Homework, Study case)
	Author : Aufa Ch.
	Last edit: 10/14/2017 (mm/dd/yy)
	****************************************************
	File input:
		input.txt
		memberIn1.txt
		memberIn1_out.txt
		memberIn2.txt
		memberIn2_out.txt
		memberOut.txt
		memberOut_sort.txt
		rule_table.txt
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

// Parameters input
char	in1_name[5],in2_name[5];
int 	in1_row,in2_colum,out_member;	
float 	in1_input, in2_input,
		in1_p1,    in1_p2,
		in2_p1,    in2_p2;
char	in1_member1[5], in1_member2[5],
		in2_member1[5], in2_member2[5];
// Parameters for Rule Table 
float	t1_p1, t1_p2,
		t2_p1, t2_p2;
char	t1_mem1[5],t1_mem2[5],
		t2_mem1[5],t2_mem2[5];
//	Parameters output from Rule Table
char	out_mem1[5],out_mem2[5],out_mem3[5],out_mem4[5];
float	out_p1,out_p2,out_p3,out_p4;
// 	Parameters after sorting 
char	s_mem1[5],s_mem2[5],s_mem3[5],s_mem4[5];
float	s_p1,s_p2,s_p3,s_p4;

void input(void);
void memberIn1(void);
void memberIn2(void);
void memberIn1_out(void);
void memberIn2_out(void);
void rule_table(void);
void rule_table_min(void);
void rule_table_max(void);
void merber_output(void);
float defuzzifier(int check);
int sort_member(void);

int main(){
	// Step 1 input value and find membership with percent
	input();
	printf("Membership of Input 1:\n");
	memberIn1();
	memberIn1_out();
	printf("Membership of Input 2:\n");
	memberIn2();
	memberIn2_out();
	// Step 2 
	printf("Membership from Rule Table:\n");
	rule_table();
	// Step 3
	printf("Membership of Output:\n");
	merber_output();
	// Step 4
	printf("After sorting membership output:\n");
	int check;
	check = sort_member();
	float ans;
	ans = defuzzifier(check-1);
	printf("Output is: %f\n",ans);
	return 0;
}
float defuzzifier(int check){
	float	left, right, slope, c;
	float	x_limit,x_limit_2, sum_y=0, sum_xy=0,y,x;
	int i;
	char s[5];
	FILE *file;
	file = fopen("memberOut.txt","r");
	fscanf(file,"%d",&i);
	if(check == 1){
		while(i>0){
			fscanf(file,"%s",s); 
			if(!strcmp(s_mem1,s)){ //Zone 1
				fscanf(file,"%f",&left); fscanf(file,"%f",&right);
				fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
				if(slope == 0.0 && c == 0.0){
				}else{
					x_limit = (s_p1 - c) / slope;
					for(x=left; x < x_limit; x+=0.001){
						y = (slope*x) + c;
						sum_xy = sum_xy + (y*x);
						sum_y = sum_y + y;
					}
					for (x=x_limit; x < right; x+=0.001){
						y = s_p1;
						sum_xy = sum_xy + (y*x);
						sum_y = sum_y + y;
					}
				}
				fscanf(file,"%f",&left); fscanf(file,"%f",&right);
				fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
				if(slope == 0.0 && c == 0.0){
				}else{ // Zone 2
					if(slope == 0.0){ // big bug when slope == 0 !!!!!!
						for(x=left; x <= right; x+=0.001){
							y = s_p1;
							sum_xy = sum_xy + (y*x);
							sum_y = sum_y + y;
						}
					}
					else{
						x_limit = (s_p1 - c) / slope;
						for(x=left; x < x_limit; x+=0.001){
							y = s_p1;
							sum_xy = sum_xy + (y*x);
							sum_y = sum_y + y;
						}
						for (x=x_limit; x <= right; x+=0.001){
							y = (slope*x) + c;
							sum_xy = sum_xy + (y*x);
							sum_y = sum_y + y;
						}
					}
				}
			}
			else{
				fscanf(file,"%f",&left); fscanf(file,"%f",&right);
				fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
				fscanf(file,"%f",&left); fscanf(file,"%f",&right);
				fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
			}		
			i--;
		}
		return sum_xy/sum_y;
	}
	if(check == 2){
		while(i>0){
			fscanf(file,"%s",s); 
			if(!strcmp(s_mem1,s))
			{
				// Zone 1
				fscanf(file,"%f",&left); fscanf(file,"%f",&right);
				fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
				if(slope == 0.0 && c == 0.0){
				}else{
					x_limit = (s_p1 - c) / slope;
					for(x=left; x < x_limit; x+=0.001){
						y = (slope*x) + c;
						sum_xy = sum_xy + (y*x);
						sum_y = sum_y + y;
					}
					for (x=x_limit; x < right; x+=0.001){
						y = s_p1;
						sum_xy = sum_xy + (y*x);
						sum_y = sum_y + y;
					}
				}
				// Zone 2
				fscanf(file,"%f",&left); fscanf(file,"%f",&right);
				fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
				fscanf(file,"%s",s);
				if(!strcmp(s_mem2,s)){
					if(s_p1 >= 0.5 && s_p2 >= 0.5){
						x_limit = (s_p1 - c) / slope;
						for (x=left; x < x_limit; x+=0.001){
							y = s_p1;
							sum_xy = sum_xy + (y*x);
							sum_y = sum_y + y;
						}
						for (x=x_limit; x < 0.5; x+=0.001){
							y = (slope*x) + c;
							sum_xy = sum_xy + (y*x);
							sum_y = sum_y + y;
						}
						fscanf(file,"%f",&left); fscanf(file,"%f",&right);
						fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
						x_limit = (s_p2 - c) / slope;
						for (x=0.5; x < x_limit; x+=0.001){
							y = (slope*x) + c;
							sum_xy = sum_xy + (y*x);
							sum_y = sum_y + y;
						}
						for (x=x_limit; x < right; x+=0.001){
							y = s_p1;
							sum_xy = sum_xy + (y*x);
							sum_y = sum_y + y;
						}
					}
					else if(s_p1 > s_p2){
						x_limit = (s_p1 - c) / slope;
						for (x=left; x < x_limit; x+=0.001){
							y = s_p1;
							sum_xy = sum_xy + (y*x);
							sum_y = sum_y + y;
						}
						x_limit_2 = (s_p2 - c) / slope;
						for (x=x_limit; x < x_limit_2; x+=0.001){
							y = (slope*x) + c;
							sum_xy = sum_xy + (y*x);
							sum_y = sum_y + y;
						}
						for (x=x_limit_2; x < right; x+=0.001){
							y = s_p2;
							sum_xy = sum_xy + (y*x);
							sum_y = sum_y + y;
						}
						fscanf(file,"%f",&left); fscanf(file,"%f",&right);
						fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
					}
					else if(s_p2 >= s_p1){
						fscanf(file,"%f",&left); fscanf(file,"%f",&right);
						fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
						x_limit = (s_p1 - c) / slope;
						for (x=left; x < x_limit; x+=0.001){
							y = s_p1;
							sum_xy = sum_xy + (y*x);
							sum_y = sum_y + y;
						}
						x_limit_2 = (s_p2 - c) / slope;
						for (x=x_limit; x < x_limit_2; x+=0.001){
							y = (slope*x) + c;
							sum_xy = sum_xy + (y*x);
							sum_y = sum_y + y;
						}
						for (x=x_limit_2; x < right; x+=0.001){
							y = s_p2;
							sum_xy = sum_xy + (y*x);
							sum_y = sum_y + y;
						}
					}
					// Zone 3
					fscanf(file,"%f",&left); fscanf(file,"%f",&right);
					fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
					if(slope == 0.0 && c == 0.0){
					}else{
						if(slope == 0.0){ // big bug when slope == 0 !!!!!!
							for(x=left; x <= right; x+=0.001){
								y = s_p2;
								sum_xy = sum_xy + (y*x);
								sum_y = sum_y + y;
							}
						}
						else{
							x_limit = (s_p2 - c) / slope;
							for(x=left; x < x_limit; x+=0.001){
								y = s_p2;
								sum_xy = sum_xy + (y*x);
								sum_y = sum_y + y;
							}
							for (x=x_limit; x <= right; x+=0.001){
								y = (slope*x) + c;
								sum_xy = sum_xy + (y*x);
								sum_y = sum_y + y;
							}
						}
					}
				}
				else{ // Zone 2
					x_limit = (s_p1 - c) / slope;
					for(x=left; x < x_limit; x+=0.001){
						y = s_p1;
						sum_xy = sum_xy + (y*x);
						sum_y = sum_y + y;
					}
					for (x=x_limit; x <= right; x+=0.001){
						y = (slope*x) + c;
						sum_xy = sum_xy + (y*x);
						sum_y = sum_y + y;
					}
					fscanf(file,"%f",&left); fscanf(file,"%f",&right);
					fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
					fscanf(file,"%f",&left); fscanf(file,"%f",&right);
					fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
					while(i>0){
						fscanf(file,"%s",s);
						if(!strcmp(s_mem2,s)){ 
							fscanf(file,"%f",&left); fscanf(file,"%f",&right);
							fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
							x_limit = (s_p2 - c) / slope; // Zone 3
							for(x=left; x < x_limit; x+=0.001){
								y = (slope*x) + c;
								sum_xy = sum_xy + (y*x);
								sum_y = sum_y + y;
							}
							for (x=x_limit; x < right; x+=0.001){
								y = s_p2;
								sum_xy = sum_xy + (y*x);
								sum_y = sum_y + y;
							}
							fscanf(file,"%f",&left); fscanf(file,"%f",&right);
							fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
							x_limit = (s_p2 - c) / slope; // Zone 4
							for(x=left; x < x_limit; x+=0.001){
								y = s_p2;
								sum_xy = sum_xy + (y*x);
								sum_y = sum_y + y;
							}
							for (x=x_limit; x <= right; x+=0.001){
								y = (slope*x) + c;
								sum_xy = sum_xy + (y*x);
								sum_y = sum_y + y;
							}
						}
						else{
							fscanf(file,"%f",&left); fscanf(file,"%f",&right);
							fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
							fscanf(file,"%f",&left); fscanf(file,"%f",&right);
							fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
						}
						i--;
					}
				}
			}
			else
			{
				fscanf(file,"%f",&left); fscanf(file,"%f",&right);
				fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
				fscanf(file,"%f",&left); fscanf(file,"%f",&right);
				fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
			}		
			i--;
		}
		return sum_xy/sum_y;
	}
	if(check == 3){
		while(i>0){
			fscanf(file,"%s",s); 
			if(!strcmp(s_mem1,s))
			{
				// Zone 1
				fscanf(file,"%f",&left); fscanf(file,"%f",&right);
				fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
				if(slope == 0.0 && c == 0.0){
				}else{
					x_limit = (s_p1 - c) / slope;
					for(x=left; x < x_limit; x+=0.001){
						y = (slope*x) + c;
						sum_xy = sum_xy + (y*x);
						sum_y = sum_y + y;
					}
					for (x=x_limit; x < right; x+=0.001){
						y = s_p1;
						sum_xy = sum_xy + (y*x);
						sum_y = sum_y + y;
					}
				}
				// Zone 2
				fscanf(file,"%f",&left); fscanf(file,"%f",&right);
				fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
				fscanf(file,"%s",s);
				if(!strcmp(s_mem2,s)){
					if(s_p1 >= 0.5 && s_p2 >= 0.5){
						x_limit = (s_p1 - c) / slope;
						for (x=left; x < x_limit; x+=0.001){
							y = s_p1;
							sum_xy = sum_xy + (y*x);
							sum_y = sum_y + y;
						}
						for (x=x_limit; x < 0.5; x+=0.001){
							y = (slope*x) + c;
							sum_xy = sum_xy + (y*x);
							sum_y = sum_y + y;
						}
						fscanf(file,"%f",&left); fscanf(file,"%f",&right);
						fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
						x_limit = (s_p2 - c) / slope;
						for (x=0.5; x < x_limit; x+=0.001){
							y = (slope*x) + c;
							sum_xy = sum_xy + (y*x);
							sum_y = sum_y + y;
						}
						for (x=x_limit; x < right; x+=0.001){
							y = s_p1;
							sum_xy = sum_xy + (y*x);
							sum_y = sum_y + y;
						}
					}
					else if(s_p1 > s_p2){
						x_limit = (s_p1 - c) / slope;
						for (x=left; x < x_limit; x+=0.001){
							y = s_p1;
							sum_xy = sum_xy + (y*x);
							sum_y = sum_y + y;
						}
						x_limit_2 = (s_p2 - c) / slope;
						for (x=x_limit; x < x_limit_2; x+=0.001){
							y = (slope*x) + c;
							sum_xy = sum_xy + (y*x);
							sum_y = sum_y + y;
						}
						for (x=x_limit_2; x < right; x+=0.001){
							y = s_p2;
							sum_xy = sum_xy + (y*x);
							sum_y = sum_y + y;
						}
						fscanf(file,"%f",&left); fscanf(file,"%f",&right);
						fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
					}
					else if(s_p2 >= s_p1){
						fscanf(file,"%f",&left); fscanf(file,"%f",&right);
						fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
						x_limit = (s_p1 - c) / slope;
						for (x=left; x < x_limit; x+=0.001){
							y = s_p1;
							sum_xy = sum_xy + (y*x);
							sum_y = sum_y + y;
						}
						x_limit_2 = (s_p2 - c) / slope;
						for (x=x_limit; x < x_limit_2; x+=0.001){
							y = (slope*x) + c;
							sum_xy = sum_xy + (y*x);
							sum_y = sum_y + y;
						}
						for (x=x_limit_2; x < right; x+=0.001){
							y = s_p2;
							sum_xy = sum_xy + (y*x);
							sum_y = sum_y + y;
						}
					}
					// Zone 3
					fscanf(file,"%f",&left); fscanf(file,"%f",&right);
					fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
					fscanf(file,"%s",s);
					if(s_p2 >= 0.5 && s_p3 >= 0.5){
						x_limit = (s_p2 - c) / slope;
						for (x=left; x < x_limit; x+=0.001){
							y = s_p2;
							sum_xy = sum_xy + (y*x);
							sum_y = sum_y + y;
						}
						for (x=x_limit; x < 0.5; x+=0.001){
							y = (slope*x) + c;
							sum_xy = sum_xy + (y*x);
							sum_y = sum_y + y;
						}
						fscanf(file,"%f",&left); fscanf(file,"%f",&right);
						fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
						x_limit = (s_p3 - c) / slope;
						for (x=0.5; x < x_limit; x+=0.001){
							y = (slope*x) + c;
							sum_xy = sum_xy + (y*x);
							sum_y = sum_y + y;
						}
						for (x=x_limit; x < right; x+=0.001){
							y = s_p2;
							sum_xy = sum_xy + (y*x);
							sum_y = sum_y + y;
						}
					}
					else if(s_p2 > s_p3){
						x_limit = (s_p2 - c) / slope;
						for (x=left; x < x_limit; x+=0.001){
							y = s_p2;
							sum_xy = sum_xy + (y*x);
							sum_y = sum_y + y;
						}
						x_limit_2 = (s_p3 - c) / slope;
						for (x=x_limit; x < x_limit_2; x+=0.001){
							y = (slope*x) + c;
							sum_xy = sum_xy + (y*x);
							sum_y = sum_y + y;
						}
						for (x=x_limit_2; x < right; x+=0.001){
							y = s_p3;
							sum_xy = sum_xy + (y*x);
							sum_y = sum_y + y;
						}
						fscanf(file,"%f",&left); fscanf(file,"%f",&right);
						fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
					}
					else if(s_p3 >= s_p2){
						fscanf(file,"%f",&left); fscanf(file,"%f",&right);
						fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
						x_limit = (s_p2 - c) / slope;
						for (x=left; x < x_limit; x+=0.001){
							y = s_p2;
							sum_xy = sum_xy + (y*x);
							sum_y = sum_y + y;
						}
						x_limit_2 = (s_p3 - c) / slope;
						for (x=x_limit; x < x_limit_2; x+=0.001){
							y = (slope*x) + c;
							sum_xy = sum_xy + (y*x);
							sum_y = sum_y + y;
						}
						for (x=x_limit_2; x < right; x+=0.001){
							y = s_p3;
							sum_xy = sum_xy + (y*x);
							sum_y = sum_y + y;
						}
					}
					// Zone 4
					fscanf(file,"%f",&left); fscanf(file,"%f",&right);
					fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
					if(slope == 0.0 && c == 0.0){
					}else{
						if(slope == 0.0){ // big bug when slope == 0 !!!!!!
							for(x=left; x <= right; x+=0.001){
								y = s_p3;
								sum_xy = sum_xy + (y*x);
								sum_y = sum_y + y;
							}
						}
						else{
							x_limit = (s_p3 - c) / slope;
							for(x=left; x < x_limit; x+=0.001){
								y = s_p3;
								sum_xy = sum_xy + (y*x);
								sum_y = sum_y + y;
							}
							for (x=x_limit; x <= right; x+=0.001){
								y = (slope*x) + c;
								sum_xy = sum_xy + (y*x);
								sum_y = sum_y + y;
							}
						}
					}
				}
				else{// Zone 2
					x_limit = (s_p1 - c) / slope;
					for(x=left; x < x_limit; x+=0.001){
						y = s_p1;
						sum_xy = sum_xy + (y*x);
						sum_y = sum_y + y;
					}
					for (x=x_limit; x <= right; x+=0.001){
						y = (slope*x) + c;
						sum_xy = sum_xy + (y*x);
						sum_y = sum_y + y;
					}
					fscanf(file,"%f",&left); fscanf(file,"%f",&right);
					fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
					fscanf(file,"%f",&left); fscanf(file,"%f",&right);
					fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
					while(i>0){
						fscanf(file,"%s",s);
						if(!strcmp(s_mem2,s)){
							// Zone 3
							fscanf(file,"%f",&left); fscanf(file,"%f",&right);
							fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
							if(slope == 0.0 && c == 0.0){
							}else{
								x_limit = (s_p2 - c) / slope;
								for(x=left; x < x_limit; x+=0.001){
									y = (slope*x) + c;
									sum_xy = sum_xy + (y*x);
									sum_y = sum_y + y;
								}
								for (x=x_limit; x < right; x+=0.001){
									y = s_p2;
									sum_xy = sum_xy + (y*x);
									sum_y = sum_y + y;
								}
							}
							// Zone 4
							fscanf(file,"%f",&left); fscanf(file,"%f",&right);
							fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
							fscanf(file,"%s",s);
							if(s_p2 >= 0.5 && s_p3 >= 0.5){
								x_limit = (s_p2 - c) / slope;
								for (x=left; x < x_limit; x+=0.001){
									y = s_p2;
									sum_xy = sum_xy + (y*x);
									sum_y = sum_y + y;
								}
								for (x=x_limit; x < 0.5; x+=0.001){
									y = (slope*x) + c;
									sum_xy = sum_xy + (y*x);
									sum_y = sum_y + y;
								}
								fscanf(file,"%f",&left); fscanf(file,"%f",&right);
								fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
								x_limit = (s_p3 - c) / slope;
								for (x=0.5; x < x_limit; x+=0.001){
									y = (slope*x) + c;
									sum_xy = sum_xy + (y*x);
									sum_y = sum_y + y;
								}
								for (x=x_limit; x < right; x+=0.001){
									y = s_p3;
									sum_xy = sum_xy + (y*x);
									sum_y = sum_y + y;
								}
							}
							else if(s_p2 > s_p3){
								x_limit = (s_p2 - c) / slope;
								for (x=left; x < x_limit; x+=0.001){
									y = s_p2;
									sum_xy = sum_xy + (y*x);
									sum_y = sum_y + y;
								}
								x_limit_2 = (s_p3 - c) / slope;
								for (x=x_limit; x < x_limit_2; x+=0.001){
									y = (slope*x) + c;
									sum_xy = sum_xy + (y*x);
									sum_y = sum_y + y;
								}
								for (x=x_limit_2; x < right; x+=0.001){
									y = s_p3;
									sum_xy = sum_xy + (y*x);
									sum_y = sum_y + y;
								}
								fscanf(file,"%f",&left); fscanf(file,"%f",&right);
								fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
							}
							else if(s_p3 >= s_p2){
								fscanf(file,"%f",&left); fscanf(file,"%f",&right);
								fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
								x_limit = (s_p2 - c) / slope;
								for (x=left; x < x_limit; x+=0.001){
									y = s_p2;
									sum_xy = sum_xy + (y*x);
									sum_y = sum_y + y;
								}
								x_limit_2 = (s_p3 - c) / slope;
								for (x=x_limit; x < x_limit_2; x+=0.001){
									y = (slope*x) + c;
									sum_xy = sum_xy + (y*x);
									sum_y = sum_y + y;
								}
								for (x=x_limit_2; x < right; x+=0.001){
									y = s_p3;
									sum_xy = sum_xy + (y*x);
									sum_y = sum_y + y;
								}
							}
							// Zone 5
							fscanf(file,"%f",&left); fscanf(file,"%f",&right);
							fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
							if(slope == 0.0 && c == 0.0){
							}else{
								if(slope == 0.0){ // big bug when slope == 0 !!!!!!
									for(x=left; x <= right; x+=0.001){
										y = s_p3;
										sum_xy = sum_xy + (y*x);
										sum_y = sum_y + y;
									}
								}
								else{
									x_limit = (s_p3 - c) / slope;
									for(x=left; x < x_limit; x+=0.001){
										y = s_p3;
										sum_xy = sum_xy + (y*x);
										sum_y = sum_y + y;
									}
									for (x=x_limit; x <= right; x+=0.001){
										y = (slope*x) + c;
										sum_xy = sum_xy + (y*x);
										sum_y = sum_y + y;
									}
								}
							}
						}
						else{
							fscanf(file,"%f",&left); fscanf(file,"%f",&right);
							fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
							fscanf(file,"%f",&left); fscanf(file,"%f",&right);
							fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
						}

						i--;
					}

				}
			}
			else
			{
				fscanf(file,"%f",&left); fscanf(file,"%f",&right);
				fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
				fscanf(file,"%f",&left); fscanf(file,"%f",&right);
				fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
			}		
			i--;
		}
		return sum_xy/sum_y;
	}
	if(check == 4){
		while(i>0){
			fscanf(file,"%s",s); 
			if(!strcmp(s_mem1,s))
			{
				// Zone 1
				fscanf(file,"%f",&left); fscanf(file,"%f",&right);
				fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
				if(slope == 0.0 && c == 0.0){
				}else{
					x_limit = (s_p1 - c) / slope;
					for(x=left; x < x_limit; x+=0.001){
						y = (slope*x) + c;
						sum_xy = sum_xy + (y*x);
						sum_y = sum_y + y;
					}
					for (x=x_limit; x < right; x+=0.001){
						y = s_p1;
						sum_xy = sum_xy + (y*x);
						sum_y = sum_y + y;
					}
				}
				// Zone 2
				if(s_p1 >= 0.5 && s_p2 >= 0.5){
					fscanf(file,"%f",&left); fscanf(file,"%f",&right);
					fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
					fscanf(file,"%s",s);
					x_limit = (s_p1 - c) / slope;
					for (x=left; x < x_limit; x+=0.001){
						y = s_p1;
						sum_xy = sum_xy + (y*x);
						sum_y = sum_y + y;
					}
					for (x=x_limit; x < 0.5; x+=0.001){
						y = (slope*x) + c;
						sum_xy = sum_xy + (y*x);
						sum_y = sum_y + y;
					}
					fscanf(file,"%f",&left); fscanf(file,"%f",&right);
					fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
					x_limit = (s_p2 - c) / slope;
					for (x=0.5; x < x_limit; x+=0.001){
						y = (slope*x) + c;
						sum_xy = sum_xy + (y*x);
						sum_y = sum_y + y;
					}
					for (x=x_limit; x < right; x+=0.001){
						y = s_p1;
						sum_xy = sum_xy + (y*x);
						sum_y = sum_y + y;
					}
				}
				else if(s_p1 > s_p2){
					fscanf(file,"%f",&left); fscanf(file,"%f",&right);
					fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
					fscanf(file,"%s",s);
					x_limit = (s_p1 - c) / slope;
					for (x=left; x < x_limit; x+=0.001){
						y = s_p1;
						sum_xy = sum_xy + (y*x);
						sum_y = sum_y + y;
					}
					x_limit_2 = (s_p2 - c) / slope;
					for (x=x_limit; x < x_limit_2; x+=0.001){
						y = (slope*x) + c;
						sum_xy = sum_xy + (y*x);
						sum_y = sum_y + y;
					}
					for (x=x_limit_2; x < right; x+=0.001){
						y = s_p2;
						sum_xy = sum_xy + (y*x);
						sum_y = sum_y + y;
					}
					fscanf(file,"%f",&left); fscanf(file,"%f",&right);
					fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
				}
				else if(s_p2 >= s_p1){
					fscanf(file,"%f",&left); fscanf(file,"%f",&right);
					fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
					fscanf(file,"%s",s);
					fscanf(file,"%f",&left); fscanf(file,"%f",&right);
					fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
					x_limit = (s_p1 - c) / slope;
					for (x=left; x < x_limit; x+=0.001){
						y = s_p1;
						sum_xy = sum_xy + (y*x);
						sum_y = sum_y + y;
					}
					x_limit_2 = (s_p2 - c) / slope;
					for (x=x_limit; x < x_limit_2; x+=0.001){
						y = (slope*x) + c;
						sum_xy = sum_xy + (y*x);
						sum_y = sum_y + y;
					}
					for (x=x_limit_2; x < right; x+=0.001){
						y = s_p2;
						sum_xy = sum_xy + (y*x);
						sum_y = sum_y + y;
					}
				}
				// Zone 3
				if(s_p2 >= 0.5 && s_p3 >= 0.5){
					fscanf(file,"%f",&left); fscanf(file,"%f",&right);
					fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
					fscanf(file,"%s",s);
					x_limit = (s_p2 - c) / slope;
					for (x=left; x < x_limit; x+=0.001){
						y = s_p2;
						sum_xy = sum_xy + (y*x);
						sum_y = sum_y + y;
					}
					for (x=x_limit; x < 0.5; x+=0.001){
						y = (slope*x) + c;
						sum_xy = sum_xy + (y*x);
						sum_y = sum_y + y;
					}
					fscanf(file,"%f",&left); fscanf(file,"%f",&right);
					fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
					x_limit = (s_p3 - c) / slope;
					for (x=0.5; x < x_limit; x+=0.001){
						y = (slope*x) + c;
						sum_xy = sum_xy + (y*x);
						sum_y = sum_y + y;
					}
					for (x=x_limit; x < right; x+=0.001){
						y = s_p2;
						sum_xy = sum_xy + (y*x);
						sum_y = sum_y + y;
					}
				}
				else if(s_p2 > s_p3){
					fscanf(file,"%f",&left); fscanf(file,"%f",&right);
					fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
					fscanf(file,"%s",s);
					x_limit = (s_p2 - c) / slope;
					for (x=left; x < x_limit; x+=0.001){
						y = s_p2;
						sum_xy = sum_xy + (y*x);
						sum_y = sum_y + y;
					}
					x_limit_2 = (s_p3 - c) / slope;
					for (x=x_limit; x < x_limit_2; x+=0.001){
						y = (slope*x) + c;
						sum_xy = sum_xy + (y*x);
						sum_y = sum_y + y;
					}
					for (x=x_limit_2; x < right; x+=0.001){
						y = s_p3;
						sum_xy = sum_xy + (y*x);
						sum_y = sum_y + y;
					}
					fscanf(file,"%f",&left); fscanf(file,"%f",&right);
					fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
				}
				else if(s_p3 >= s_p2){
					fscanf(file,"%f",&left); fscanf(file,"%f",&right);
					fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
					fscanf(file,"%s",s);
					fscanf(file,"%f",&left); fscanf(file,"%f",&right);
					fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
					x_limit = (s_p2 - c) / slope;
					for (x=left; x < x_limit; x+=0.001){
						y = s_p2;
						sum_xy = sum_xy + (y*x);
						sum_y = sum_y + y;
					}
					x_limit_2 = (s_p3 - c) / slope;
					for (x=x_limit; x < x_limit_2; x+=0.001){
						y = (slope*x) + c;
						sum_xy = sum_xy + (y*x);
						sum_y = sum_y + y;
					}
					for (x=x_limit_2; x < right; x+=0.001){
						y = s_p3;
						sum_xy = sum_xy + (y*x);
						sum_y = sum_y + y;
					}
				}
				// Zone 4
				if(s_p3 >= 0.5 && s_p4 >= 0.5){
					fscanf(file,"%f",&left); fscanf(file,"%f",&right);
					fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
					fscanf(file,"%s",s);
					x_limit = (s_p3 - c) / slope;
					for (x=left; x < x_limit; x+=0.001){
						y = s_p3;
						sum_xy = sum_xy + (y*x);
						sum_y = sum_y + y;
					}
					for (x=x_limit; x < 0.5; x+=0.001){
						y = (slope*x) + c;
						sum_xy = sum_xy + (y*x);
						sum_y = sum_y + y;
					}
					fscanf(file,"%f",&left); fscanf(file,"%f",&right);
					fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
					x_limit = (s_p4 - c) / slope;
					for (x=0.5; x < x_limit; x+=0.001){
						y = (slope*x) + c;
						sum_xy = sum_xy + (y*x);
						sum_y = sum_y + y;
					}
					for (x=x_limit; x < right; x+=0.001){
						y = s_p3;
						sum_xy = sum_xy + (y*x);
						sum_y = sum_y + y;
					}
				}
				else if(s_p3 > s_p4){
					fscanf(file,"%f",&left); fscanf(file,"%f",&right);
					fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
					fscanf(file,"%s",s);
					x_limit = (s_p3 - c) / slope;
					for (x=left; x < x_limit; x+=0.001){
						y = s_p3;
						sum_xy = sum_xy + (y*x);
						sum_y = sum_y + y;
					}
					x_limit_2 = (s_p4 - c) / slope;
					for (x=x_limit; x < x_limit_2; x+=0.001){
						y = (slope*x) + c;
						sum_xy = sum_xy + (y*x);
						sum_y = sum_y + y;
					}
					for (x=x_limit_2; x < right; x+=0.001){
						y = s_p4;
						sum_xy = sum_xy + (y*x);
						sum_y = sum_y + y;
					}
					fscanf(file,"%f",&left); fscanf(file,"%f",&right);
					fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
				}
				else if(s_p4 >= s_p3){
					fscanf(file,"%f",&left); fscanf(file,"%f",&right);
					fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
					fscanf(file,"%s",s);
					fscanf(file,"%f",&left); fscanf(file,"%f",&right);
					fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
					x_limit = (s_p3 - c) / slope;
					for (x=left; x < x_limit; x+=0.001){
						y = s_p3;
						sum_xy = sum_xy + (y*x);
						sum_y = sum_y + y;
					}
					x_limit_2 = (s_p4 - c) / slope;
					for (x=x_limit; x < x_limit_2; x+=0.001){
						y = (slope*x) + c;
						sum_xy = sum_xy + (y*x);
						sum_y = sum_y + y;
					}
					for (x=x_limit_2; x < right; x+=0.001){
						y = s_p4;
						sum_xy = sum_xy + (y*x);
						sum_y = sum_y + y;
					}
				}
				// Zone 5
				fscanf(file,"%f",&left); fscanf(file,"%f",&right);
				fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
				if(slope == 0.0 && c == 0.0){
				}else{
					if(slope == 0.0){ // big bug when slope == 0 !!!!!!
						for(x=left; x <= right; x+=0.001){
							y = s_p4;
							sum_xy = sum_xy + (y*x);
							sum_y = sum_y + y;
						}
					}
					else{
						x_limit = (s_p4 - c) / slope;
						for(x=left; x < x_limit; x+=0.001){
							y = s_p4;
							sum_xy = sum_xy + (y*x);
							sum_y = sum_y + y;
						}
						for (x=x_limit; x <= right; x+=0.001){
							y = (slope*x) + c;
							sum_xy = sum_xy + (y*x);
							sum_y = sum_y + y;
						}
					}
				}
			}
			else
			{
				fscanf(file,"%f",&left); fscanf(file,"%f",&right);
				fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
				fscanf(file,"%f",&left); fscanf(file,"%f",&right);
				fscanf(file,"%f",&slope); fscanf(file,"%f",&c);
			}		
			i--;
		}
		return sum_xy/sum_y;
	}
	fclose(file);
}
int sort_member(){
	FILE *file;
	int i, check;
	char s[5];
	file = fopen("memberOut_sort.txt","r");
	fscanf(file, "%d",&i); //get i loop
	check = 1;
	do{
		fscanf(file,"%s",s);
		if(!strcmp(out_mem1,s) && out_p1 != 0.0){
			if(check == 1){strcpy(s_mem1,out_mem1); s_p1=out_p1;}
			if(check == 2){strcpy(s_mem2,out_mem1); s_p2=out_p1;}
			if(check == 3){strcpy(s_mem3,out_mem1); s_p3=out_p1;}
			if(check == 4){strcpy(s_mem4,out_mem1); s_p4=out_p1;}
			check++;
		} 
		if(!strcmp(out_mem2,s) && out_p2 != 0.0){
			if(check == 1){strcpy(s_mem1,out_mem2); s_p1=out_p2;}
			if(check == 2){strcpy(s_mem2,out_mem2); s_p2=out_p2;}
			if(check == 3){strcpy(s_mem3,out_mem2); s_p3=out_p2;}
			if(check == 4){strcpy(s_mem4,out_mem2); s_p4=out_p2;}
			check++;
		}
		if(!strcmp(out_mem3,s) && out_p3 != 0.0){
			if(check == 1){strcpy(s_mem1,out_mem3); s_p1=out_p3;}
			if(check == 2){strcpy(s_mem2,out_mem3); s_p2=out_p3;}
			if(check == 3){strcpy(s_mem3,out_mem3); s_p3=out_p3;}
			if(check == 4){strcpy(s_mem4,out_mem3); s_p4=out_p3;}
			check++;
		}
		if(!strcmp(out_mem4,s) && out_p4 != 0.0){
			if(check == 1){strcpy(s_mem1,out_mem4); s_p1=out_p4;}
			if(check == 2){strcpy(s_mem2,out_mem4); s_p2=out_p4;}
			if(check == 3){strcpy(s_mem3,out_mem4); s_p3=out_p4;}
			if(check == 4){strcpy(s_mem4,out_mem4); s_p4=out_p4;}
			check++;
		} 
		i--;
	}while(i>0);
	fclose(file);
	printf("%s %f\n%s %f\n%s %f\n%s %f\n",
			s_mem1,s_p1,s_mem2,s_p2,s_mem3,s_p3,s_mem4,s_p4);
	return check;
}
void merber_output(){ //take out the same membership
	strcpy(out_mem1,t1_mem1);
	out_p1 = t1_p1;
	if(strcmp(out_mem1,t1_mem2) && strcmp(t1_mem2,"NULL")){
		strcpy(out_mem2,t1_mem2);
		out_p2 = t1_p2;
		if(strcmp(out_mem1,t2_mem1) && strcmp(out_mem2,t2_mem1) && strcmp(t2_mem1,"NULL")){
			strcpy(out_mem3,t2_mem1);
			out_p3 = t2_p1;
			if(strcmp(out_mem1,t2_mem2) && strcmp(out_mem2,t2_mem2) && strcmp(out_mem3,t2_mem2) && strcmp(t2_mem2,"NULL")){
				strcpy(out_mem4,t2_mem2);
				out_p4 = t2_p2;
			}
		}
		else if(strcmp(out_mem1,t2_mem2) && strcmp(out_mem2,t2_mem2) && strcmp(t2_mem2,"NULL")){
			strcpy(out_mem3,t2_mem2);
			out_p3 = t2_p2;
			strcpy(out_mem4,"NULL");
			out_p4 = 0.0;
		}
		else{
			strcpy(out_mem3,"NULL");
			out_p3 = 0.0;
			strcpy(out_mem4,"NULL");
			out_p4 = 0.0;
		}
	}
	else if(strcmp(out_mem1,t2_mem1) && strcmp(t2_mem1,"NULL")){
		strcpy(out_mem2,t2_mem1);
		out_p2 = t2_p1;
		if(strcmp(out_mem1,t2_mem2) && strcmp(out_mem2,t2_mem2) && strcmp(t2_mem2,"NULL")){
			strcpy(out_mem3,t2_mem2);
			out_p3 = t2_p2;
			strcpy(out_mem4,"NULL");
			out_p4 = 0.0;
		}
		else{
			strcpy(out_mem3,"NULL");
			out_p3 = 0.0;
			strcpy(out_mem4,"NULL");
			out_p4 = 0.0;
		}
	}
	else if(strcmp(out_mem1,t2_mem2) && strcmp(t2_mem2,"NULL")){
		strcpy(out_mem2,t2_mem2);
		out_p2 = t2_p2;
		strcpy(out_mem3,"NULL");
		out_p3 = 0.0;
		strcpy(out_mem4,"NULL");
		out_p4 = 0.0;
	}
	else{
		printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
		strcpy(out_mem2,"NULL");
		out_p2 = 0.0;
		strcpy(out_mem3,"NULL");
		out_p3 = 0.0;
		strcpy(out_mem4,"NULL");
		out_p4 = 0.0;
	}
	printf("%s %f\n%s %f\n%s %f\n%s %f\n",
		out_mem1,out_p1,out_mem2,out_p2,out_mem3,out_p3,out_mem4,out_p4);	
}
void rule_table_max(){
	// (PN = 4) == (n-1)! => 6 
	if(!strcmp(t1_mem1,t1_mem2)){
		if(t1_p1 > t1_p2) t1_p2 = t1_p1;
		else t1_p1 = t1_p2;
	}
	if(!strcmp(t1_mem1,t2_mem1)){
		if(t1_p1 > t2_p1) t2_p1 = t1_p1;
		else t1_p1 = t2_p1;
	}
	if(!strcmp(t1_mem1,t2_mem2)){
		if(t1_p1 > t2_p2) t2_p2 = t1_p1;
		else t1_p1 = t2_p2;
	}
	if(!strcmp(t1_mem2,t2_mem1)){
		if(t1_p2 > t2_p1) t2_p1 = t1_p2;
		else t1_p2 = t2_p1;
	}
	if(!strcmp(t1_mem2,t2_mem2)){
		if(t1_p2 > t2_p2) t2_p2 = t1_p2;
		else t1_p2 = t2_p2;
	}
	if(!strcmp(t2_mem1,t2_mem2)){
		if(t2_p1 > t2_p2) t2_p2 = t2_p1;
		else t2_p1 = t2_p2;
	}
}
void rule_table_min(){
	if(in1_p1 < in2_p1) t1_p1 = in1_p1;
	else t1_p1 = in2_p1;
	if(in1_p1 < in2_p2) t1_p2 = in1_p1;
	else t1_p2 = in2_p2;
	if(in1_p2 < in2_p1) t2_p1 = in1_p2;
	else t2_p1 = in2_p1;
	if(in1_p2 < in2_p2) t2_p2 = in1_p2;
	else t2_p2 = in2_p2;
}
void rule_table(){
	FILE *file;
	int i;
	char s1[5],s2[5],s3[5];
	// in1_member1 & in2_member1
	file = fopen("rule_table.txt", "r");
	fscanf(file,"%d",&i);
	while(i>0){
		fscanf(file,"%s",s1);
		fscanf(file,"%s",s2);
		if(!strcmp(in1_member1,s1) && !strcmp(in2_member1,s2)){
			fscanf(file, "%s", t1_mem1);
			break;
		}
		else{
			fscanf(file,"%s",s3);
		}
		i--;
	}
	fclose (file);
	// in1_member1 & in2_member2
	file = fopen("rule_table.txt", "r");
	fscanf(file,"%d",&i);
	while(i>0){
		fscanf(file,"%s",s1);
		fscanf(file,"%s",s2);
		if(!strcmp(in1_member1,s1) && !strcmp(in2_member2,s2)){
			fscanf(file, "%s", t1_mem2);
			break;
		}
		else{
			fscanf(file,"%s",s3);
		}
		i--;
	}
	fclose (file);
	// in1_member2 & in2_member1
	file = fopen("rule_table.txt", "r");
	fscanf(file,"%d",&i);
	while(i>0){
		fscanf(file,"%s",s1);
		fscanf(file,"%s",s2);
		if(!strcmp(in1_member2,s1) && !strcmp(in2_member1,s2)){
			fscanf(file, "%s", t2_mem1);
			break;
		}
		else{
			fscanf(file,"%s",s3);
		}
		i--;
	}
	fclose (file);
	// in1_member2 & in2_member2
	file = fopen("rule_table.txt", "r");
	fscanf(file,"%d",&i);
	while(i>0){
		fscanf(file,"%s",s1);
		fscanf(file,"%s",s2);
		if(!strcmp(in1_member2,s1) && !strcmp(in2_member2,s2)){
			fscanf(file, "%s", t2_mem2);
			break;
		}
		else{
			fscanf(file,"%s",s3);
		}
		i--;
	}
	fclose (file);
	// check min data for new membership and find max data of membership
	rule_table_min();
	printf("%s %f\n%s %f\n%s %f\n%s %f\n",
		t1_mem1,t1_p1,t1_mem2,t1_p2,t2_mem1,t2_p1,t2_mem2,t2_p2);
	rule_table_max();
	printf("Membership MAX from Rule Table\n");
	printf("%s %f\n%s %f\n%s %f\n%s %f\n",
		t1_mem1,t1_p1,t1_mem2,t1_p2,t2_mem1,t2_p1,t2_mem2,t2_p2);
}
void memberIn2_out(){
	FILE *file;
	file = fopen("memberIn2_out.txt", "r");
	int i;
	float slope,c;
	char s1[5],s2[5];
	fscanf(file, "%d", &i);
	while(i>0){
		fscanf(file, " %s", s1);
		fscanf(file, " %s", s2);
		if(!strcmp(s1,in2_member1) && !strcmp(s2,in2_member2)){
			fscanf(file," %f",&slope);
			fscanf(file," %f",&c);
			in2_p1 = (slope*in2_input)+c;
			in2_p2 = fabsf(1.0 - in2_p1);
			break;	
		}else{
			fscanf(file," %f",&slope);
			fscanf(file," %f",&c);
		}
		i--;	
	}
	printf("%f %f\n", in2_p1,in2_p2);
	fclose (file);
}
void memberIn1_out(){
	FILE *file;
	file = fopen("memberIn1_out.txt", "r");
	int i;
	float slope,c;
	char s1[5],s2[5];
	fscanf(file, "%d", &i);
	while(i>0){
		fscanf(file, " %s", s1);
		fscanf(file, " %s", s2);
		if(!strcmp(s1,in1_member1) && !strcmp(s2,in1_member2)){
			fscanf(file," %f",&slope);
			fscanf(file," %f",&c);
			in1_p1 = (slope*in1_input)+c;
			in1_p2 = fabsf(1.0 - in1_p1);
			break;	
		}else{
			fscanf(file," %f",&slope);
			fscanf(file," %f",&c);
		}
		i--;	
	}
	printf("%f %f\n", in1_p1,in1_p2);
	fclose (file);
}
void memberIn2(){
	FILE *file;
	file = fopen("memberIn2.txt", "r");
	int i;
	float check;
	char s[5];
	fscanf(file, "%d", &i);
	while(i>0){
		fscanf(file,"%f",&check);
		if(in2_input <= check){
			fscanf(file,"%f",&check);
			fscanf(file,"%s",in2_member1);
			fscanf(file,"%s",in2_member2);
			break;
		}
		else if(in2_input >= check){
			fscanf(file,"%f",&check);
			if(in2_input <= check){
				fscanf(file,"%s",in2_member1);
				fscanf(file,"%s",in2_member2);
				break;
			}
			else{
				fscanf(file,"%s",in2_member1);
				fscanf(file,"%s",in2_member2);
			}	
		}
		i--;
	}
	printf("%s %s\n",in2_member1,in2_member2);
	fclose (file);
}
void memberIn1(){
	FILE *file;
	file = fopen("memberIn1.txt", "r");
	int i;
	float check;
	char s[5];
	fscanf(file, "%d", &i);
	while(i>0){
		fscanf(file,"%f",&check);
		if(in1_input <= check){
			fscanf(file,"%f",&check);
			fscanf(file,"%s",in1_member1);
			fscanf(file,"%s",in1_member2);
			break;
		}
		else if(in1_input >= check){
			fscanf(file,"%f",&check);
			if(in1_input <= check){
				fscanf(file,"%s",in1_member1);
				fscanf(file,"%s",in1_member2);
				break;
			}
			else{
				fscanf(file,"%s",in1_member1);
				fscanf(file,"%s",in1_member2);
			}	
		}
		i--;
	}
	printf("%s %s\n",in1_member1,in1_member2);
	fclose (file);
}
void input(){
	// open file
	FILE *file;
	file = fopen("input.txt", "r");
	// read data
	fscanf(file, "%s", in1_name);
	fscanf(file, "%f", &in1_input);
	printf("Hello, This is Fuzzy program. \nThe %s input value: %.2f\n",in1_name,in1_input);
	fscanf(file, "%s", in2_name);
	fscanf(file, "%f", &in2_input);
	printf("The %s input value: %.2f\n",in2_name,in2_input);
	fscanf(file,"%d",&in1_row);
	fscanf(file,"%d",&in2_colum);
	fscanf(file, "%d",&out_member);
	// printf("The number of %s     membership is %d\n",in1_name,in1_row);
	// printf("The number of %s    membership is %d\n",in2_name,in2_colum);
	// printf("The number of output membership is %d\n",out_member);
	fclose (file);
}
