package commend;
import Jama.Matrix;
import java.io.*;

public class test {
    public static void main(String[] args) {

        double [][]ori=new double[1000][1000];
        double [][]ori_2=new double[1000][1000];


        BufferedReader reader;
        try {
            reader = new BufferedReader(new FileReader(
                    "C:\\Users\\Q\\Desktop\\Discrete Mathematics\\Final\\facebook\\0.txt"));
            String line = reader.readLine();
            while (line != null) {
                String arr[] = line.split("\\s+");
                int i=Integer.parseInt(arr[0]);
                int j=Integer.parseInt(arr[1]);
                ori[i][j]=1;
                ori[j][i]=1;
                line = reader.readLine();
            }
            reader.close();
        } catch (IOException e) {
            e.printStackTrace();
        }


        try {
            reader = new BufferedReader(new FileReader(
                    "C:\\Users\\Q\\Desktop\\Discrete Mathematics\\Final\\facebook\\1.txt"));
            String line_2 = reader.readLine();
            while (line_2 != null) {
                String arr[] = line_2.split("\\s+");
                int i=Integer.parseInt(arr[0]);
                int j=Integer.parseInt(arr[1]);
                ori_2[i][j]=1;
                ori_2[j][i]=1;
                line_2 = reader.readLine();
            }
            reader.close();
        } catch (IOException e) {
            e.printStackTrace();
        }


        Matrix origin=new Matrix(ori);
        int row=origin.getRowDimension();


        Matrix result1=score(origin,row);

        Matrix result2=new Matrix(delete(result1,origin));

        double[][] r=result2.getArray();
        double[][] rr=new double[1000][1000];

        for(int i=0;i<row;i++){
            for(int j=0;j<row;j++){
                rr[i][j]=r[i][j];
            }
        }

        System.out.println();

        for(int t=0;t<row;t++) {
            quickSort(rr[t], 0, row - 1);
        }

        System.out.println();

        //记录预测结果
        int [][]foresee=new int[row][5];
        int t=0;

        for(int j=1;j<row;j++){
            t=0;
            for (int i = 1; i < row&&t<5&&rr[j][t]!=0; i++) {
                if (r[j][i] == rr[j][t]) {
                    foresee[j][t] = i;
                    System.out.print(i + " ");
                    t++;
                    if(rr[j][t]!=rr[j][t-1]) {
                        i = 0;
                    }
                }
              }
            System.out.println();
        }

        System.out.println();

        int marks=mark(foresee,ori_2,row);

        System.out.println("该参数下的算法得分为：");
        System.out.println(marks);

    }

    public static Matrix score(Matrix origin,int row){
        Matrix oorigin=origin;
        oorigin=re_delete(oorigin.getArray(),oorigin.getRowDimension());
        double[]r=new double[row*row];
        Matrix result=new Matrix(r,row);
        //------------------参数调整-----------------
        //t<n,n为关系产生中间人最大数量，这里默认为3个，既最长可以通过A认识到B，B认识到C，C认识到D，D认识到E，从而A认识到E
        //pow()中的常数为每次自乘后的值乘以的权重的底数，这里为乘以0.8的t次方
        for(int t=0;t<3;t++) {
            origin=re_delete(origin.getArray(),origin.getRowDimension());
            origin=origin.times(oorigin);
            origin=re_delete(origin.getArray(),origin.getRowDimension());
            origin=new Matrix(delete(origin,result));
            result=result.plus(origin.times(Math.pow(0.8,t)));
        }
        //------------------------------------------
        return result;
    }
    //将不必要的数据删除
    public static double[][] delete(Matrix result1,Matrix origin){
        double[][]re= result1.getArray();
        double[][]or= origin.getArray();
       for(int i=0;i<result1.getRowDimension();i++) {
           for (int j = 0; j < result1.getRowDimension(); j++) {
               if (or[i][j] == 1) {
                   re[i][j] = 0;
               }
           }
       }
       Matrix result=re_delete(re,result1.getRowDimension());
       re=result.getArray();
       return re;
    }

    //去自反，防止自己到自己的错误路径产生
    public static Matrix re_delete(double[][] re,int row){
        for(int t=0;t<row;t++)
        {
            re[t][t]=0;
        }
        Matrix result=new Matrix(re);
       return result;
    }
    public static void quickSort(double[] nums,int start,int end){
        if(start>=end) return;

        double pivot=nums[start];
        int i=start;
        int j=end;
        while(i<j) {
            while (i < j && nums[j] <= pivot) {
                j--;
            }

            if (i < j) {
                nums[i++] = nums[j];
            }

            while (i < j && nums[i] > pivot) {
                i++;
            }
            if (i < j) {
                nums[j--] = nums[i];
            }
        }

        nums[i]=pivot;

        quickSort(nums,start,i-1);
        quickSort(nums,i+1,end);
    }

    public static int mark(int [][]foresee,double[][]ori_2,int row){

        int marks=0;
        //算分，并打印出推荐列表
        for(int j=1;j<row;j++) {
            //t<n,n为给一个用户推荐可添加好友个数,这里给一个人推荐三个好友
            for (int t = 0; t<3&&foresee[j][t]!=0; t++) {
                System.out.print(foresee[j][t]+" ");
                    if(ori_2[j][foresee[j][t]]==1)
                        marks=marks+1;
                    }
            System.out.println();
            }
        return marks;

    }

}


