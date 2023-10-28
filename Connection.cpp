#include <cstdio>
#include <cstdlib>
//#include <iostream>
#include <cmath>
//using namespace std;

FILE *fp1, *fp2, *fp3, *fp4, *fp5, *fp6;
double COG[500][500],BFG[500][500],BOFG[500][500],dis_H2[500][500],dis_CO[500][500];
int ori[750000],des[750000],mark[750000];

int main()
{
	int i,j,tot1=0,tot2=0,tot3=0,x,y;
	char ss[255];
	
	fp1 = fopen("Feasible H2.xls","r");
	fp2 = fopen("Feasible CO-BFG-500km.xls","r");
	fp3 = fopen("Feasible CO-BOFG.xls","r");
	fp4 = fopen("Distance-H2.xls","r");
	fp5 = fopen("Distance-CO.xls","r");
	fp6 = fopen("Connection.xls","a+");
	
    //fscanf(fp1,"%s",&ss);
	for (i=1;i<=171;i++)
    	for (j=1;j<=187;j++)
    	{
			fscanf(fp1,"%lf",&COG[i][j]);
			if (COG[i][j]>0)
			{
				tot1++;
				ori[tot1]=i;
				des[tot1]=j;
				mark[tot1]=1;
			}
		}
	
	for (i=1;i<=272;i++)
    	for (j=1;j<=187;j++)
    	{
    		fscanf(fp2,"%lf",&BFG[i][j]);
    		if (BFG[i][j]>0)
			{
				tot2++;
				ori[tot1+tot2]=i;
				des[tot1+tot2]=j;
				mark[tot1+tot2]=2;
			}
		}
	
	for (i=1;i<=272;i++)
    	for (j=1;j<=187;j++)
    	{
    		fscanf(fp3,"%lf",&BOFG[i][j]);
    		if (BOFG[i][j]>0)
			{
				tot3++;
				ori[tot1+tot2+tot3]=i;
				des[tot1+tot2+tot3]=j;
				mark[tot1+tot2+tot3]=3;
			}
		}
		
	
	for (i=1;i<=171;i++)
    	for (j=1;j<=187;j++)
    		fscanf(fp4,"%lf",&dis_H2[i][j]);
    		
	for (i=1;i<=272;i++)
    	for (j=1;j<=187;j++)
    		fscanf(fp5,"%lf",&dis_CO[i][j]);
    
    printf("%d %d %d\n",tot1,tot2,tot3);
    
    
    fprintf(fp6,"No\t");
    fprintf(fp6,"Origin\t");
    fprintf(fp6,"Destination\t");
    fprintf(fp6,"Length(km)\t");
    fprintf(fp6,"Gas\t");
    fprintf(fp6,"Flux(Mm3)\t");
    fprintf(fp6,"\n");
    
    for (i=1;i<=tot1+tot2+tot3;i++)
    {
    	fprintf(fp6,"%d\t",i);
    	fprintf(fp6,"%d\t",ori[i]);
    	fprintf(fp6,"%d\t",des[i]);
    	x=ori[i];
    	y=des[i];
    	if (mark[i]==1)
			fprintf(fp6,"%lf\t",dis_H2[x][y]/1000);
		else
			fprintf(fp6,"%lf\t",dis_CO[x][y]/1000);
		
		if (mark[i]==1)
		{
    		fprintf(fp6,"H2\t");
			fprintf(fp6,"%lf\t",COG[x][y]);
    		fprintf(fp6,"\n");
    	}
    	
    	if (mark[i]==2)
    	{
    		fprintf(fp6,"CO-BFG\t");
			fprintf(fp6,"%lf\t",BFG[x][y]);
    		fprintf(fp6,"\n");
    	}
    	
    	if (mark[i]==3)
    	{
    		fprintf(fp6,"CO-BOFG\t");
			fprintf(fp6,"%lf\t",BOFG[x][y]);
    		fprintf(fp6,"\n");
    	}
	}

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
    fclose(fp5);
    fclose(fp6);
	//system("PAUSE");
    return 0;
}

