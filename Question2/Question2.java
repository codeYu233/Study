package DM_1;
import Jama.Matrix;

public class test {
    public static void main(String[] args) {

        //输入要进行操作的关系矩阵
       double [][]a={
               {0,0,0,1},
               {0,0,0,1},
               {1,0,0,0},
               {0,1,0,0}
       } ;
        Matrix matrix = new Matrix(a);

        //获取矩阵行数(列数)
        int row=matrix.getRowDimension();

        //显示输入矩阵
        System.out.println("输入矩阵为：");
        matrix.print(row,1);

        //进行初步操作并显示操作结果
        Matrix t=transitive(row,a);
        System.out.println("初步操作后结果为：");
        t.print(row,1);

        //得到传递闭包关系矩阵并显示结果
      Matrix re=new Matrix(change(t,row));
        System.out.println("传递闭包关系矩阵：");
       re.print(row,1);

       //得到增添关系矩阵并显示结果
      Matrix tran=new Matrix(gettran(re,matrix));
        System.out.println("需增添关系矩阵：");
      tran.print(row,1);

    }




    /*初步推导处理*/
    public static Matrix transitive(int n,double [][]a){
        double[]temp2=new double[n*n];
       Matrix tp2=new Matrix(temp2,n);
        Matrix A=new Matrix(a);
        Matrix tp=new Matrix(a);
       for(int i=0;i<n;i++){
          tp2=tp2.plus(A);
          A=A.times(tp);
       }
       return tp2;
    }




    /*获得传递闭包矩阵*/

public static double[][] change(Matrix t,int n) {

    double[][] result = t.getArray();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (result[i][j] > 1) {
                result[i][j] = 1;
            }
        }
    }
    return result;

}


/*获取闭包要添加的关系矩阵*/

public static double[][] gettran(Matrix result,Matrix origin){
       return result.minus(origin).getArray();
}
}
