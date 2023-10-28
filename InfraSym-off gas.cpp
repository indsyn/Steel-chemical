#include <cstdio>
#include <cstdlib>
//#include <iostream>
#include <cmath>
//using namespace std;

FILE *fp1, *fp2;//输出输入文件变量
int finish,n,m,x,y,count,tot,pan2x,pan2y;
int row[500],col[500],markx[500],marky[500],flagx[500],flagy[500],tui[500][500];
double c[500][500],a[500],b[500],ans[500][500],w[500],v[500],eva[500][500];
double opt,tota,totb,cmin,pan,pan2;

void inputdata()
{
    int i,j;
    char ss[255];

    //fscanf(fp1,"%s",&ss); 
	fscanf(fp1,"%d",&m);
	fscanf(fp1,"%d",&n);
    for (i=1;i<=m;i++)
	{
		fscanf(fp1,"%lf",&a[i]);
		tota=tota+a[i];
	}
	for (j=1;j<=n;j++)
	{
		fscanf(fp1,"%lf",&b[j]);
		totb=totb+b[j];
	}
    for (i=1;i<=m;i++)
		for (j=1;j<=n;j++)
		{
			fscanf(fp1,"%lf",&c[i][j]);
			c[i][j]=c[i][j]/1000;
		}
}

void initial()
{
	int i,j;
	while ((tota>0.0001)&&(totb>0.0001))	
	{
		cmin=-1;
		x=0;
		y=0;
		for (i=1;i<=m;i++)
			if (markx[i]==0)
				for (j=1;j<=n;j++) 
					if (marky[j]==0)
						if ((cmin==-1)||(cmin>c[i][j]))
						{
						 	cmin=c[i][j];
							x=i;
							y=j;
							//printf("%.1lf\n",cmin);
						}
		if (cmin!=-1)
			if (a[x]>b[y])
			{
				if (b[y]==0)
				{
					tui[x][y]=1;
					//printf("tuix: %d  tuiy: %d ",tuix,tuiy);
				}
				//printf("byy: %.0lf ",b[y]);
				ans[x][y]=b[y];
				tota=tota-b[y];
				totb=totb-b[y];
				a[x]=a[x]-b[y];
				b[y]=0;
				marky[y]=1;
				//printf("xx: %d   yy: %d  tota: %.0lf  totb: %.0lf\n",x,y,tota,totb);
			}
			else
			{
				if (a[x]==0)
				{
					tui[x][y]=1;
					//printf("tuix: %d  tuiy: %d ",tuix,tuiy);
				}
				//printf("axx: %.0lf ",a[x]);
				ans[x][y]=a[x];
				tota=tota-a[x];
				totb=totb-a[x];
				b[y]=b[y]-a[x];
				a[x]=0;
				markx[x]=1;
				//printf("xx: %d   yy: %d  tota: %.0lf  totb: %.0lf\n",x,y,tota,totb);
			}
	}
}

void evanum(int s,int t,int r)
{
	int i,j;
	//printf("(%d, %d, %d)\n",s,t,r);
	if (r==0)
		for (j=1;j<=n;j++) 
			if (((ans[s][j]>0)||(tui[s][j]==1)) &&(flagy[j]==0))
			{
				v[j]=c[s][j]-w[s];
				flagy[j]=1;
				count++;
				if(count<m+n) evanum(s,j,1);
			}
	
	if (r==1)
		for (i=1;i<=m;i++)
			if (((ans[i][t]>0)||(tui[i][t]==1)) &&(flagx[i]==0))
			{
				w[i]=c[i][t]-v[t];
				flagx[i]=1;
				count++;
				if (count<m+n) evanum(i,t,0);
			}
}

void evacal()
{
	int i,j;
	pan=0;
	pan2=0;
	for (i=1;i<=m;i++)
		for (j=1;j<=n;j++)
		{
			eva[i][j]=w[i]+v[j]-c[i][j];
			//printf("%.0lf   ",eva[i][j]);
			if (pan<eva[i][j])
			{
				pan2=pan;
				pan2x=row[1];
				pan2y=col[1];
				pan=eva[i][j];
				row[1]=i;
				col[1]=j;
			}
			//if (j==n) printf("\n");
		}
}

void path(int x, int y, int z)
{
	int i,j,yy,xx;

	if (z==0)
	{
		yy=y;
		if (finish==0)
			while (yy<n)
			{
				yy++;
				if ((finish==0)&& ((ans[x][yy]>0)||(tui[x][yy]==1)))
				{
					tot++;
					row[tot]=x;
					col[tot]=yy;
					//printf("(%d  %d  %d  tot: %d) \n",x,yy,1,tot);
					if ((tot>=4)&&(x!=row[1])&&(yy==col[1]))
					{
						finish=1;
						printf("(finished %d) ",finish);
					}
					else path(x,yy,1);
					
					if (finish==0)
					{
						row[tot]=0;
						col[tot]=0;
						tot--;
					}
				} 
			}
		
		yy=y;
		if (finish==0)
			while (yy>1)
			{
				yy--;
				if ((finish==0)&& ((ans[x][yy]>0)||(tui[x][yy]==1)))
				{
					tot++;
					row[tot]=x;
					col[tot]=yy;
					//printf("(%d  %d  %d  tot: %d) \n",x,yy,1,tot);
					if ((tot>=4)&&(x!=row[1])&&(yy==col[1]))
					{
						finish=1;
						printf("(finished %d) ",finish);
					}
					else path(x,yy,1);
					
					if (finish==0)
					{
						row[tot]=0;
						col[tot]=0;
						tot--;
					}
				} 
			}
	}

	
	if (z==1)
	{
		xx=x;
		if (finish==0)
			while (xx<m)
			{
				xx++;
				if ((finish==0)&& ((ans[xx][y]>0)||(tui[xx][y]==1)))
				{
					tot++;
					row[tot]=xx;
					col[tot]=y;
					//printf("(%d  %d  %d  tot: %d) \n",xx,y,0,tot);
					if ((tot>=4)&&(xx==row[1])&&(y!=col[1]))
					{
						finish=1;
						printf("(finished %d) ",finish);
					}
					else path(xx,y,0);
					
					if (finish==0)
					{
						row[tot]=0;
						col[tot]=0;
						tot--;
					}	
				} 
			}
		
		xx=x;
		if (finish==0)
			while (xx>1)
			{
				xx--;
				if ((finish==0)&& ((ans[xx][y]>0)||(tui[xx][y]==1)))
				{
					tot++;
					row[tot]=xx;
					col[tot]=y;
					//printf("(%d  %d  %d  tot: %d) \n",xx,y,0,tot);
					if ((tot>=4)&&(xx==row[1])&&(y!=col[1]))
					{
						finish=1;
						printf("(finished %d) ",finish);
					}
					else path(xx,y,0);
					
					if (finish==0)
					{
						row[tot]=0;
						col[tot]=0;
						tot--;
					}
				} 
			}
	}
	
	//if (finish==0) 
		//if (tot>1) 
			//tot--;

}


int main()
{
    int i,j,tt,record;
    double change;
    
    tota=0;
    totb=0;
    //m=3;
	//n=4; 
	fp1 = fopen("Data input-BFG-100km.xls","r");
    fp2 = fopen("Data output-BFG-100km.xls","a+");
    inputdata();
    printf("m: %d  n: %d\n",m,n);
	for (i=1;i<=m;i++)
		for (j=1;j<=n;j++)
		{
			ans[i][j]=0;
			tui[x][y]=0;
		}
	for (i=1;i<=m;i++) markx[i]=0;
	for (j=1;j<=n;j++) marky[j]=0;
	initial();
	printf("initial solution:\n");
	//for (i=1;i<=m;i++)
	//{
		//for (j=1;j<=n;j++) 
			//printf("%.0lf  ",ans[i][j]);
		//printf("\n");
	//}
	
	
	pan=1;
	finish=0;
	while (pan>0.0001)
	{
		
		for (i=1;i<=m;i++) flagx[i]=0;
		for (j=1;j<=n;j++) flagy[j]=0;
		w[1]=0;
		flagx[1]=1;
		count=1;
		evanum(1,1,0);
		//printf("panbieshu: \n");
		//for (i=1;i<=m;i++) printf("%.0lf  ",w[i]);
		//printf("\n");
		//for (j=1;j<=n;j++) printf("%.0lf  ",v[j]);
		//printf("\n");
		//printf("%d\n",count);
		
		//printf("\n");
		evacal();
		printf("  pan: %.4lf    \n",pan);
		if (finish==0)
		{
			pan=pan2;
			row[1]=pan2x;
			col[1]=pan2y;	
		}
		
		if (pan>0.0001)
		{
			finish=0;
			tot=1;
			//printf("(%d  %d  %d  tot: %d) \n",row[1],col[1],0,tot);
			path(row[1],col[1],0);
		
			if (finish==1)
			{
	
				tt=0;
				//printf("tot: %d  \n",tot);
				change=0;
				while (tt<tot)
				{
					tt++;
					if (tt%2==0)
					{
						if ((change==0)||(change>ans[row[tt]][col[tt]]))
							change=ans[row[tt]][col[tt]];
					}
					//printf("(%d, %d)",row[tt],col[tt]);
				} 
				//printf("\n");
				tt=0;
				record=0;
				if (change==0) tui[row[1]][col[1]]=1;
							
				while (tt<tot)
				{
					tt++;
					if (tt%2==1)
					{
						ans[row[tt]][col[tt]]=ans[row[tt]][col[tt]]+change;
						if (ans[row[tt]][col[tt]]>0)
							tui[row[tt]][col[tt]]=0;
						else
							tui[row[tt]][col[tt]]=1;
					}
					else 
					{
						ans[row[tt]][col[tt]]=ans[row[tt]][col[tt]]-change;
						if (ans[row[tt]][col[tt]]==0) 
						{
							record++;
							if (record==1) tui[row[tt]][col[tt]]=0;
							if (record>1) tui[row[tt]][col[tt]]=1;
						}
					}
				}
			}

			//printf("solution: \n");
			//for (i=1;i<=m;i++)
			//{
				//for (j=1;j<=n;j++) 
					//printf("%.0lf  ",ans[i][j]);
				//printf("\n");
			//}
			//printf("\n");
			
		}
	}
	
	fprintf(fp2,"opt ans:\n");
	opt=0;
	for (i=1;i<=m;i++)
	{
		for (j=1;j<=n;j++) 
		{
			fprintf(fp2,"%.10lf\t",ans[i][j]);
			opt=opt+ans[i][j]*c[i][j];
		}
		fprintf(fp2,"\n");
	}
	fprintf(fp2,"opt f: %.10lf\n",opt);
	
    fclose(fp1);
    fclose(fp2);
    //system("PAUSE");
    return 0;
}

