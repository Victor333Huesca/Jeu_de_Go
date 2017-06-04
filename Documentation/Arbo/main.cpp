#include <iostream>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#define N 2

struct noeud
{
	int p;
	int n;
	noeud * f[2];
};

void afficheABR(noeud * r)
{
	if(r != NULL)
	{
		for(int i = 0; i < r->n; i++)
		{
			std::cout<<r->p<<std::endl;
			afficheABR(r->f[i]);
		}	
	}
}

void elaguerABR(noeud * r, int cmp)
{
	int i;
	if(r != NULL)
	{
		for(i = 0; i < r->n; i++)
		{
			if(r->f[i]->p != cmp)
			{
				r->f[i] = NULL;
			}else{ break;
			}
			
		}
		for(int j = i; j < r->n; j++)
		{
			r->f[j] = NULL;
		}
		if(cmp == 1){
			cmp--;
		}
		elaguerABR(r->f[i], cmp);
	}
}


int main(int argc, char** argv) {
	
	noeud r, f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, f15, f16, f18, f19, f20;
	r.p = 0; f1.n = 2;
	r.n = 2; f1.p = 0;
	f2.p = 0; f9.n = 2;
	f2.n = 2; f9.p = 0;
	f3.p = 0; f10.n = 2;
	f3.n = 2; f10.p = 0;
	f4.p = 0; f11.n = 2;
	f4.n = 2; f11.p = 0;
	f5.p = 0; f12.n = 2;
	f5.n = 2; f12.p = 0;
	f6.p = 0; f13.n = 2;
	f6.n = 2; f13.p = 0;
	f7.p = 0; f14.n = 2;
	f7.n = 2; f14.p = 0;
	f8.p = 0; f15.n = 2;
	f8.n = 2; f15.p = 0;
	r.f[0] = &f1; r.f[1] = &f2; 
	f1.f[0] = &f3; f2.f[0] = &f5;
	f1.f[1] = &f4; f2.f[1] = &f6;
	f3.f[0] = &f7; f4.f[0] = &f9; f5.f[0] = &f11; f6.f[0] = &f13;
	f3.f[1] = &f8; f4.f[1] = &f10; f5.f[1] = &f12; f6.f[1] = &f14;
	f7.f[0] = NULL; f8.f[0] = NULL; 
	f7.f[1] = NULL; f8.f[1] = NULL;
	f9.f[0] = NULL; f10.f[0] = NULL;
	f9.f[1] = NULL; f10.f[1] = NULL;
	f11.f[0] = NULL; f12.f[0] = NULL;
	f11.f[1] = NULL; f12.f[1] = NULL;
	f13.f[0] = NULL; f14.f[0] = NULL;
	f13.f[1] = NULL; f14.f[1] = NULL;
	
	
	afficheABR(&r);
	
	return 0;
}
