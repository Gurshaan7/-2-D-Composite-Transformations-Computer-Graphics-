#include <GL/gl.h>
#include <GL/glu.h>

#include <GL/glut.h>
#include<bits/stdc++.h>
using namespace std;

vector<vector<float>> multiplication(vector<vector<float>> mat1,vector<vector<float>> mat2){
    int p=mat1.size();
    int q=mat2[0].size();
    int n=mat1[0].size();
    vector<vector<float>> ans(p,vector<float>(q,0));

     for(int i = 0; i < p; i++){
        for(int j = 0; j < q; j++){
            for(int k = 0; k < n;k++){
                ans[i][j] += mat1[i][k]*mat2[k][j];
            }
        }
    }
    return ans;


}



vector<vector<float>> transfromation(vector<vector<float>> &mat){

    vector<vector<float>> ans=mat; 
    char ch;

    cout<<"Do you want to continue"<<endl;
    cin>>ch;
    while(ch=='y')
    {
    char choice;

    cout<<"For translation press -> t "<<endl;
    cout<<"For rotation press -> r "<<endl;
    cout<<"For scaling  press -> s "<<endl;
    cin>> choice;


    if(choice=='t'){
        float tx,ty;
        cout<<"Enter tx ,ty "<<endl;
        cin>>tx>>ty;
        vector<vector<float>> tmat(3,vector<float> (3,0));
        tmat[0][0]=1;
        tmat[0][2]=tx;
        tmat[1][2]=ty;
        tmat[1][1]=1;
        tmat[2][2]=1;
        ans=multiplication(tmat,ans);


    }

    else if(choice=='r'){
        float ang;
        cout<<"Enter angle of rotation"<<endl;
        cin>>ang;
        ang*=0.0174533;//converting in radians
        vector<vector<float>> rmat(3,vector<float> (3,0));
        rmat[0][0]=cos(ang);
        rmat[0][1]=-1*sin(ang);
        rmat[0][2]=0;
        rmat[1][0]=sin(ang);
        rmat[1][1]=cos(ang);
        rmat[1][2]=0;
        rmat[2][0]=0;
        rmat[2][1]=0;
        rmat[2][2]=1;
        ans=multiplication(rmat,ans);
    }

    else{
        float sx,sy;
        cout<<"Enter sx ,sy "<<endl;
        cin>>sx>>sy;
        vector<vector<float>> smat(3,vector<float> (3,0));
        smat[0][0]=sx;
        smat[1][1]=sy;
        smat[2][2]=1;
        ans=multiplication(smat,ans);
    }




    cout<<"Do you want to continue"<<endl;
    cin>>ch;

    }



    return ans;

}



void display(void)
{


    float xi,yi,xf,yf,dx,dy;
    float x_inc,y_inc;

    vector<vector<float>> mat(3);

    cout<<"Enter the starting point"<<endl;
    cin>>xi>>yi;
    cout<<"Enter the final point"<<endl;
    cin>>xf>>yf;
    dx=xf-xi;
    dy=yf-yi;
    float steps=max(abs(dx),abs(dy));
    x_inc=dx/steps;
    y_inc=dy/steps;
    mat[0].push_back(xi);
    mat[1].push_back(yi);
    mat[2].push_back(1);
    glBegin(GL_POINTS);
     glVertex2i(round(xi),round(yi));
    for(int i=1;i<=steps;i++){
        xi+=x_inc;
        yi+=y_inc;
        mat[0].push_back(round(xi));
        mat[1].push_back(round(yi));
        mat[2].push_back(round(1));
        glVertex2i(round(xi),round(yi));
    }


    vector<vector<float>> ans=transfromation(mat);

    int s=ans[0].size();
    glColor3f(1,0,1);
    for(int i=0;i<s;i++){
        glVertex2i(round(ans[0][i]),round(ans[1][i]));
    }



    glEnd();
    glFlush();

}
void init()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0,700.0,0,700.0,1.0,-1.0);
}
int main(int argc,char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE);
    glutInitWindowSize(700,700);
    glutInitWindowPosition(0,0);

    glutCreateWindow("Window 1");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;

}
