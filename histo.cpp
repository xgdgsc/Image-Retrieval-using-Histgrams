#include"histo.h"
using namespace std;

void Histo::input()
{
  ifstream infile;
  infile.open("AllImages.txt",ios::in);
  string nameTemp;
  uint w,h;
  imgHisto tempimg;
  Mat tempM;
  string prefix("./DataSet/");
  while(infile>>nameTemp>>w>>h)
    {
      int found=nameTemp.find_first_of("/");
      string nameCore=nameTemp;
      nameCore.erase(nameCore.begin()+found,nameCore.end());
     // cout<<nameCore<<endl;
      nameTemp=prefix+nameTemp;
      tempimg.imgName=nameTemp;
      tempimg.w=w;
      tempimg.h=h;
      tempimg.nameCore=nameCore;
      tempimg.img=imread(nameTemp,1);
      allImage.push_back(tempimg);
    }
  infile.close();
  infile.open("QueryImages.txt",ios::in);
  while(infile>>nameTemp>>w>>h)
    {
      int found=nameTemp.find_first_of("/");
      string nameCore=nameTemp;
      nameCore.erase(nameCore.begin()+found,nameCore.end());
      nameTemp=prefix+nameTemp;
      tempimg.imgName=nameTemp;
      tempimg.w=w;
      tempimg.h=h;
      tempimg.nameCore=nameCore;
      tempimg.img=imread(nameTemp,1);
      queryImage.push_back(tempimg);
    }

  int part16[3]={2,4,2};
  int part128[3]={4,8,4};
  generateHist(part16);
  generateHist(part128);
}


void Histo::generateHist(int part[])
{
  clearH();
  int step[3];
  for(int i=0;i<3;i++)
    {
      step[i]=256/part[i];
    }
  double histo[part[0]][part[1]][part[2]];
  double imgSize;
  int index[3];
  for(uint i=0;i<allImage.size();i++)
    {
      for(int a=0;a<part[0];a++)
        for(int b=0;b<part[1];b++)
          for(int c=0;c<part[2];c++)
            {
              histo[a][b][c]=0;
            }
      vector<Mat> bgr_planes;
      split(allImage[i].img,bgr_planes);
      for(int x=0;x<allImage[i].img.rows;x++)
        for(int y=0;y<allImage[i].img.cols;y++)
          {
            index[0]= bgr_planes[0].at<uchar>(x,y)/step[0];
            index[1]= bgr_planes[1].at<uchar>(x,y)/step[1];
            index[2]= bgr_planes[2].at<uchar>(x,y)/step[2];
            histo[index[0]][index[1]][index[2]]++;
            //            cout<<bgr_planes[1].at<uchar>(x,y)<<' '<<index[1]<<endl;
          }
      imgSize=allImage[i].img.rows*allImage[i].img.cols;
      for(int a=0;a<part[0];a++)
        for(int b=0;b<part[1];b++)
          for(int c=0;c<part[2];c++)
            {
              histo[a][b][c]= histo[a][b][c]/imgSize;
              allImage[i].histo.push_back(histo[a][b][c]);
            }
      //      int sum=0;
      //      for(int j=0;j<16;j++)
      //        {
      //          sum+=allImage[i].histo[j];
      //        }
      //      cout<<sum<<endl;
    }



  for(uint i=0;i<queryImage.size();i++)
    {
      for(int a=0;a<part[0];a++)
        for(int b=0;b<part[1];b++)
          for(int c=0;c<part[2];c++)
            {
              histo[a][b][c]=0;
            }
      vector<Mat> bgr_planes;
      split(queryImage[i].img,bgr_planes);
      for(int x=0;x<queryImage[i].img.rows;x++)
        for(int y=0;y<queryImage[i].img.cols;y++)
          {
            index[0]= bgr_planes[0].at<uchar>(x,y)/step[0];
            index[1]= bgr_planes[1].at<uchar>(x,y)/step[1];
            index[2]= bgr_planes[2].at<uchar>(x,y)/step[2];
            histo[index[0]][index[1]][index[2]]++;
            //            cout<<bgr_planes[1].at<uchar>(x,y)<<' '<<index[1]<<endl;
          }
      imgSize=queryImage[i].img.rows*queryImage[i].img.cols;
      for(int a=0;a<part[0];a++)
        for(int b=0;b<part[1];b++)
          for(int c=0;c<part[2];c++)
            {
              histo[a][b][c]= histo[a][b][c]/imgSize;
              queryImage[i].histo.push_back(histo[a][b][c]);
            }
      //      int sum=0;
      //      for(int j=0;j<16;j++)
      //        {
      //          sum+=queryImage[i].histo[j];
      //        }
      //      cout<<sum<<endl;
    }
  for(uint i=0;i<queryImage.size();i++)
    {
      clear();
      generateReport(queryImage[i],part,"L2");
    }
  overall(part,"L2");
  for(uint i=0;i<queryImage.size();i++)
    {
      clear();
      generateReport(queryImage[i],part,"HI");
    }
    overall(part,"HI");
    for(uint i=0;i<queryImage.size();i++)
      {
        clear();
        generateReport(queryImage[i],part,"Bh");
      }
    overall(part,"Bh");
    for(uint i=0;i<queryImage.size();i++)
      {
        clear();
        generateReport(queryImage[i],part,"Co");
      }
    overall(part,"Co");
}

double Histo::calcL2(imgHisto query,imgHisto all)
{
  double sum=0;
  for(uint i=0;i<query.histo.size();i++)
    {
      sum+=pow(query.histo[i]-all.histo[i],2);
    }
  return sqrt(sum);
}


double Histo::calcHI(imgHisto query, imgHisto all)
{
  double sum=0;
  for(uint i=0;i<query.histo.size();i++)
    {
      sum+=min(query.histo[i],all.histo[i]);
    }
  return sum;
}

double Histo::calcBh(imgHisto query, imgHisto all)
{
  double sum=0;
  for(uint i=0;i<query.histo.size();i++)
    {
      sum+=sqrt(query.histo[i]*all.histo[i]);
    }
  //cout<<sum<<endl;
  if(sum>1)sum=1;
  return sqrt(1-sum);
}

double Histo::calcCo(imgHisto query, imgHisto all)
{
  double sum=0;
  for(uint i=0;i<query.histo.size();i++)
    {
      sum+=query.histo[i];
    }
  double aveq=sum/query.histo.size();
  sum=0;
  for(uint i=0;i<all.histo.size();i++)
    {
      sum+=all.histo[i];
    }
  double avea=sum/all.histo.size();
  double up=0;
  for(uint i=0;i<all.histo.size();i++)
    {
      up+=(query.histo[i]-aveq)*(all.histo[i]-avea);
    }
  double downleft=0;
  for(uint i=0;i<all.histo.size();i++)
    {
      downleft+=pow((query.histo[i]-aveq),2);
    }
  double downright=0;
  for(uint i=0;i<all.histo.size();i++)
    {
      downright+=pow((all.histo[i]-avea),2);
    }

  return up/sqrt(downleft*downright);
}


void Histo::generateReport(imgHisto& query, int part[], string method)
{
  //generateHist(part);
  HDist tmpDist;
  if(method=="L2")
    {
      for(uint i=0;i<allImage.size();i++)
        {
          tmpDist.distance=calcL2(query,allImage[i]);
          tmpDist.name=allImage[i].imgName;
          query.dist.push_back(tmpDist);
        }
    }
  else if(method=="HI")
    {
      for(uint i=0;i<allImage.size();i++)
        {
          tmpDist.distance=calcHI(query,allImage[i]);
          tmpDist.name=allImage[i].imgName;
          query.dist.push_back(tmpDist);
        }
    }
  else if(method=="Bh")
    {
      for(uint i=0;i<allImage.size();i++)
        {
          tmpDist.distance=calcBh(query,allImage[i]);
          tmpDist.name=allImage[i].imgName;
          query.dist.push_back(tmpDist);
        }
    }
  else if(method=="Co")
    {
      for(uint i=0;i<allImage.size();i++)
        {
          tmpDist.distance=calcCo(query,allImage[i]);
          tmpDist.name=allImage[i].imgName;
          query.dist.push_back(tmpDist);
        }
    }

  sort(query.dist.begin(),query.dist.end());
  query.precision=0;
  for(uint i=0;i<30;i++)
    {
      if(query.dist[i].name.find(query.nameCore)!=string::npos)
        {
          //cout<<part[0]<<method<<' '<<query.dist[i].name<<endl;
          query.precision++;
        }
    }

  stringstream bins;
  int bin=part[0]*part[1]*part[2];
  bins<<bin;


  myMkdir("./Output/");
  string FileName("./Output/");
  FileName.append(bins.str()+"_"+method);
  myMkdir("./Output/"+bins.str()+"_"+method);


  FileName.append("/res_");


  string imgS=query.imgName;
  imgS.erase(imgS.begin(),imgS.begin()+10);
  imgS.erase(imgS.end()-4,imgS.end());
  replace(imgS.begin(),imgS.end(),'/','_');
  FileName.append(imgS);
  string imgPath(FileName);
  imgPath.append("_sorted_images/");
  myMkdir(imgPath);

  FileName.append(".txt");

  ofstream outfile;
  string temp;
  outfile.open(FileName.c_str(),ios::out);
  Mat sortM;

  for(int i=0;i<30;i++)
    {
      temp=query.dist[i].name;
      temp.erase(temp.begin(),temp.begin()+10);
      outfile<<temp<<' '<<query.dist[i].distance<<endl;
      sortM=imread(query.dist[i].name,1);
      stringstream num;
      num<<i;
      imwrite(imgPath+num.str()+".jpg",sortM);
    }
  //overall(part,method);
}

void Histo::overall( int part[], string method)
{
  stringstream bins;
  int bin=part[0]*part[1]*part[2];
  bins<<bin;
  string FileName("./Output/");
  FileName.append(bins.str()+"_"+method);
  FileName.append("/res_overall.txt");
  ofstream outfile;
  outfile.open(FileName.c_str(),ios::out);
  string temp;

  double pre=0;
  for(uint i=0;i<queryImage.size();i++)
    {
      stringstream ss;
      temp=queryImage[i].imgName;
      temp.erase(temp.begin(),temp.begin()+10);
      temp.erase(temp.end()-4,temp.end());
      ss<<queryImage[i].precision;
      pre+=queryImage[i].precision;
      outfile<<temp<<' '<<ss.str()<<"/30"<<endl;
    }
  pre=pre/queryImage.size()/30;
  outfile<<"Average Overall:"<<pre<<endl;
}

void Histo::clear()
{
  for(uint i=0;i<queryImage.size();i++)
    {
      queryImage[i].clear();
    }
}

void Histo::clearH()
{
  for(uint i=0;i<queryImage.size();i++)
    {
      queryImage[i].clearH();
    }
  for(uint i=0;i<allImage.size();i++)
    {
      allImage[i].clearH();
    }
}
