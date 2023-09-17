clc
clear
tic

% 载入数据
%load('province_d01.mat')
load('grid_GHG_H2.mat')

% 载入colormap
load color.mat;
clear coltemp
%temp=color{135}(31:8:256,:);
coltemp=color{135}(20:14:90,:);
%coltemp=flipud(coltemp);
%clear temp

% 画空间分布图
figure
load land_d01 % 画图用不带m后缀的格点数据
axes('position',[0 0 0.95 0.95]);
m_proj('Lambert','lon',[80,129],'lat',[18,52],'par',[25,45],'ori',[110,34],'rec','on');

value=zeros(229,159);
for i=1:1:229
    for j=1:1:159
        value(i,j)=-GHG(i,j);
        if value(i,j)==0
            value(i,j)=nan;
        end
    end
end

[H1]=m_pcolor(nlon,nlat,value);
set(H1,'linestyle','none');
m_grid('linestyle','none','tickdir','in','xtick',[],'ytick',[],'fontsize',10);
colormap(coltemp);
pc=colorbar('fontsize',12);
caxis([-6 0]);
set(pc,'ytick',[-6:1:0]);
m_plotbndry('shengjie','color','k');
xlabel(pc,'MtCO_2eq/yr');
%title('','fontsize',8);
print(gcf,'-dpng','-r1200',['./GHG_H2.png']);

        