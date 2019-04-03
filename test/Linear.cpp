#include<iostream>
#include<cmath>
#include<conio.h>
#include<iomanip>
float y_actual[5]={1,2,3,4,5},x[5]={1,2,3,4,5},y_pred[5];
float alpha=.1;
int size=5;
int count=0;
float m_final,c_final;
using namespace std;
class Linear{
	public:
		
		//data members
	float m,c;
	float error;
	
	//Initialize 
	Linear(){
		error=0.0;    // afterwards use a cin, cout statement for size
	}
	
	//member functions
	
	// Input will wither be hardcoded or through armadillo so no need for an input function
	
	void fit(float m= 0.0,float c=0.0){
		for(int i=0;i<size;i++)
		{
			y_pred[i]=(m*x[i])+c;
		}
		cost_function(m,c);
	}
		
		
	void cost_function(float m,float c){
		error=0;
		for( int i=0;i< size;i++)
		{
			error+=pow((y_pred[i]-y_actual[i]),2);   // this is working
		}
		error=error/(2*size);	  
		cout<<"error"<<error<<endl;
		if(error==0){
			final_values(m,c);
			cout<<" we are here";
		}
		else
		{
		if(count<100){
			count++;	
			minimizing_function();
	}
	}
}
	
	// to minimize the cost function error
	void minimizing_function() {
		float a,b;
		for(int i=0;i<size;i++){
		
		a+=(y_pred[i]-y_actual[i]);
		b+=(y_pred[i]-y_actual[i])*x[i];
		
		
	}
	
		b/=size;
		a/=size;
		
		m-=alpha*b;
		c-=alpha*a;
	
	/*	
		m=(m%1>0.5?(int)(m+0.5):(int)m);            //round off
		c=(c%1>0.5?(int)(c+0.5):(int)c);
		
	*/			
		cout<<count<<endl;
		cout<<m<<"\n";
		cout<<c<<endl;
		
		fit(m,c);
	}
	
	void final_values(float a, float b){
	
		m=a;
		c=b;
	}
	
	
	void predict(float a, float b)
	{
		float x,y;
		cout<<" Enter the x ( predictor ) for which response to be predicted\n";
		cin>>x;
		cout<<" The predicted value is \n";
		y=(a*x)+b;
		cout<<y;
	}
};


int main(){
	char a;
	Linear l;
	l.fit();
	cout<<" The best fit line for data is"<<endl;
	cout<<"y="<<l.m<<"x+"<<l.c;
	cout<<" Do you want to predict anything";
	cin>>a;
	if (a=='Y'||a=='y'){
		l.predict(l.m,l.c);
	}
	getch();
	return 0;
}
