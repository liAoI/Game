#include <stdio.h>
#include <stdlib.h>


# define F(x_1,x_2) (x_1-x_2+2*x_1*x_1+2*x_1*x_2+x_2*x_2)
# define df_x1(x_1,x_2) (1+4*x_1+2*x_2)
# define df_x2(x_1,x_2) (-1+2*x_1+2*x_2)

double X[2];

double lambda=0.01;

double Gradient_Descent(double lambda){
	/*
		new_x[0] = X[0] - lambda * df/x1
		new_x[1] = X[1] - lambda * df/x2
		
		更新完成之后，带入f(x1,x2)中，求出函数值 
	*/
	double df_1 =  df_x1(X[0],X[1]);
	double df_2 =  df_x2(X[0],X[1]);
	
	double new_x[2];
	new_x[0] = X[0] - lambda * df_1;
	new_x[1] = X[1] - lambda * df_2;
	
	X[0] = new_x[0];
	X[1] = new_x[1];
	printf("x1 = %lf\t x2 = %lf\t",X[0],X[1]);
	return F(new_x[0],new_x[1]);
}

int main(int argc, char** argv) {
	
	//初始化变量
	int count=0;
	X[0] = 0.0,X[1] = 0.0;
	double minf_pre = F(X[0],X[1]);
//	printf("%lf\n",minf_pre);
	double minf = Gradient_Descent(lambda);

			
	while(minf_pre - minf >=0.000001 || minf - minf_pre >=0.000001)
	{
		minf_pre = minf;
		minf = Gradient_Descent(lambda);
		printf("count = %d\t",++count);
		printf("minf = %.8lf\n",minf);
	}
	
	printf("-----------最后所得结果-----------\n");
	printf("x1 = %lf\t x2 = %lf\n",X[0],X[1]);
	printf("min F(x) = %lf\n",minf);
	return 0;
}
