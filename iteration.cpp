#include "iteration.h"

double euclNorm(vector<double>* u)
{
   double norm = 0.;
   for (vector<double>::iterator it = u->begin() ; it != u->end(); ++it)
      norm += (*it)*(*it);

   return sqrt(norm);
}


void vectorScalar(vector<double>* u,double scalar)
{
   for (unsigned int i=0; i<u->size(); ++i)
      (*u)[i] = u->at(i)*scalar;
}

double vectorVector(vector<double>* u,vector<double>* v)
{
   double ret=0.; 

   if (u->size()!=v->size())
      return ret;

   for (unsigned int i=0; i<u->size(); ++i)
      ret=u->at(i)*v->at(i);

   return ret;
}

double vectorSub(vector<double>* u,vector<double>* v)
{
   double ret=0.; 

   if (u->size()!=v->size())
      exit(1);

   for (unsigned int i=0; i<u->size(); ++i)
      ret=u->at(i)*v->at(i);

   return ret;
}

void matrixVector(vector<map<int,double> >* mat,vector<double>* vec,vector<double>* ret)
{
   if (mat->size()!=vec->size())
      exit(1);

   for(unsigned int j = 0;j<mat->size();++j){
      double value=0.;

      for(unsigned int i = 0; i < mat->size(); i++){
	 if(mat->at(j).count(i)==1){
	    value += mat->at(j).at(i)*vec->at(i);
	 }
      }
      (*ret)[j]=value;
   }
}

void solveJacobi(vector<map<int,double> >* A,vector<double>* u,vector<double>* f,int iter)
{
   vector<double> u_alt(*u);
   for (int i=0;i< iter;i++)
   {
      (*u)=(*f);

      for (unsigned int j=0;j< u->size();j++)
      {
	 for (unsigned int k=0;k< u->size();k++)
	 {
	    if (k!=j)
	    {
	       if(A->at(j).count(k)==1)
	       {
		  (*u)[j]=(*u)[j] - A->at(j).at(k)*u_alt[j];
	       }
	    }
	 }
	 (*u)[j]/=A->at(j).at(j);
      }
      u_alt=(*u);
   }
   (*u)=u_alt;

}



